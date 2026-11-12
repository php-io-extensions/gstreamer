/*
 * The field getters of the handle classes, read live from the native struct.
 * Every getter method's entry is this one function (each module's file maps
 * zim_<Class>_<field> to gstreamer_field before it includes its arginfo): it
 * finds the field by the called method's class and name.
 */

#include "runtime.h"

typedef enum {
	FIELD_INT,          /* gint, or an enum */
	FIELD_UINT64,       /* guint64 (GstClockTime) */
	FIELD_GSIZE,        /* gsize */
	FIELD_GOBJECT,      /* a GstObject * the struct holds, as a handle of its most derived bound class */
	FIELD_VIDEO_FORMAT, /* const GstVideoFormatInfo *, as its GstVideoFormat */
	FIELD_AUDIO_FORMAT, /* const GstAudioFormatInfo *, as its GstAudioFormat */
	FIELD_INTS,         /* gint [GST_VIDEO_MAX_PLANES] */
	FIELD_GSIZES,       /* gsize [GST_VIDEO_MAX_PLANES] */
} gstreamer_field_kind;

typedef struct {
	zend_class_entry **ce;
	const char *name;
	gstreamer_field_kind kind;
	size_t offset;
} gstreamer_field_entry;

#define F(cls, field, kind) { &gstreamer_ce_##cls, #field, kind, offsetof(cls, field) }

static const gstreamer_field_entry gstreamer_fields[] = {
	F(GstMessage, type, FIELD_INT),
	F(GstMessage, timestamp, FIELD_UINT64),
	F(GstMessage, src, FIELD_GOBJECT),

	F(GstBuffer, pts, FIELD_UINT64),
	F(GstBuffer, dts, FIELD_UINT64),
	F(GstBuffer, duration, FIELD_UINT64),
	F(GstBuffer, offset, FIELD_UINT64),

	F(GstVideoInfo, finfo, FIELD_VIDEO_FORMAT),
	F(GstVideoInfo, interlace_mode, FIELD_INT),
	F(GstVideoInfo, flags, FIELD_INT),
	F(GstVideoInfo, width, FIELD_INT),
	F(GstVideoInfo, height, FIELD_INT),
	F(GstVideoInfo, size, FIELD_GSIZE),
	F(GstVideoInfo, views, FIELD_INT),
	F(GstVideoInfo, fps_n, FIELD_INT),
	F(GstVideoInfo, fps_d, FIELD_INT),
	F(GstVideoInfo, par_n, FIELD_INT),
	F(GstVideoInfo, par_d, FIELD_INT),
	F(GstVideoInfo, stride, FIELD_INTS),
	F(GstVideoInfo, offset, FIELD_GSIZES),

	F(GstAudioInfo, finfo, FIELD_AUDIO_FORMAT),
	F(GstAudioInfo, flags, FIELD_INT),
	F(GstAudioInfo, layout, FIELD_INT),
	F(GstAudioInfo, rate, FIELD_INT),
	F(GstAudioInfo, channels, FIELD_INT),
	F(GstAudioInfo, bpf, FIELD_INT),
};

ZEND_NAMED_FUNCTION(gstreamer_field)
{
	zend_object *self = Z_OBJ_P(ZEND_THIS);
	zend_string *method = EX(func)->common.function_name;
	const gstreamer_field_entry *entry = NULL;
	const char *base;
	size_t i;

	ZEND_PARSE_PARAMETERS_NONE();

	for (i = 0; i < sizeof(gstreamer_fields) / sizeof(gstreamer_fields[0]); i++) {
		if (*gstreamer_fields[i].ce == self->ce && zend_string_equals_cstr(method, gstreamer_fields[i].name, strlen(gstreamer_fields[i].name))) {
			entry = &gstreamer_fields[i];
			break;
		}
	}
	ZEND_ASSERT(entry != NULL);

	base = gstreamer_ptr(self);
	/* The getter reads the struct itself: a released handle is NULL. */
	if (!GSTREAMER_PROBE_OFF("gst-field-released") && (base == NULL)) {
		zend_value_error("%s has been released", ZSTR_VAL(self->ce->name)); /* binding:gst-field-released */
		RETURN_THROWS();
	}
	base += entry->offset;

	switch (entry->kind) {
		case FIELD_INT:
			RETURN_LONG(*(const gint *) base);
		case FIELD_UINT64:
			RETURN_LONG((zend_long) *(const guint64 *) base);
		case FIELD_GSIZE:
			RETURN_LONG((zend_long) *(const gsize *) base);
		case FIELD_GOBJECT:
			gstreamer_box_gobject(return_value, *(gpointer const *) base);
			return;
		case FIELD_VIDEO_FORMAT:
			RETURN_LONG((*(const GstVideoFormatInfo *const *) base)->format);
		case FIELD_AUDIO_FORMAT:
			RETURN_LONG((*(const GstAudioFormatInfo *const *) base)->format);
		case FIELD_INTS:
			array_init_size(return_value, GST_VIDEO_MAX_PLANES);
			for (i = 0; i < GST_VIDEO_MAX_PLANES; i++) {
				add_next_index_long(return_value, ((const gint *) base)[i]);
			}
			return;
		case FIELD_GSIZES:
			array_init_size(return_value, GST_VIDEO_MAX_PLANES);
			for (i = 0; i < GST_VIDEO_MAX_PLANES; i++) {
				add_next_index_long(return_value, (zend_long) ((const gsize *) base)[i]);
			}
			return;
	}
}

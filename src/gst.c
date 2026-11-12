/* gstreamer-1.0: init, version, pipelines, elements, bus, messages, caps, structures, samples, buffers. */

#include "runtime.h"
#include "ext/spl/spl_exceptions.h"

#define zim_GstMessage_type gstreamer_field
#define zim_GstMessage_timestamp gstreamer_field
#define zim_GstMessage_src gstreamer_field
#define zim_GstBuffer_pts gstreamer_field
#define zim_GstBuffer_dts gstreamer_field
#define zim_GstBuffer_duration gstreamer_field
#define zim_GstBuffer_offset gstreamer_field

#include "../stubs/gst_arginfo.h"

zend_class_entry *gstreamer_ce_GstError;
zend_class_entry *gstreamer_ce_GstMapInfo;
zend_class_entry *gstreamer_ce_GstObject;
zend_class_entry *gstreamer_ce_GstElement;
zend_class_entry *gstreamer_ce_GstBin;
zend_class_entry *gstreamer_ce_GstPipeline;
zend_class_entry *gstreamer_ce_GstBus;
zend_class_entry *gstreamer_ce_GstMessage;
zend_class_entry *gstreamer_ce_GstCaps;
zend_class_entry *gstreamer_ce_GstStructure;
zend_class_entry *gstreamer_ce_GstSample;
zend_class_entry *gstreamer_ce_GstBuffer;

GSTREAMER_HANDLE_METHODS(GstObject)
GSTREAMER_HANDLE_METHODS(GstMessage)
GSTREAMER_HANDLE_METHODS(GstCaps)
GSTREAMER_HANDLE_METHODS(GstStructure)
GSTREAMER_HANDLE_METHODS(GstSample)
GSTREAMER_HANDLE_METHODS(GstBuffer)

ZEND_METHOD(GstMapInfo, __construct)
{
	ZEND_PARSE_PARAMETERS_NONE();
}

#define P(obj) gstreamer_ptr(obj)

PHP_FUNCTION(gst_init_check)
{
	zval *ref, *list;
	GError *error = NULL;
	gboolean ok;

	ZEND_PARSE_PARAMETERS_START(1, 1)
		Z_PARAM_ZVAL(ref)
	ZEND_PARSE_PARAMETERS_END();

	/* The parameter is ?array by reference: PHP checked the type on entry. */
	list = Z_REFVAL_P(ref);
	if (Z_TYPE_P(list) == IS_ARRAY) {
		int argc = 0, i;
		uint32_t n = zend_hash_num_elements(Z_ARRVAL_P(list));
		char **argv = ecalloc(n + 1, sizeof(char *));
		char **owned = ecalloc(n + 1, sizeof(char *));
		zval *zv, rest;

		ZEND_HASH_FOREACH_VAL(Z_ARRVAL_P(list), zv) {
			zend_string *s = zval_try_get_string(zv);

			if (s == NULL) {
				for (i = 0; i < argc; i++) {
					efree(owned[i]);
				}
				efree(argv);
				efree(owned);
				RETURN_THROWS();
			}
			owned[argc] = argv[argc] = estrndup(ZSTR_VAL(s), ZSTR_LEN(s));
			argc++;
			zend_string_release(s);
		} ZEND_HASH_FOREACH_END();

		ok = gst_init_check(&argc, &argv, &error);

		array_init_size(&rest, argc);
		for (i = 0; i < argc; i++) {
			add_next_index_string(&rest, argv[i]);
		}
		ZEND_TRY_ASSIGN_REF_TMP(ref, &rest);
		for (i = 0; i < (int) n; i++) {
			efree(owned[i]);
		}
		efree(argv);
		efree(owned);
	} else {
		ok = gst_init_check(NULL, NULL, &error);
	}

	if (error != NULL) {
		gstreamer_throw_gerror(error);
		g_error_free(error);
		RETURN_THROWS();
	}
	RETURN_BOOL(ok);
}

PHP_FUNCTION(gst_version)
{
	zval *major, *minor, *micro, *nano;
	guint v_major, v_minor, v_micro, v_nano;

	ZEND_PARSE_PARAMETERS_START(4, 4)
		Z_PARAM_ZVAL(major)
		Z_PARAM_ZVAL(minor)
		Z_PARAM_ZVAL(micro)
		Z_PARAM_ZVAL(nano)
	ZEND_PARSE_PARAMETERS_END();

	gst_version(&v_major, &v_minor, &v_micro, &v_nano);
	ZEND_TRY_ASSIGN_REF_LONG(major, v_major);
	ZEND_TRY_ASSIGN_REF_LONG(minor, v_minor);
	ZEND_TRY_ASSIGN_REF_LONG(micro, v_micro);
	ZEND_TRY_ASSIGN_REF_LONG(nano, v_nano);
}

PHP_FUNCTION(gst_version_string)
{
	ZEND_PARSE_PARAMETERS_NONE();

	gstreamer_return_owned_string(return_value, gst_version_string());
}

PHP_FUNCTION(gst_parse_launch)
{
	zend_string *description;
	GError *error = NULL;
	GstElement *element;

	ZEND_PARSE_PARAMETERS_START(1, 1)
		Z_PARAM_STR(description)
	ZEND_PARSE_PARAMETERS_END();

	element = gst_parse_launch(ZSTR_VAL(description), &error);
	if (error != NULL) {
		/* A partial pipeline comes with the error: the thrown GError replaces it, so it is unreffed here. */
		if (element != NULL) {
			gst_object_unref(element);
		}
		gstreamer_throw_gerror(error);
		g_error_free(error);
		RETURN_THROWS();
	}
	gstreamer_box_gobject(return_value, element);
	gstreamer_take(return_value);
}

PHP_FUNCTION(gst_pipeline_new)
{
	zend_string *name = NULL;

	ZEND_PARSE_PARAMETERS_START(1, 1)
		Z_PARAM_STR_OR_NULL(name)
	ZEND_PARSE_PARAMETERS_END();

	gstreamer_box_gobject(return_value, gst_pipeline_new(name != NULL ? ZSTR_VAL(name) : NULL));
	gstreamer_take(return_value);
}

PHP_FUNCTION(gst_element_factory_make)
{
	zend_string *factoryname, *name = NULL;

	ZEND_PARSE_PARAMETERS_START(2, 2)
		Z_PARAM_STR(factoryname)
		Z_PARAM_STR_OR_NULL(name)
	ZEND_PARSE_PARAMETERS_END();

	gstreamer_box_gobject(return_value, gst_element_factory_make(ZSTR_VAL(factoryname), name != NULL ? ZSTR_VAL(name) : NULL));
	gstreamer_take(return_value);
}

PHP_FUNCTION(gst_bin_add)
{
	zend_object *bin, *element;
	gboolean floating, ok;

	ZEND_PARSE_PARAMETERS_START(2, 2)
		Z_PARAM_OBJ_OF_CLASS(bin, gstreamer_ce_GstBin)
		Z_PARAM_OBJ_OF_CLASS(element, gstreamer_ce_GstElement)
	ZEND_PARSE_PARAMETERS_END();

	floating = P(element) != NULL && g_object_is_floating(P(element));
	ok = gst_bin_add(P(bin), P(element));
	if (ok && floating) {
		gstreamer_disown(element);
	}
	RETURN_BOOL(ok);
}

PHP_FUNCTION(gst_bin_remove)
{
	zend_object *bin, *element;
	gboolean ok;

	ZEND_PARSE_PARAMETERS_START(2, 2)
		Z_PARAM_OBJ_OF_CLASS(bin, gstreamer_ce_GstBin)
		Z_PARAM_OBJ_OF_CLASS(element, gstreamer_ce_GstElement)
	ZEND_PARSE_PARAMETERS_END();

	ok = gst_bin_remove(P(bin), P(element));
	/* The bin held the only reference the binding knows of: the element is gone with it. */
	if (ok && gstreamer_handle_from(element)->refs == 0) {
		gstreamer_release(element);
	}
	RETURN_BOOL(ok);
}

PHP_FUNCTION(gst_bin_get_by_name)
{
	zend_object *bin;
	zend_string *name;

	ZEND_PARSE_PARAMETERS_START(2, 2)
		Z_PARAM_OBJ_OF_CLASS(bin, gstreamer_ce_GstBin)
		Z_PARAM_STR(name)
	ZEND_PARSE_PARAMETERS_END();

	gstreamer_box_gobject(return_value, gst_bin_get_by_name(P(bin), ZSTR_VAL(name)));
	gstreamer_take(return_value);
}

PHP_FUNCTION(gst_element_link)
{
	zend_object *src, *dest;

	ZEND_PARSE_PARAMETERS_START(2, 2)
		Z_PARAM_OBJ_OF_CLASS(src, gstreamer_ce_GstElement)
		Z_PARAM_OBJ_OF_CLASS(dest, gstreamer_ce_GstElement)
	ZEND_PARSE_PARAMETERS_END();

	RETURN_BOOL(gst_element_link(P(src), P(dest)));
}

PHP_FUNCTION(gst_element_link_filtered)
{
	zend_object *src, *dest, *filter = NULL;

	ZEND_PARSE_PARAMETERS_START(3, 3)
		Z_PARAM_OBJ_OF_CLASS(src, gstreamer_ce_GstElement)
		Z_PARAM_OBJ_OF_CLASS(dest, gstreamer_ce_GstElement)
		Z_PARAM_OBJ_OF_CLASS_OR_NULL(filter, gstreamer_ce_GstCaps)
	ZEND_PARSE_PARAMETERS_END();

	RETURN_BOOL(gst_element_link_filtered(P(src), P(dest), gstreamer_ptr_or_null(filter)));
}

PHP_FUNCTION(gst_element_unlink)
{
	zend_object *src, *dest;

	ZEND_PARSE_PARAMETERS_START(2, 2)
		Z_PARAM_OBJ_OF_CLASS(src, gstreamer_ce_GstElement)
		Z_PARAM_OBJ_OF_CLASS(dest, gstreamer_ce_GstElement)
	ZEND_PARSE_PARAMETERS_END();

	gst_element_unlink(P(src), P(dest));
}

PHP_FUNCTION(gst_element_set_state)
{
	zend_object *element;
	zend_long state;

	ZEND_PARSE_PARAMETERS_START(2, 2)
		Z_PARAM_OBJ_OF_CLASS(element, gstreamer_ce_GstElement)
		Z_PARAM_LONG(state)
	ZEND_PARSE_PARAMETERS_END();

	RETURN_LONG(gst_element_set_state(P(element), (GstState) state));
}

PHP_FUNCTION(gst_element_get_state)
{
	zend_object *element;
	zval *state, *pending;
	zend_long timeout;
	GstState s = GST_STATE_VOID_PENDING, p = GST_STATE_VOID_PENDING;
	GstStateChangeReturn ret;

	ZEND_PARSE_PARAMETERS_START(4, 4)
		Z_PARAM_OBJ_OF_CLASS(element, gstreamer_ce_GstElement)
		Z_PARAM_ZVAL(state)
		Z_PARAM_ZVAL(pending)
		Z_PARAM_LONG(timeout)
	ZEND_PARSE_PARAMETERS_END();

	ret = gst_element_get_state(P(element), &s, &p, (GstClockTime) timeout);
	ZEND_TRY_ASSIGN_REF_LONG(state, s);
	ZEND_TRY_ASSIGN_REF_LONG(pending, p);
	RETURN_LONG(ret);
}

PHP_FUNCTION(gst_element_get_bus)
{
	zend_object *element;

	ZEND_PARSE_PARAMETERS_START(1, 1)
		Z_PARAM_OBJ_OF_CLASS(element, gstreamer_ce_GstElement)
	ZEND_PARSE_PARAMETERS_END();

	gstreamer_box_gobject(return_value, gst_element_get_bus(P(element)));
	gstreamer_take(return_value);
}

PHP_FUNCTION(gst_element_seek_simple)
{
	zend_object *element;
	zend_long format, flags, pos;

	ZEND_PARSE_PARAMETERS_START(4, 4)
		Z_PARAM_OBJ_OF_CLASS(element, gstreamer_ce_GstElement)
		Z_PARAM_LONG(format)
		Z_PARAM_LONG(flags)
		Z_PARAM_LONG(pos)
	ZEND_PARSE_PARAMETERS_END();

	RETURN_BOOL(gst_element_seek_simple(P(element), (GstFormat) format, (GstSeekFlags) flags, (gint64) pos));
}

PHP_FUNCTION(gst_element_query_position)
{
	zend_object *element;
	zend_long format;
	zval *cur;
	gint64 value = 0;
	gboolean ok;

	ZEND_PARSE_PARAMETERS_START(3, 3)
		Z_PARAM_OBJ_OF_CLASS(element, gstreamer_ce_GstElement)
		Z_PARAM_LONG(format)
		Z_PARAM_ZVAL(cur)
	ZEND_PARSE_PARAMETERS_END();

	ok = gst_element_query_position(P(element), (GstFormat) format, &value);
	ZEND_TRY_ASSIGN_REF_LONG(cur, value);
	RETURN_BOOL(ok);
}

PHP_FUNCTION(gst_element_query_duration)
{
	zend_object *element;
	zend_long format;
	zval *duration;
	gint64 value = 0;
	gboolean ok;

	ZEND_PARSE_PARAMETERS_START(3, 3)
		Z_PARAM_OBJ_OF_CLASS(element, gstreamer_ce_GstElement)
		Z_PARAM_LONG(format)
		Z_PARAM_ZVAL(duration)
	ZEND_PARSE_PARAMETERS_END();

	ok = gst_element_query_duration(P(element), (GstFormat) format, &value);
	ZEND_TRY_ASSIGN_REF_LONG(duration, value);
	RETURN_BOOL(ok);
}

PHP_FUNCTION(gst_element_state_get_name)
{
	zend_long state;

	ZEND_PARSE_PARAMETERS_START(1, 1)
		Z_PARAM_LONG(state)
	ZEND_PARSE_PARAMETERS_END();

	gstreamer_return_string(return_value, gst_element_state_get_name((GstState) state));
}

PHP_FUNCTION(gst_element_state_change_return_get_name)
{
	zend_long ret;

	ZEND_PARSE_PARAMETERS_START(1, 1)
		Z_PARAM_LONG(ret)
	ZEND_PARSE_PARAMETERS_END();

	gstreamer_return_string(return_value, gst_element_state_change_return_get_name((GstStateChangeReturn) ret));
}

PHP_FUNCTION(gst_object_ref)
{
	zend_object *object;

	ZEND_PARSE_PARAMETERS_START(1, 1)
		Z_PARAM_OBJ(object)
	ZEND_PARSE_PARAMETERS_END();

	if (!gstreamer_gobject_arg(object, 1)) {
		RETURN_THROWS();
	}
	gstreamer_box_gobject(return_value, gst_object_ref(P(object)));
	gstreamer_take(return_value);
}

PHP_FUNCTION(gst_object_unref)
{
	zend_object *object;

	ZEND_PARSE_PARAMETERS_START(1, 1)
		Z_PARAM_OBJ(object)
	ZEND_PARSE_PARAMETERS_END();

	if (!gstreamer_gobject_arg(object, 1)) {
		RETURN_THROWS();
	}
	gst_object_unref(P(object));
	gstreamer_unref(object);
}

PHP_FUNCTION(gst_object_get_name)
{
	zend_object *object;

	ZEND_PARSE_PARAMETERS_START(1, 1)
		Z_PARAM_OBJ_OF_CLASS(object, gstreamer_ce_GstObject)
	ZEND_PARSE_PARAMETERS_END();

	gstreamer_return_owned_string(return_value, gst_object_get_name(P(object)));
}

PHP_FUNCTION(gst_util_set_object_arg)
{
	zend_object *object;
	zend_string *name, *value;

	ZEND_PARSE_PARAMETERS_START(3, 3)
		Z_PARAM_OBJ(object)
		Z_PARAM_STR(name)
		Z_PARAM_STR(value)
	ZEND_PARSE_PARAMETERS_END();

	if (!gstreamer_gobject_arg(object, 1)) {
		RETURN_THROWS();
	}
	gst_util_set_object_arg(P(object), ZSTR_VAL(name), ZSTR_VAL(value));
}

PHP_FUNCTION(gst_bus_timed_pop_filtered)
{
	zend_object *bus;
	zend_long timeout, types;

	ZEND_PARSE_PARAMETERS_START(3, 3)
		Z_PARAM_OBJ_OF_CLASS(bus, gstreamer_ce_GstBus)
		Z_PARAM_LONG(timeout)
		Z_PARAM_LONG(types)
	ZEND_PARSE_PARAMETERS_END();

	gstreamer_box(return_value, gst_bus_timed_pop_filtered(P(bus), (GstClockTime) timeout, (GstMessageType) types), gstreamer_ce_GstMessage);
	gstreamer_take(return_value);
}

PHP_FUNCTION(gst_message_unref)
{
	zend_object *msg;

	ZEND_PARSE_PARAMETERS_START(1, 1)
		Z_PARAM_OBJ_OF_CLASS(msg, gstreamer_ce_GstMessage)
	ZEND_PARSE_PARAMETERS_END();

	gst_message_unref(P(msg));
	gstreamer_unref(msg);
}

PHP_FUNCTION(gst_message_type_get_name)
{
	zend_long type;

	ZEND_PARSE_PARAMETERS_START(1, 1)
		Z_PARAM_LONG(type)
	ZEND_PARSE_PARAMETERS_END();

	gstreamer_return_string(return_value, gst_message_type_get_name((GstMessageType) type));
}

/* parse_error / parse_warning: debug goes to the reference, the message's GError is thrown. */
static void gstreamer_parse_report(INTERNAL_FUNCTION_PARAMETERS, void (*parse)(GstMessage *, GError **, gchar **))
{
	zend_object *message;
	zval *debug;
	GError *error = NULL;
	gchar *text = NULL;
	zval value;

	ZEND_PARSE_PARAMETERS_START(2, 2)
		Z_PARAM_OBJ_OF_CLASS(message, gstreamer_ce_GstMessage)
		Z_PARAM_ZVAL(debug)
	ZEND_PARSE_PARAMETERS_END();

	parse(P(message), &error, &text);
	gstreamer_return_owned_string(&value, text);
	ZEND_TRY_ASSIGN_REF_TMP(debug, &value);
	if (error != NULL) {
		gstreamer_throw_gerror(error);
		g_error_free(error);
		RETURN_THROWS();
	}
}

PHP_FUNCTION(gst_message_parse_error)
{
	gstreamer_parse_report(INTERNAL_FUNCTION_PARAM_PASSTHRU, gst_message_parse_error);
}

PHP_FUNCTION(gst_message_parse_warning)
{
	gstreamer_parse_report(INTERNAL_FUNCTION_PARAM_PASSTHRU, gst_message_parse_warning);
}

PHP_FUNCTION(gst_message_parse_state_changed)
{
	zend_object *message;
	zval *oldstate, *newstate, *pending;
	GstState o = GST_STATE_VOID_PENDING, n = GST_STATE_VOID_PENDING, p = GST_STATE_VOID_PENDING;

	ZEND_PARSE_PARAMETERS_START(4, 4)
		Z_PARAM_OBJ_OF_CLASS(message, gstreamer_ce_GstMessage)
		Z_PARAM_ZVAL(oldstate)
		Z_PARAM_ZVAL(newstate)
		Z_PARAM_ZVAL(pending)
	ZEND_PARSE_PARAMETERS_END();

	gst_message_parse_state_changed(P(message), &o, &n, &p);
	ZEND_TRY_ASSIGN_REF_LONG(oldstate, o);
	ZEND_TRY_ASSIGN_REF_LONG(newstate, n);
	ZEND_TRY_ASSIGN_REF_LONG(pending, p);
}

PHP_FUNCTION(gst_caps_from_string)
{
	zend_string *string;

	ZEND_PARSE_PARAMETERS_START(1, 1)
		Z_PARAM_STR(string)
	ZEND_PARSE_PARAMETERS_END();

	gstreamer_box(return_value, gst_caps_from_string(ZSTR_VAL(string)), gstreamer_ce_GstCaps);
	gstreamer_take(return_value);
}

PHP_FUNCTION(gst_caps_to_string)
{
	zend_object *caps;

	ZEND_PARSE_PARAMETERS_START(1, 1)
		Z_PARAM_OBJ_OF_CLASS(caps, gstreamer_ce_GstCaps)
	ZEND_PARSE_PARAMETERS_END();

	gstreamer_return_owned_string(return_value, gst_caps_to_string(P(caps)));
}

PHP_FUNCTION(gst_caps_unref)
{
	zend_object *caps;

	ZEND_PARSE_PARAMETERS_START(1, 1)
		Z_PARAM_OBJ_OF_CLASS(caps, gstreamer_ce_GstCaps)
	ZEND_PARSE_PARAMETERS_END();

	gst_caps_unref(P(caps));
	gstreamer_unref(caps);
}

PHP_FUNCTION(gst_caps_get_size)
{
	zend_object *caps;

	ZEND_PARSE_PARAMETERS_START(1, 1)
		Z_PARAM_OBJ_OF_CLASS(caps, gstreamer_ce_GstCaps)
	ZEND_PARSE_PARAMETERS_END();

	RETURN_LONG(gst_caps_get_size(P(caps)));
}

PHP_FUNCTION(gst_caps_get_structure)
{
	zend_object *caps;
	zend_long index;

	ZEND_PARSE_PARAMETERS_START(2, 2)
		Z_PARAM_OBJ_OF_CLASS(caps, gstreamer_ce_GstCaps)
		Z_PARAM_LONG(index)
	ZEND_PARSE_PARAMETERS_END();

	gstreamer_box(return_value, gst_caps_get_structure(P(caps), (guint) index), gstreamer_ce_GstStructure);
}

PHP_FUNCTION(gst_structure_get_name)
{
	zend_object *structure;

	ZEND_PARSE_PARAMETERS_START(1, 1)
		Z_PARAM_OBJ_OF_CLASS(structure, gstreamer_ce_GstStructure)
	ZEND_PARSE_PARAMETERS_END();

	gstreamer_return_string(return_value, gst_structure_get_name(P(structure)));
}

PHP_FUNCTION(gst_structure_to_string)
{
	zend_object *structure;

	ZEND_PARSE_PARAMETERS_START(1, 1)
		Z_PARAM_OBJ_OF_CLASS(structure, gstreamer_ce_GstStructure)
	ZEND_PARSE_PARAMETERS_END();

	gstreamer_return_owned_string(return_value, gst_structure_to_string(P(structure)));
}

PHP_FUNCTION(gst_structure_get_int)
{
	zend_object *structure;
	zend_string *fieldname;
	zval *value;
	gint v = 0;
	gboolean ok;

	ZEND_PARSE_PARAMETERS_START(3, 3)
		Z_PARAM_OBJ_OF_CLASS(structure, gstreamer_ce_GstStructure)
		Z_PARAM_STR(fieldname)
		Z_PARAM_ZVAL(value)
	ZEND_PARSE_PARAMETERS_END();

	ok = gst_structure_get_int(P(structure), ZSTR_VAL(fieldname), &v);
	ZEND_TRY_ASSIGN_REF_LONG(value, v);
	RETURN_BOOL(ok);
}

PHP_FUNCTION(gst_structure_get_fraction)
{
	zend_object *structure;
	zend_string *fieldname;
	zval *numerator, *denominator;
	gint n = 0, d = 0;
	gboolean ok;

	ZEND_PARSE_PARAMETERS_START(4, 4)
		Z_PARAM_OBJ_OF_CLASS(structure, gstreamer_ce_GstStructure)
		Z_PARAM_STR(fieldname)
		Z_PARAM_ZVAL(numerator)
		Z_PARAM_ZVAL(denominator)
	ZEND_PARSE_PARAMETERS_END();

	ok = gst_structure_get_fraction(P(structure), ZSTR_VAL(fieldname), &n, &d);
	ZEND_TRY_ASSIGN_REF_LONG(numerator, n);
	ZEND_TRY_ASSIGN_REF_LONG(denominator, d);
	RETURN_BOOL(ok);
}

PHP_FUNCTION(gst_sample_get_buffer)
{
	zend_object *sample;

	ZEND_PARSE_PARAMETERS_START(1, 1)
		Z_PARAM_OBJ_OF_CLASS(sample, gstreamer_ce_GstSample)
	ZEND_PARSE_PARAMETERS_END();

	gstreamer_box(return_value, gst_sample_get_buffer(P(sample)), gstreamer_ce_GstBuffer);
}

PHP_FUNCTION(gst_sample_get_caps)
{
	zend_object *sample;

	ZEND_PARSE_PARAMETERS_START(1, 1)
		Z_PARAM_OBJ_OF_CLASS(sample, gstreamer_ce_GstSample)
	ZEND_PARSE_PARAMETERS_END();

	gstreamer_box(return_value, gst_sample_get_caps(P(sample)), gstreamer_ce_GstCaps);
}

PHP_FUNCTION(gst_sample_unref)
{
	zend_object *sample;

	ZEND_PARSE_PARAMETERS_START(1, 1)
		Z_PARAM_OBJ_OF_CLASS(sample, gstreamer_ce_GstSample)
	ZEND_PARSE_PARAMETERS_END();

	gst_sample_unref(P(sample));
	gstreamer_unref(sample);
}

PHP_FUNCTION(gst_buffer_get_size)
{
	zend_object *buffer;

	ZEND_PARSE_PARAMETERS_START(1, 1)
		Z_PARAM_OBJ_OF_CLASS(buffer, gstreamer_ce_GstBuffer)
	ZEND_PARSE_PARAMETERS_END();

	RETURN_LONG((zend_long) gst_buffer_get_size(P(buffer)));
}

PHP_FUNCTION(gst_buffer_extract)
{
	zend_object *buffer;
	zend_long offset, size;
	zval *dest;
	zend_string *bytes;
	gsize copied;

	ZEND_PARSE_PARAMETERS_START(4, 4)
		Z_PARAM_OBJ_OF_CLASS(buffer, gstreamer_ce_GstBuffer)
		Z_PARAM_LONG(offset)
		Z_PARAM_ZVAL(dest)
		Z_PARAM_LONG(size)
	ZEND_PARSE_PARAMETERS_END();

	bytes = zend_string_alloc((size_t) size, 0);
	copied = gst_buffer_extract(P(buffer), (gsize) offset, ZSTR_VAL(bytes), (gsize) size);
	ZSTR_LEN(bytes) = copied;
	ZSTR_VAL(bytes)[copied] = '\0';
	ZEND_TRY_ASSIGN_REF_STR(dest, bytes);
	RETURN_LONG((zend_long) copied);
}

PHP_FUNCTION(gst_buffer_map)
{
	zend_object *buffer, *info;
	zend_long flags;
	gstreamer_map *map;
	gboolean ok;

	ZEND_PARSE_PARAMETERS_START(3, 3)
		Z_PARAM_OBJ_OF_CLASS(buffer, gstreamer_ce_GstBuffer)
		Z_PARAM_OBJ_OF_CLASS(info, gstreamer_ce_GstMapInfo)
		Z_PARAM_LONG(flags)
	ZEND_PARSE_PARAMETERS_END();

	map = gstreamer_map_from(info);
	ok = gst_buffer_map(P(buffer), &map->info, (GstMapFlags) flags);
	if (ok) {
		map->buffer = P(buffer);
		zend_update_property_long(gstreamer_ce_GstMapInfo, info, ZEND_STRL("flags"), map->info.flags);
		zend_update_property_stringl(gstreamer_ce_GstMapInfo, info, ZEND_STRL("data"), (const char *) map->info.data, map->info.size);
		zend_update_property_long(gstreamer_ce_GstMapInfo, info, ZEND_STRL("size"), (zend_long) map->info.size);
		zend_update_property_long(gstreamer_ce_GstMapInfo, info, ZEND_STRL("maxsize"), (zend_long) map->info.maxsize);
	}
	RETURN_BOOL(ok);
}

PHP_FUNCTION(gst_buffer_unmap)
{
	zend_object *buffer, *info;
	gstreamer_map *map;

	ZEND_PARSE_PARAMETERS_START(2, 2)
		Z_PARAM_OBJ_OF_CLASS(buffer, gstreamer_ce_GstBuffer)
		Z_PARAM_OBJ_OF_CLASS(info, gstreamer_ce_GstMapInfo)
	ZEND_PARSE_PARAMETERS_END();

	map = gstreamer_map_from(info);
	gst_buffer_unmap(P(buffer), &map->info);
	map->buffer = NULL;
}

PHP_FUNCTION(gst_format_get_name)
{
	zend_long format;

	ZEND_PARSE_PARAMETERS_START(1, 1)
		Z_PARAM_LONG(format)
	ZEND_PARSE_PARAMETERS_END();

	gstreamer_return_string(return_value, gst_format_get_name((GstFormat) format));
}

void gstreamer_register_gst(int module_number)
{
	zend_register_functions(NULL, ext_functions, NULL, MODULE_PERSISTENT);
	register_gst_symbols(module_number);

	gstreamer_ce_GstError = register_class_GstError(spl_ce_RuntimeException);
	gstreamer_ce_GstMapInfo = register_class_GstMapInfo();
	gstreamer_map_setup(gstreamer_ce_GstMapInfo);

	gstreamer_ce_GstObject = register_class_GstObject();
	gstreamer_handle_setup(gstreamer_ce_GstObject);
	gstreamer_ce_GstElement = register_class_GstElement(gstreamer_ce_GstObject);
	gstreamer_ce_GstBin = register_class_GstBin(gstreamer_ce_GstElement);
	gstreamer_ce_GstPipeline = register_class_GstPipeline(gstreamer_ce_GstBin);
	gstreamer_ce_GstBus = register_class_GstBus(gstreamer_ce_GstObject);

	gstreamer_ce_GstMessage = register_class_GstMessage();
	gstreamer_handle_setup(gstreamer_ce_GstMessage);
	gstreamer_ce_GstCaps = register_class_GstCaps();
	gstreamer_handle_setup(gstreamer_ce_GstCaps);
	gstreamer_ce_GstStructure = register_class_GstStructure();
	gstreamer_handle_setup(gstreamer_ce_GstStructure);
	gstreamer_ce_GstSample = register_class_GstSample();
	gstreamer_handle_setup(gstreamer_ce_GstSample);
	gstreamer_ce_GstBuffer = register_class_GstBuffer();
	gstreamer_handle_setup(gstreamer_ce_GstBuffer);
}

#ifndef GSTREAMER_RUNTIME_H
#define GSTREAMER_RUNTIME_H

#ifdef HAVE_CONFIG_H
# include "config.h"
#endif

#include "php.h"
#include "zend_exceptions.h"
#include "../php_gstreamer.h"

#include <gst/gst.h>
#include <gst/app/gstappsink.h>
#include <gst/video/video.h>
#include <gst/audio/audio.h>
#include <gst/pbutils/pbutils.h>

ZEND_BEGIN_MODULE_GLOBALS(gstreamer)
	HashTable boxes;               /* native address => zend_object*, live handles only, not refcounted */
ZEND_END_MODULE_GLOBALS(gstreamer)

ZEND_EXTERN_MODULE_GLOBALS(gstreamer)
#define GSTREAMER_G(v) ZEND_MODULE_GLOBALS_ACCESSOR(gstreamer, v)

typedef struct {
	void *ptr;                     /* the native object; NULL once released */
	uint32_t refs;                 /* references the binding has seen; the unref that brings it to 0 releases the handle */
	zend_object std;
} gstreamer_handle;

static zend_always_inline gstreamer_handle *gstreamer_handle_from(zend_object *obj)
{
	return (gstreamer_handle *) ((char *) obj - XtOffsetOf(gstreamer_handle, std));
}

/* The handle's native pointer: NULL once released. */
static zend_always_inline void *gstreamer_ptr(zend_object *obj)
{
	return gstreamer_handle_from(obj)->ptr;
}

/* The pointer of an optional handle argument: NULL for null or a released handle. */
static zend_always_inline void *gstreamer_ptr_or_null(zend_object *obj)
{
	return obj == NULL ? NULL : gstreamer_handle_from(obj)->ptr;
}

/* The PHP object holding ptr, or a new one of class ce. NULL ptr gives null. */
void gstreamer_box(zval *rv, void *ptr, zend_class_entry *ce);
/* As gstreamer_box, with the class picked from the object's runtime GType: the most derived bound class it is. */
void gstreamer_box_gobject(zval *rv, gpointer object);
/* A reference the binding was handed (creation, *_ref, a transfer-full getter). */
void gstreamer_ref(zend_object *obj);
/* A reference the binding gave back (*_unref): the last one releases the handle. */
void gstreamer_unref(zend_object *obj);
/* After a transfer-full return was boxed into rv: the binding holds that reference. */
static zend_always_inline void gstreamer_take(zval *rv)
{
	if (Z_TYPE_P(rv) == IS_OBJECT) {
		gstreamer_ref(Z_OBJ_P(rv));
	}
}
/* A gchar * the caller owns: returned as a string (null for NULL) and freed. */
static zend_always_inline void gstreamer_return_owned_string(zval *rv, gchar *s)
{
	if (s == NULL) {
		ZVAL_NULL(rv);
		return;
	}
	ZVAL_STRING(rv, s);
	g_free(s);
}
/* A const gchar *: returned as a string, null for NULL. */
static zend_always_inline void gstreamer_return_string(zval *rv, const gchar *s)
{
	if (s == NULL) {
		ZVAL_NULL(rv);
		return;
	}
	ZVAL_STRING(rv, s);
}
/* A floating reference another object took (gst_bin_add): the handle stays usable while its owner lives. */
void gstreamer_disown(zend_object *obj);
/* Marks a handle released: pointer cleared, identity entry dropped. */
void gstreamer_release(zend_object *obj);

void gstreamer_handle_setup(zend_class_entry *ce);

/* A GObject * / gpointer argument: a GstObject, GstDiscoverer, GstDiscovererInfo or GstDiscovererStreamInfo. False (and a TypeError) for another object. */
bool gstreamer_gobject_arg(zend_object *arg, uint32_t arg_num);

/* Throws the GError a native call reported, as GstError. Does not free it. */
void gstreamer_throw_gerror(const GError *error);

/* GstMapInfo: the native map the PHP object keeps for gst_buffer_unmap(). */
typedef struct {
	GstMapInfo info;
	GstBuffer *buffer;             /* the buffer it maps; NULL when not mapped */
	zend_object std;
} gstreamer_map;

static zend_always_inline gstreamer_map *gstreamer_map_from(zend_object *obj)
{
	return (gstreamer_map *) ((char *) obj - XtOffsetOf(gstreamer_map, std));
}

void gstreamer_map_setup(zend_class_entry *ce);

/*
 * The probe switch. A kept refusal site reads `if (!GSTREAMER_PROBE_OFF("<id>") && (<check>))`.
 * A build configured with --enable-gstreamer-probes lets env GSTREAMER_PROBE_OFF=<id> turn that one
 * site off, so tests/Probes can show the crash the site prevents; any other build compiles
 * the switch out.
 */
#ifdef GSTREAMER_PROBES
bool gstreamer_probe_off(const char *id);
# define GSTREAMER_PROBE_OFF(id) gstreamer_probe_off(id)
#else
# define GSTREAMER_PROBE_OFF(id) 0
#endif

/* pointer(), fromPointer() and the private constructor of a handle class. The address is trusted; 0 (and a released handle) is NULL. */
#define GSTREAMER_HANDLE_METHODS(cls) \
	ZEND_METHOD(cls, __construct) { ZEND_PARSE_PARAMETERS_NONE(); } \
	ZEND_METHOD(cls, pointer) { ZEND_PARSE_PARAMETERS_NONE(); RETURN_LONG((zend_long) (uintptr_t) gstreamer_ptr(Z_OBJ_P(ZEND_THIS))); } \
	ZEND_METHOD(cls, fromPointer) { zend_long p; ZEND_PARSE_PARAMETERS_START(1, 1) Z_PARAM_LONG(p) ZEND_PARSE_PARAMETERS_END(); \
		gstreamer_box(return_value, (void *) (uintptr_t) p, zend_get_called_scope(execute_data)); }

/* Every field getter of every handle class is this one function (src/fields.c). */
ZEND_NAMED_FUNCTION(gstreamer_field);

extern zend_class_entry *gstreamer_ce_GstError;
extern zend_class_entry *gstreamer_ce_GstObject;
extern zend_class_entry *gstreamer_ce_GstElement;
extern zend_class_entry *gstreamer_ce_GstBin;
extern zend_class_entry *gstreamer_ce_GstPipeline;
extern zend_class_entry *gstreamer_ce_GstBus;
extern zend_class_entry *gstreamer_ce_GstMessage;
extern zend_class_entry *gstreamer_ce_GstCaps;
extern zend_class_entry *gstreamer_ce_GstStructure;
extern zend_class_entry *gstreamer_ce_GstSample;
extern zend_class_entry *gstreamer_ce_GstBuffer;
extern zend_class_entry *gstreamer_ce_GstMapInfo;
extern zend_class_entry *gstreamer_ce_GstAppSink;
extern zend_class_entry *gstreamer_ce_GstVideoInfo;
extern zend_class_entry *gstreamer_ce_GstAudioInfo;
extern zend_class_entry *gstreamer_ce_GstDiscoverer;
extern zend_class_entry *gstreamer_ce_GstDiscovererInfo;
extern zend_class_entry *gstreamer_ce_GstDiscovererStreamInfo;
extern zend_class_entry *gstreamer_ce_GstDiscovererVideoInfo;
extern zend_class_entry *gstreamer_ce_GstDiscovererAudioInfo;

void gstreamer_register_gst(int module_number);
void gstreamer_register_app(int module_number);
void gstreamer_register_video(int module_number);
void gstreamer_register_audio(int module_number);
void gstreamer_register_pbutils(int module_number);

#endif

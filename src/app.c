/* gstreamer-app-1.0: appsink. */

#include "runtime.h"

#include "../stubs/app_arginfo.h"

zend_class_entry *gstreamer_ce_GstAppSink;

#define SINK(obj) ((GstAppSink *) gstreamer_ptr(obj))

PHP_FUNCTION(gst_app_sink_pull_sample)
{
	zend_object *appsink;

	ZEND_PARSE_PARAMETERS_START(1, 1)
		Z_PARAM_OBJ_OF_CLASS(appsink, gstreamer_ce_GstAppSink)
	ZEND_PARSE_PARAMETERS_END();

	gstreamer_box(return_value, gst_app_sink_pull_sample(SINK(appsink)), gstreamer_ce_GstSample);
	gstreamer_take(return_value);
}

PHP_FUNCTION(gst_app_sink_try_pull_sample)
{
	zend_object *appsink;
	zend_long timeout;

	ZEND_PARSE_PARAMETERS_START(2, 2)
		Z_PARAM_OBJ_OF_CLASS(appsink, gstreamer_ce_GstAppSink)
		Z_PARAM_LONG(timeout)
	ZEND_PARSE_PARAMETERS_END();

	gstreamer_box(return_value, gst_app_sink_try_pull_sample(SINK(appsink), (GstClockTime) timeout), gstreamer_ce_GstSample);
	gstreamer_take(return_value);
}

PHP_FUNCTION(gst_app_sink_is_eos)
{
	zend_object *appsink;

	ZEND_PARSE_PARAMETERS_START(1, 1)
		Z_PARAM_OBJ_OF_CLASS(appsink, gstreamer_ce_GstAppSink)
	ZEND_PARSE_PARAMETERS_END();

	RETURN_BOOL(gst_app_sink_is_eos(SINK(appsink)));
}

PHP_FUNCTION(gst_app_sink_set_caps)
{
	zend_object *appsink, *caps = NULL;

	ZEND_PARSE_PARAMETERS_START(2, 2)
		Z_PARAM_OBJ_OF_CLASS(appsink, gstreamer_ce_GstAppSink)
		Z_PARAM_OBJ_OF_CLASS_OR_NULL(caps, gstreamer_ce_GstCaps)
	ZEND_PARSE_PARAMETERS_END();

	gst_app_sink_set_caps(SINK(appsink), gstreamer_ptr_or_null(caps));
}

PHP_FUNCTION(gst_app_sink_set_max_buffers)
{
	zend_object *appsink;
	zend_long max;

	ZEND_PARSE_PARAMETERS_START(2, 2)
		Z_PARAM_OBJ_OF_CLASS(appsink, gstreamer_ce_GstAppSink)
		Z_PARAM_LONG(max)
	ZEND_PARSE_PARAMETERS_END();

	gst_app_sink_set_max_buffers(SINK(appsink), (guint) max);
}

PHP_FUNCTION(gst_app_sink_set_drop)
{
	zend_object *appsink;
	bool drop;

	ZEND_PARSE_PARAMETERS_START(2, 2)
		Z_PARAM_OBJ_OF_CLASS(appsink, gstreamer_ce_GstAppSink)
		Z_PARAM_BOOL(drop)
	ZEND_PARSE_PARAMETERS_END();

	gst_app_sink_set_drop(SINK(appsink), drop);
}

void gstreamer_register_app(int module_number)
{
	(void) module_number;
	zend_register_functions(NULL, ext_functions, NULL, MODULE_PERSISTENT);
	gstreamer_ce_GstAppSink = register_class_GstAppSink(gstreamer_ce_GstElement);
}

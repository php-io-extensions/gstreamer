/* This is a generated file, edit the .stub.php file instead.
 * Stub hash: 22ef81f528c0cb08f87eade87388f5cd7f8dda1f */

ZEND_BEGIN_ARG_WITH_RETURN_OBJ_INFO_EX(arginfo_gst_app_sink_pull_sample, 0, 1, GstSample, 1)
	ZEND_ARG_OBJ_INFO(0, appsink, GstAppSink, 0)
ZEND_END_ARG_INFO()

ZEND_BEGIN_ARG_WITH_RETURN_OBJ_INFO_EX(arginfo_gst_app_sink_try_pull_sample, 0, 2, GstSample, 1)
	ZEND_ARG_OBJ_INFO(0, appsink, GstAppSink, 0)
	ZEND_ARG_TYPE_INFO(0, timeout, IS_LONG, 0)
ZEND_END_ARG_INFO()

ZEND_BEGIN_ARG_WITH_RETURN_TYPE_INFO_EX(arginfo_gst_app_sink_is_eos, 0, 1, _IS_BOOL, 0)
	ZEND_ARG_OBJ_INFO(0, appsink, GstAppSink, 0)
ZEND_END_ARG_INFO()

ZEND_BEGIN_ARG_WITH_RETURN_TYPE_INFO_EX(arginfo_gst_app_sink_set_caps, 0, 2, IS_VOID, 0)
	ZEND_ARG_OBJ_INFO(0, appsink, GstAppSink, 0)
	ZEND_ARG_OBJ_INFO(0, caps, GstCaps, 1)
ZEND_END_ARG_INFO()

ZEND_BEGIN_ARG_WITH_RETURN_TYPE_INFO_EX(arginfo_gst_app_sink_set_max_buffers, 0, 2, IS_VOID, 0)
	ZEND_ARG_OBJ_INFO(0, appsink, GstAppSink, 0)
	ZEND_ARG_TYPE_INFO(0, max, IS_LONG, 0)
ZEND_END_ARG_INFO()

ZEND_BEGIN_ARG_WITH_RETURN_TYPE_INFO_EX(arginfo_gst_app_sink_set_drop, 0, 2, IS_VOID, 0)
	ZEND_ARG_OBJ_INFO(0, appsink, GstAppSink, 0)
	ZEND_ARG_TYPE_INFO(0, drop, _IS_BOOL, 0)
ZEND_END_ARG_INFO()

ZEND_FUNCTION(gst_app_sink_pull_sample);
ZEND_FUNCTION(gst_app_sink_try_pull_sample);
ZEND_FUNCTION(gst_app_sink_is_eos);
ZEND_FUNCTION(gst_app_sink_set_caps);
ZEND_FUNCTION(gst_app_sink_set_max_buffers);
ZEND_FUNCTION(gst_app_sink_set_drop);

static const zend_function_entry ext_functions[] = {
	ZEND_FE(gst_app_sink_pull_sample, arginfo_gst_app_sink_pull_sample)
	ZEND_FE(gst_app_sink_try_pull_sample, arginfo_gst_app_sink_try_pull_sample)
	ZEND_FE(gst_app_sink_is_eos, arginfo_gst_app_sink_is_eos)
	ZEND_FE(gst_app_sink_set_caps, arginfo_gst_app_sink_set_caps)
	ZEND_FE(gst_app_sink_set_max_buffers, arginfo_gst_app_sink_set_max_buffers)
	ZEND_FE(gst_app_sink_set_drop, arginfo_gst_app_sink_set_drop)
	ZEND_FE_END
};

static zend_class_entry *register_class_GstAppSink(zend_class_entry *class_entry_GstElement)
{
	zend_class_entry ce, *class_entry;

	INIT_CLASS_ENTRY(ce, "GstAppSink", NULL);
	class_entry = zend_register_internal_class_with_flags(&ce, class_entry_GstElement, ZEND_ACC_FINAL|ZEND_ACC_NOT_SERIALIZABLE);

	return class_entry;
}

/* This is a generated file, edit the .stub.php file instead.
 * Stub hash: cc749b40012ddb36b0cbd9b58e1ab13f606de96a */

ZEND_BEGIN_ARG_WITH_RETURN_OBJ_INFO_EX(arginfo_gst_discoverer_new, 0, 1, GstDiscoverer, 1)
	ZEND_ARG_TYPE_INFO(0, timeout, IS_LONG, 0)
ZEND_END_ARG_INFO()

ZEND_BEGIN_ARG_WITH_RETURN_OBJ_INFO_EX(arginfo_gst_discoverer_discover_uri, 0, 2, GstDiscovererInfo, 1)
	ZEND_ARG_OBJ_INFO(0, discoverer, GstDiscoverer, 0)
	ZEND_ARG_TYPE_INFO(0, uri, IS_STRING, 0)
ZEND_END_ARG_INFO()

ZEND_BEGIN_ARG_WITH_RETURN_TYPE_INFO_EX(arginfo_gst_discoverer_info_unref, 0, 1, IS_VOID, 0)
	ZEND_ARG_OBJ_INFO(0, info, GstDiscovererInfo, 0)
ZEND_END_ARG_INFO()

ZEND_BEGIN_ARG_WITH_RETURN_TYPE_INFO_EX(arginfo_gst_discoverer_info_get_result, 0, 1, IS_LONG, 0)
	ZEND_ARG_OBJ_INFO(0, info, GstDiscovererInfo, 0)
ZEND_END_ARG_INFO()

ZEND_BEGIN_ARG_WITH_RETURN_TYPE_INFO_EX(arginfo_gst_discoverer_info_get_uri, 0, 1, IS_STRING, 0)
	ZEND_ARG_OBJ_INFO(0, info, GstDiscovererInfo, 0)
ZEND_END_ARG_INFO()

#define arginfo_gst_discoverer_info_get_duration arginfo_gst_discoverer_info_get_result

ZEND_BEGIN_ARG_WITH_RETURN_TYPE_INFO_EX(arginfo_gst_discoverer_info_get_seekable, 0, 1, _IS_BOOL, 0)
	ZEND_ARG_OBJ_INFO(0, info, GstDiscovererInfo, 0)
ZEND_END_ARG_INFO()

ZEND_BEGIN_ARG_WITH_RETURN_TYPE_INFO_EX(arginfo_gst_discoverer_info_get_video_streams, 0, 1, IS_ARRAY, 0)
	ZEND_ARG_OBJ_INFO(0, info, GstDiscovererInfo, 0)
ZEND_END_ARG_INFO()

#define arginfo_gst_discoverer_info_get_audio_streams arginfo_gst_discoverer_info_get_video_streams

ZEND_BEGIN_ARG_WITH_RETURN_TYPE_INFO_EX(arginfo_gst_discoverer_stream_info_list_free, 0, 1, IS_VOID, 0)
	ZEND_ARG_TYPE_INFO(0, infos, IS_ARRAY, 0)
ZEND_END_ARG_INFO()

ZEND_BEGIN_ARG_WITH_RETURN_OBJ_INFO_EX(arginfo_gst_discoverer_stream_info_get_caps, 0, 1, GstCaps, 1)
	ZEND_ARG_OBJ_INFO(0, info, GstDiscovererStreamInfo, 0)
ZEND_END_ARG_INFO()

ZEND_BEGIN_ARG_WITH_RETURN_TYPE_INFO_EX(arginfo_gst_discoverer_stream_info_get_stream_id, 0, 1, IS_STRING, 1)
	ZEND_ARG_OBJ_INFO(0, info, GstDiscovererStreamInfo, 0)
ZEND_END_ARG_INFO()

ZEND_BEGIN_ARG_WITH_RETURN_TYPE_INFO_EX(arginfo_gst_discoverer_video_info_get_width, 0, 1, IS_LONG, 0)
	ZEND_ARG_OBJ_INFO(0, info, GstDiscovererVideoInfo, 0)
ZEND_END_ARG_INFO()

#define arginfo_gst_discoverer_video_info_get_height arginfo_gst_discoverer_video_info_get_width

#define arginfo_gst_discoverer_video_info_get_framerate_num arginfo_gst_discoverer_video_info_get_width

#define arginfo_gst_discoverer_video_info_get_framerate_denom arginfo_gst_discoverer_video_info_get_width

ZEND_BEGIN_ARG_WITH_RETURN_TYPE_INFO_EX(arginfo_gst_discoverer_audio_info_get_channels, 0, 1, IS_LONG, 0)
	ZEND_ARG_OBJ_INFO(0, info, GstDiscovererAudioInfo, 0)
ZEND_END_ARG_INFO()

#define arginfo_gst_discoverer_audio_info_get_sample_rate arginfo_gst_discoverer_audio_info_get_channels

#define arginfo_gst_discoverer_audio_info_get_bitrate arginfo_gst_discoverer_audio_info_get_channels

ZEND_BEGIN_ARG_INFO_EX(arginfo_class_GstDiscoverer___construct, 0, 0, 0)
ZEND_END_ARG_INFO()

ZEND_BEGIN_ARG_WITH_RETURN_TYPE_INFO_EX(arginfo_class_GstDiscoverer_pointer, 0, 0, IS_LONG, 0)
ZEND_END_ARG_INFO()

ZEND_BEGIN_ARG_WITH_RETURN_TYPE_INFO_EX(arginfo_class_GstDiscoverer_fromPointer, 0, 1, IS_STATIC, 1)
	ZEND_ARG_TYPE_INFO(0, pointer, IS_LONG, 0)
ZEND_END_ARG_INFO()

#define arginfo_class_GstDiscovererInfo___construct arginfo_class_GstDiscoverer___construct

#define arginfo_class_GstDiscovererInfo_pointer arginfo_class_GstDiscoverer_pointer

#define arginfo_class_GstDiscovererInfo_fromPointer arginfo_class_GstDiscoverer_fromPointer

#define arginfo_class_GstDiscovererStreamInfo___construct arginfo_class_GstDiscoverer___construct

#define arginfo_class_GstDiscovererStreamInfo_pointer arginfo_class_GstDiscoverer_pointer

#define arginfo_class_GstDiscovererStreamInfo_fromPointer arginfo_class_GstDiscoverer_fromPointer

ZEND_FUNCTION(gst_discoverer_new);
ZEND_FUNCTION(gst_discoverer_discover_uri);
ZEND_FUNCTION(gst_discoverer_info_unref);
ZEND_FUNCTION(gst_discoverer_info_get_result);
ZEND_FUNCTION(gst_discoverer_info_get_uri);
ZEND_FUNCTION(gst_discoverer_info_get_duration);
ZEND_FUNCTION(gst_discoverer_info_get_seekable);
ZEND_FUNCTION(gst_discoverer_info_get_video_streams);
ZEND_FUNCTION(gst_discoverer_info_get_audio_streams);
ZEND_FUNCTION(gst_discoverer_stream_info_list_free);
ZEND_FUNCTION(gst_discoverer_stream_info_get_caps);
ZEND_FUNCTION(gst_discoverer_stream_info_get_stream_id);
ZEND_FUNCTION(gst_discoverer_video_info_get_width);
ZEND_FUNCTION(gst_discoverer_video_info_get_height);
ZEND_FUNCTION(gst_discoverer_video_info_get_framerate_num);
ZEND_FUNCTION(gst_discoverer_video_info_get_framerate_denom);
ZEND_FUNCTION(gst_discoverer_audio_info_get_channels);
ZEND_FUNCTION(gst_discoverer_audio_info_get_sample_rate);
ZEND_FUNCTION(gst_discoverer_audio_info_get_bitrate);
ZEND_METHOD(GstDiscoverer, __construct);
ZEND_METHOD(GstDiscoverer, pointer);
ZEND_METHOD(GstDiscoverer, fromPointer);
ZEND_METHOD(GstDiscovererInfo, __construct);
ZEND_METHOD(GstDiscovererInfo, pointer);
ZEND_METHOD(GstDiscovererInfo, fromPointer);
ZEND_METHOD(GstDiscovererStreamInfo, __construct);
ZEND_METHOD(GstDiscovererStreamInfo, pointer);
ZEND_METHOD(GstDiscovererStreamInfo, fromPointer);

static const zend_function_entry ext_functions[] = {
	ZEND_FE(gst_discoverer_new, arginfo_gst_discoverer_new)
	ZEND_FE(gst_discoverer_discover_uri, arginfo_gst_discoverer_discover_uri)
	ZEND_FE(gst_discoverer_info_unref, arginfo_gst_discoverer_info_unref)
	ZEND_FE(gst_discoverer_info_get_result, arginfo_gst_discoverer_info_get_result)
	ZEND_FE(gst_discoverer_info_get_uri, arginfo_gst_discoverer_info_get_uri)
	ZEND_FE(gst_discoverer_info_get_duration, arginfo_gst_discoverer_info_get_duration)
	ZEND_FE(gst_discoverer_info_get_seekable, arginfo_gst_discoverer_info_get_seekable)
	ZEND_FE(gst_discoverer_info_get_video_streams, arginfo_gst_discoverer_info_get_video_streams)
	ZEND_FE(gst_discoverer_info_get_audio_streams, arginfo_gst_discoverer_info_get_audio_streams)
	ZEND_FE(gst_discoverer_stream_info_list_free, arginfo_gst_discoverer_stream_info_list_free)
	ZEND_FE(gst_discoverer_stream_info_get_caps, arginfo_gst_discoverer_stream_info_get_caps)
	ZEND_FE(gst_discoverer_stream_info_get_stream_id, arginfo_gst_discoverer_stream_info_get_stream_id)
	ZEND_FE(gst_discoverer_video_info_get_width, arginfo_gst_discoverer_video_info_get_width)
	ZEND_FE(gst_discoverer_video_info_get_height, arginfo_gst_discoverer_video_info_get_height)
	ZEND_FE(gst_discoverer_video_info_get_framerate_num, arginfo_gst_discoverer_video_info_get_framerate_num)
	ZEND_FE(gst_discoverer_video_info_get_framerate_denom, arginfo_gst_discoverer_video_info_get_framerate_denom)
	ZEND_FE(gst_discoverer_audio_info_get_channels, arginfo_gst_discoverer_audio_info_get_channels)
	ZEND_FE(gst_discoverer_audio_info_get_sample_rate, arginfo_gst_discoverer_audio_info_get_sample_rate)
	ZEND_FE(gst_discoverer_audio_info_get_bitrate, arginfo_gst_discoverer_audio_info_get_bitrate)
	ZEND_FE_END
};

static const zend_function_entry class_GstDiscoverer_methods[] = {
	ZEND_ME(GstDiscoverer, __construct, arginfo_class_GstDiscoverer___construct, ZEND_ACC_PRIVATE)
	ZEND_ME(GstDiscoverer, pointer, arginfo_class_GstDiscoverer_pointer, ZEND_ACC_PUBLIC)
	ZEND_ME(GstDiscoverer, fromPointer, arginfo_class_GstDiscoverer_fromPointer, ZEND_ACC_PUBLIC|ZEND_ACC_STATIC)
	ZEND_FE_END
};

static const zend_function_entry class_GstDiscovererInfo_methods[] = {
	ZEND_ME(GstDiscovererInfo, __construct, arginfo_class_GstDiscovererInfo___construct, ZEND_ACC_PRIVATE)
	ZEND_ME(GstDiscovererInfo, pointer, arginfo_class_GstDiscovererInfo_pointer, ZEND_ACC_PUBLIC)
	ZEND_ME(GstDiscovererInfo, fromPointer, arginfo_class_GstDiscovererInfo_fromPointer, ZEND_ACC_PUBLIC|ZEND_ACC_STATIC)
	ZEND_FE_END
};

static const zend_function_entry class_GstDiscovererStreamInfo_methods[] = {
	ZEND_ME(GstDiscovererStreamInfo, __construct, arginfo_class_GstDiscovererStreamInfo___construct, ZEND_ACC_PRIVATE)
	ZEND_ME(GstDiscovererStreamInfo, pointer, arginfo_class_GstDiscovererStreamInfo_pointer, ZEND_ACC_PUBLIC)
	ZEND_ME(GstDiscovererStreamInfo, fromPointer, arginfo_class_GstDiscovererStreamInfo_fromPointer, ZEND_ACC_PUBLIC|ZEND_ACC_STATIC)
	ZEND_FE_END
};

static void register_pbutils_symbols(int module_number)
{
	REGISTER_LONG_CONSTANT("GST_DISCOVERER_OK", GST_DISCOVERER_OK, CONST_PERSISTENT);
	REGISTER_LONG_CONSTANT("GST_DISCOVERER_URI_INVALID", GST_DISCOVERER_URI_INVALID, CONST_PERSISTENT);
	REGISTER_LONG_CONSTANT("GST_DISCOVERER_ERROR", GST_DISCOVERER_ERROR, CONST_PERSISTENT);
	REGISTER_LONG_CONSTANT("GST_DISCOVERER_TIMEOUT", GST_DISCOVERER_TIMEOUT, CONST_PERSISTENT);
	REGISTER_LONG_CONSTANT("GST_DISCOVERER_BUSY", GST_DISCOVERER_BUSY, CONST_PERSISTENT);
	REGISTER_LONG_CONSTANT("GST_DISCOVERER_MISSING_PLUGINS", GST_DISCOVERER_MISSING_PLUGINS, CONST_PERSISTENT);
}

static zend_class_entry *register_class_GstDiscoverer(void)
{
	zend_class_entry ce, *class_entry;

	INIT_CLASS_ENTRY(ce, "GstDiscoverer", class_GstDiscoverer_methods);
	class_entry = zend_register_internal_class_with_flags(&ce, NULL, ZEND_ACC_FINAL|ZEND_ACC_NOT_SERIALIZABLE);

	return class_entry;
}

static zend_class_entry *register_class_GstDiscovererInfo(void)
{
	zend_class_entry ce, *class_entry;

	INIT_CLASS_ENTRY(ce, "GstDiscovererInfo", class_GstDiscovererInfo_methods);
	class_entry = zend_register_internal_class_with_flags(&ce, NULL, ZEND_ACC_FINAL|ZEND_ACC_NOT_SERIALIZABLE);

	return class_entry;
}

static zend_class_entry *register_class_GstDiscovererStreamInfo(void)
{
	zend_class_entry ce, *class_entry;

	INIT_CLASS_ENTRY(ce, "GstDiscovererStreamInfo", class_GstDiscovererStreamInfo_methods);
	class_entry = zend_register_internal_class_with_flags(&ce, NULL, ZEND_ACC_NOT_SERIALIZABLE);

	return class_entry;
}

static zend_class_entry *register_class_GstDiscovererVideoInfo(zend_class_entry *class_entry_GstDiscovererStreamInfo)
{
	zend_class_entry ce, *class_entry;

	INIT_CLASS_ENTRY(ce, "GstDiscovererVideoInfo", NULL);
	class_entry = zend_register_internal_class_with_flags(&ce, class_entry_GstDiscovererStreamInfo, ZEND_ACC_FINAL|ZEND_ACC_NOT_SERIALIZABLE);

	return class_entry;
}

static zend_class_entry *register_class_GstDiscovererAudioInfo(zend_class_entry *class_entry_GstDiscovererStreamInfo)
{
	zend_class_entry ce, *class_entry;

	INIT_CLASS_ENTRY(ce, "GstDiscovererAudioInfo", NULL);
	class_entry = zend_register_internal_class_with_flags(&ce, class_entry_GstDiscovererStreamInfo, ZEND_ACC_FINAL|ZEND_ACC_NOT_SERIALIZABLE);

	return class_entry;
}

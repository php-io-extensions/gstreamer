/* gstreamer-pbutils-1.0: discoverer. */

#include "runtime.h"

#include "../stubs/pbutils_arginfo.h"

zend_class_entry *gstreamer_ce_GstDiscoverer;
zend_class_entry *gstreamer_ce_GstDiscovererInfo;
zend_class_entry *gstreamer_ce_GstDiscovererStreamInfo;
zend_class_entry *gstreamer_ce_GstDiscovererVideoInfo;
zend_class_entry *gstreamer_ce_GstDiscovererAudioInfo;

GSTREAMER_HANDLE_METHODS(GstDiscoverer)
GSTREAMER_HANDLE_METHODS(GstDiscovererInfo)
GSTREAMER_HANDLE_METHODS(GstDiscovererStreamInfo)

#define P(obj) gstreamer_ptr(obj)

PHP_FUNCTION(gst_discoverer_new)
{
	zend_long timeout;
	GError *error = NULL;
	GstDiscoverer *discoverer;

	ZEND_PARSE_PARAMETERS_START(1, 1)
		Z_PARAM_LONG(timeout)
	ZEND_PARSE_PARAMETERS_END();

	discoverer = gst_discoverer_new((GstClockTime) timeout, &error);
	if (error != NULL) {
		if (discoverer != NULL) {
			g_object_unref(discoverer);
		}
		gstreamer_throw_gerror(error);
		g_error_free(error);
		RETURN_THROWS();
	}
	gstreamer_box_gobject(return_value, discoverer);
	gstreamer_take(return_value);
}

PHP_FUNCTION(gst_discoverer_discover_uri)
{
	zend_object *discoverer;
	zend_string *uri;
	GError *error = NULL;
	GstDiscovererInfo *info;

	ZEND_PARSE_PARAMETERS_START(2, 2)
		Z_PARAM_OBJ_OF_CLASS(discoverer, gstreamer_ce_GstDiscoverer)
		Z_PARAM_STR(uri)
	ZEND_PARSE_PARAMETERS_END();

	info = gst_discoverer_discover_uri(P(discoverer), ZSTR_VAL(uri), &error);
	if (error != NULL) {
		/* The info that may come with the error is replaced by the thrown GError, so it is unreffed here. */
		if (info != NULL) {
			gst_discoverer_info_unref(info);
		}
		gstreamer_throw_gerror(error);
		g_error_free(error);
		RETURN_THROWS();
	}
	gstreamer_box_gobject(return_value, info);
	gstreamer_take(return_value);
}

PHP_FUNCTION(gst_discoverer_info_unref)
{
	zend_object *info;

	ZEND_PARSE_PARAMETERS_START(1, 1)
		Z_PARAM_OBJ_OF_CLASS(info, gstreamer_ce_GstDiscovererInfo)
	ZEND_PARSE_PARAMETERS_END();

	gst_discoverer_info_unref(P(info));
	gstreamer_unref(info);
}

PHP_FUNCTION(gst_discoverer_info_get_result)
{
	zend_object *info;

	ZEND_PARSE_PARAMETERS_START(1, 1)
		Z_PARAM_OBJ_OF_CLASS(info, gstreamer_ce_GstDiscovererInfo)
	ZEND_PARSE_PARAMETERS_END();

	RETURN_LONG(gst_discoverer_info_get_result(P(info)));
}

PHP_FUNCTION(gst_discoverer_info_get_uri)
{
	zend_object *info;

	ZEND_PARSE_PARAMETERS_START(1, 1)
		Z_PARAM_OBJ_OF_CLASS(info, gstreamer_ce_GstDiscovererInfo)
	ZEND_PARSE_PARAMETERS_END();

	gstreamer_return_string(return_value, gst_discoverer_info_get_uri(P(info)));
}

PHP_FUNCTION(gst_discoverer_info_get_duration)
{
	zend_object *info;

	ZEND_PARSE_PARAMETERS_START(1, 1)
		Z_PARAM_OBJ_OF_CLASS(info, gstreamer_ce_GstDiscovererInfo)
	ZEND_PARSE_PARAMETERS_END();

	RETURN_LONG((zend_long) gst_discoverer_info_get_duration(P(info)));
}

PHP_FUNCTION(gst_discoverer_info_get_seekable)
{
	zend_object *info;

	ZEND_PARSE_PARAMETERS_START(1, 1)
		Z_PARAM_OBJ_OF_CLASS(info, gstreamer_ce_GstDiscovererInfo)
	ZEND_PARSE_PARAMETERS_END();

	RETURN_BOOL(gst_discoverer_info_get_seekable(P(info)));
}

/* A transfer-full GList of stream infos: each one boxed with its reference, the list nodes freed. */
static void gstreamer_stream_list(zval *rv, GList *list)
{
	GList *l;

	array_init(rv);
	for (l = list; l != NULL; l = l->next) {
		zval item;

		gstreamer_box_gobject(&item, l->data);
		gstreamer_take(&item);
		add_next_index_zval(rv, &item);
	}
	g_list_free(list);
}

PHP_FUNCTION(gst_discoverer_info_get_video_streams)
{
	zend_object *info;

	ZEND_PARSE_PARAMETERS_START(1, 1)
		Z_PARAM_OBJ_OF_CLASS(info, gstreamer_ce_GstDiscovererInfo)
	ZEND_PARSE_PARAMETERS_END();

	gstreamer_stream_list(return_value, gst_discoverer_info_get_video_streams(P(info)));
}

PHP_FUNCTION(gst_discoverer_info_get_audio_streams)
{
	zend_object *info;

	ZEND_PARSE_PARAMETERS_START(1, 1)
		Z_PARAM_OBJ_OF_CLASS(info, gstreamer_ce_GstDiscovererInfo)
	ZEND_PARSE_PARAMETERS_END();

	gstreamer_stream_list(return_value, gst_discoverer_info_get_audio_streams(P(info)));
}

PHP_FUNCTION(gst_discoverer_stream_info_list_free)
{
	HashTable *infos;
	GList *list = NULL;
	zval *zv;

	ZEND_PARSE_PARAMETERS_START(1, 1)
		Z_PARAM_ARRAY_HT(infos)
	ZEND_PARSE_PARAMETERS_END();

	ZEND_HASH_REVERSE_FOREACH_VAL(infos, zv) {
		if (Z_TYPE_P(zv) == IS_OBJECT && instanceof_function(Z_OBJCE_P(zv), gstreamer_ce_GstDiscovererStreamInfo)) {
			list = g_list_prepend(list, P(Z_OBJ_P(zv)));
		}
	} ZEND_HASH_FOREACH_END();

	gst_discoverer_stream_info_list_free(list);

	ZEND_HASH_FOREACH_VAL(infos, zv) {
		if (Z_TYPE_P(zv) == IS_OBJECT && instanceof_function(Z_OBJCE_P(zv), gstreamer_ce_GstDiscovererStreamInfo)) {
			gstreamer_unref(Z_OBJ_P(zv));
		}
	} ZEND_HASH_FOREACH_END();
}

PHP_FUNCTION(gst_discoverer_stream_info_get_caps)
{
	zend_object *info;

	ZEND_PARSE_PARAMETERS_START(1, 1)
		Z_PARAM_OBJ_OF_CLASS(info, gstreamer_ce_GstDiscovererStreamInfo)
	ZEND_PARSE_PARAMETERS_END();

	gstreamer_box(return_value, gst_discoverer_stream_info_get_caps(P(info)), gstreamer_ce_GstCaps);
	gstreamer_take(return_value);
}

PHP_FUNCTION(gst_discoverer_stream_info_get_stream_id)
{
	zend_object *info;

	ZEND_PARSE_PARAMETERS_START(1, 1)
		Z_PARAM_OBJ_OF_CLASS(info, gstreamer_ce_GstDiscovererStreamInfo)
	ZEND_PARSE_PARAMETERS_END();

	gstreamer_return_string(return_value, gst_discoverer_stream_info_get_stream_id(P(info)));
}

PHP_FUNCTION(gst_discoverer_video_info_get_width)
{
	zend_object *info;

	ZEND_PARSE_PARAMETERS_START(1, 1)
		Z_PARAM_OBJ_OF_CLASS(info, gstreamer_ce_GstDiscovererVideoInfo)
	ZEND_PARSE_PARAMETERS_END();

	RETURN_LONG(gst_discoverer_video_info_get_width(P(info)));
}

PHP_FUNCTION(gst_discoverer_video_info_get_height)
{
	zend_object *info;

	ZEND_PARSE_PARAMETERS_START(1, 1)
		Z_PARAM_OBJ_OF_CLASS(info, gstreamer_ce_GstDiscovererVideoInfo)
	ZEND_PARSE_PARAMETERS_END();

	RETURN_LONG(gst_discoverer_video_info_get_height(P(info)));
}

PHP_FUNCTION(gst_discoverer_video_info_get_framerate_num)
{
	zend_object *info;

	ZEND_PARSE_PARAMETERS_START(1, 1)
		Z_PARAM_OBJ_OF_CLASS(info, gstreamer_ce_GstDiscovererVideoInfo)
	ZEND_PARSE_PARAMETERS_END();

	RETURN_LONG(gst_discoverer_video_info_get_framerate_num(P(info)));
}

PHP_FUNCTION(gst_discoverer_video_info_get_framerate_denom)
{
	zend_object *info;

	ZEND_PARSE_PARAMETERS_START(1, 1)
		Z_PARAM_OBJ_OF_CLASS(info, gstreamer_ce_GstDiscovererVideoInfo)
	ZEND_PARSE_PARAMETERS_END();

	RETURN_LONG(gst_discoverer_video_info_get_framerate_denom(P(info)));
}

PHP_FUNCTION(gst_discoverer_audio_info_get_channels)
{
	zend_object *info;

	ZEND_PARSE_PARAMETERS_START(1, 1)
		Z_PARAM_OBJ_OF_CLASS(info, gstreamer_ce_GstDiscovererAudioInfo)
	ZEND_PARSE_PARAMETERS_END();

	RETURN_LONG(gst_discoverer_audio_info_get_channels(P(info)));
}

PHP_FUNCTION(gst_discoverer_audio_info_get_sample_rate)
{
	zend_object *info;

	ZEND_PARSE_PARAMETERS_START(1, 1)
		Z_PARAM_OBJ_OF_CLASS(info, gstreamer_ce_GstDiscovererAudioInfo)
	ZEND_PARSE_PARAMETERS_END();

	RETURN_LONG(gst_discoverer_audio_info_get_sample_rate(P(info)));
}

PHP_FUNCTION(gst_discoverer_audio_info_get_bitrate)
{
	zend_object *info;

	ZEND_PARSE_PARAMETERS_START(1, 1)
		Z_PARAM_OBJ_OF_CLASS(info, gstreamer_ce_GstDiscovererAudioInfo)
	ZEND_PARSE_PARAMETERS_END();

	RETURN_LONG(gst_discoverer_audio_info_get_bitrate(P(info)));
}

void gstreamer_register_pbutils(int module_number)
{
	zend_register_functions(NULL, ext_functions, NULL, MODULE_PERSISTENT);
	register_pbutils_symbols(module_number);
	gstreamer_ce_GstDiscoverer = register_class_GstDiscoverer();
	gstreamer_handle_setup(gstreamer_ce_GstDiscoverer);
	gstreamer_ce_GstDiscovererInfo = register_class_GstDiscovererInfo();
	gstreamer_handle_setup(gstreamer_ce_GstDiscovererInfo);
	gstreamer_ce_GstDiscovererStreamInfo = register_class_GstDiscovererStreamInfo();
	gstreamer_handle_setup(gstreamer_ce_GstDiscovererStreamInfo);
	gstreamer_ce_GstDiscovererVideoInfo = register_class_GstDiscovererVideoInfo(gstreamer_ce_GstDiscovererStreamInfo);
	gstreamer_ce_GstDiscovererAudioInfo = register_class_GstDiscovererAudioInfo(gstreamer_ce_GstDiscovererStreamInfo);
}

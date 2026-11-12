/* gstreamer-video-1.0: video info, video formats. */

#include "runtime.h"

#define zim_GstVideoInfo_finfo gstreamer_field
#define zim_GstVideoInfo_interlace_mode gstreamer_field
#define zim_GstVideoInfo_flags gstreamer_field
#define zim_GstVideoInfo_width gstreamer_field
#define zim_GstVideoInfo_height gstreamer_field
#define zim_GstVideoInfo_size gstreamer_field
#define zim_GstVideoInfo_views gstreamer_field
#define zim_GstVideoInfo_fps_n gstreamer_field
#define zim_GstVideoInfo_fps_d gstreamer_field
#define zim_GstVideoInfo_par_n gstreamer_field
#define zim_GstVideoInfo_par_d gstreamer_field
#define zim_GstVideoInfo_stride gstreamer_field
#define zim_GstVideoInfo_offset gstreamer_field

#include "../stubs/video_arginfo.h"

zend_class_entry *gstreamer_ce_GstVideoInfo;

GSTREAMER_HANDLE_METHODS(GstVideoInfo)

PHP_FUNCTION(gst_video_info_new)
{
	ZEND_PARSE_PARAMETERS_NONE();

	gstreamer_box(return_value, gst_video_info_new(), gstreamer_ce_GstVideoInfo);
	gstreamer_take(return_value);
}

PHP_FUNCTION(gst_video_info_free)
{
	zend_object *info;

	ZEND_PARSE_PARAMETERS_START(1, 1)
		Z_PARAM_OBJ_OF_CLASS(info, gstreamer_ce_GstVideoInfo)
	ZEND_PARSE_PARAMETERS_END();

	gst_video_info_free(gstreamer_ptr(info));
	gstreamer_release(info);
}

PHP_FUNCTION(gst_video_info_from_caps)
{
	zend_object *info, *caps;

	ZEND_PARSE_PARAMETERS_START(2, 2)
		Z_PARAM_OBJ_OF_CLASS(info, gstreamer_ce_GstVideoInfo)
		Z_PARAM_OBJ_OF_CLASS(caps, gstreamer_ce_GstCaps)
	ZEND_PARSE_PARAMETERS_END();

	RETURN_BOOL(gst_video_info_from_caps(gstreamer_ptr(info), gstreamer_ptr(caps)));
}

PHP_FUNCTION(gst_video_format_to_string)
{
	zend_long format;

	ZEND_PARSE_PARAMETERS_START(1, 1)
		Z_PARAM_LONG(format)
	ZEND_PARSE_PARAMETERS_END();

	gstreamer_return_string(return_value, gst_video_format_to_string((GstVideoFormat) format));
}

PHP_FUNCTION(gst_video_format_from_string)
{
	zend_string *format;

	ZEND_PARSE_PARAMETERS_START(1, 1)
		Z_PARAM_STR(format)
	ZEND_PARSE_PARAMETERS_END();

	RETURN_LONG(gst_video_format_from_string(ZSTR_VAL(format)));
}

void gstreamer_register_video(int module_number)
{
	zend_register_functions(NULL, ext_functions, NULL, MODULE_PERSISTENT);
	register_video_symbols(module_number);
	gstreamer_ce_GstVideoInfo = register_class_GstVideoInfo();
	gstreamer_handle_setup(gstreamer_ce_GstVideoInfo);
}

/* gstreamer-audio-1.0: audio info, audio formats. */

#include "runtime.h"

#define zim_GstAudioInfo_finfo gstreamer_field
#define zim_GstAudioInfo_flags gstreamer_field
#define zim_GstAudioInfo_layout gstreamer_field
#define zim_GstAudioInfo_rate gstreamer_field
#define zim_GstAudioInfo_channels gstreamer_field
#define zim_GstAudioInfo_bpf gstreamer_field

#include "../stubs/audio_arginfo.h"

zend_class_entry *gstreamer_ce_GstAudioInfo;

GSTREAMER_HANDLE_METHODS(GstAudioInfo)

PHP_FUNCTION(gst_audio_info_new)
{
	ZEND_PARSE_PARAMETERS_NONE();

	gstreamer_box(return_value, gst_audio_info_new(), gstreamer_ce_GstAudioInfo);
	gstreamer_take(return_value);
}

PHP_FUNCTION(gst_audio_info_free)
{
	zend_object *info;

	ZEND_PARSE_PARAMETERS_START(1, 1)
		Z_PARAM_OBJ_OF_CLASS(info, gstreamer_ce_GstAudioInfo)
	ZEND_PARSE_PARAMETERS_END();

	gst_audio_info_free(gstreamer_ptr(info));
	gstreamer_release(info);
}

PHP_FUNCTION(gst_audio_info_from_caps)
{
	zend_object *info, *caps;

	ZEND_PARSE_PARAMETERS_START(2, 2)
		Z_PARAM_OBJ_OF_CLASS(info, gstreamer_ce_GstAudioInfo)
		Z_PARAM_OBJ_OF_CLASS(caps, gstreamer_ce_GstCaps)
	ZEND_PARSE_PARAMETERS_END();

	RETURN_BOOL(gst_audio_info_from_caps(gstreamer_ptr(info), gstreamer_ptr(caps)));
}

PHP_FUNCTION(gst_audio_format_to_string)
{
	zend_long format;

	ZEND_PARSE_PARAMETERS_START(1, 1)
		Z_PARAM_LONG(format)
	ZEND_PARSE_PARAMETERS_END();

	gstreamer_return_string(return_value, gst_audio_format_to_string((GstAudioFormat) format));
}

PHP_FUNCTION(gst_audio_format_from_string)
{
	zend_string *format;

	ZEND_PARSE_PARAMETERS_START(1, 1)
		Z_PARAM_STR(format)
	ZEND_PARSE_PARAMETERS_END();

	RETURN_LONG(gst_audio_format_from_string(ZSTR_VAL(format)));
}

void gstreamer_register_audio(int module_number)
{
	zend_register_functions(NULL, ext_functions, NULL, MODULE_PERSISTENT);
	register_audio_symbols(module_number);
	gstreamer_ce_GstAudioInfo = register_class_GstAudioInfo();
	gstreamer_handle_setup(gstreamer_ce_GstAudioInfo);
}

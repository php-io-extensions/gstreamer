/*
 * gstreamer: 1:1 bindings of GStreamer 1.26 (gstreamer, gstreamer-app,
 * gstreamer-video, gstreamer-audio, gstreamer-pbutils). Function and constant
 * names are the C names. Only functions the 1.26 headers declare are bound.
 */

#include "runtime.h"
#include "ext/standard/info.h"

ZEND_DECLARE_MODULE_GLOBALS(gstreamer)

static PHP_GINIT_FUNCTION(gstreamer)
{
#if defined(COMPILE_DL_GSTREAMER) && defined(ZTS)
	ZEND_TSRMLS_CACHE_UPDATE();
#endif
	zend_hash_init(&gstreamer_globals->boxes, 64, NULL, NULL, 1);
}

static PHP_GSHUTDOWN_FUNCTION(gstreamer)
{
	zend_hash_destroy(&gstreamer_globals->boxes);
}

PHP_MINIT_FUNCTION(gstreamer)
{
	gstreamer_register_gst(module_number);
	gstreamer_register_app(module_number);
	gstreamer_register_video(module_number);
	gstreamer_register_audio(module_number);
	gstreamer_register_pbutils(module_number);
#ifdef GSTREAMER_PROBES
	REGISTER_BOOL_CONSTANT("GSTREAMER_PROBES", true, CONST_PERSISTENT);
#endif

	return SUCCESS;
}

PHP_RINIT_FUNCTION(gstreamer)
{
#if defined(COMPILE_DL_GSTREAMER) && defined(ZTS)
	ZEND_TSRMLS_CACHE_UPDATE();
#endif
	return SUCCESS;
}

PHP_MINFO_FUNCTION(gstreamer)
{
	gchar *version = gst_version_string();

	php_info_print_table_start();
	php_info_print_table_row(2, "gstreamer support", "enabled");
	php_info_print_table_row(2, "Version", PHP_GSTREAMER_VERSION);
	php_info_print_table_row(2, "GStreamer", version);
	php_info_print_table_end();
	g_free(version);
}

zend_module_entry gstreamer_module_entry = {
	STANDARD_MODULE_HEADER,
	"gstreamer",
	NULL,
	PHP_MINIT(gstreamer),
	NULL,
	PHP_RINIT(gstreamer),
	NULL,
	PHP_MINFO(gstreamer),
	PHP_GSTREAMER_VERSION,
	PHP_MODULE_GLOBALS(gstreamer),
	PHP_GINIT(gstreamer),
	PHP_GSHUTDOWN(gstreamer),
	NULL,
	STANDARD_MODULE_PROPERTIES_EX
};

#ifdef COMPILE_DL_GSTREAMER
# ifdef ZTS
ZEND_TSRMLS_CACHE_DEFINE()
# endif
ZEND_GET_MODULE(gstreamer)
#endif

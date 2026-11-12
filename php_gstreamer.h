#ifndef PHP_GSTREAMER_H
#define PHP_GSTREAMER_H

extern zend_module_entry gstreamer_module_entry;
#define phpext_gstreamer_ptr &gstreamer_module_entry

#define PHP_GSTREAMER_VERSION "0.11.0"

#if defined(ZTS) && defined(COMPILE_DL_GSTREAMER)
ZEND_TSRMLS_CACHE_EXTERN()
#endif

#endif

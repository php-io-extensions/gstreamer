PHP_ARG_ENABLE([gstreamer],
  [whether to enable gstreamer support],
  [AS_HELP_STRING([--enable-gstreamer], [Enable the GStreamer 1.26 bindings (gstreamer, gstreamer-app, gstreamer-video, gstreamer-audio, gstreamer-pbutils)])],
  [no])

PHP_ARG_ENABLE([gstreamer-probes],
  [whether to build the gstreamer probe switch],
  [AS_HELP_STRING([--enable-gstreamer-probes],
    [Build the GSTREAMER_PROBE_OFF switch that tests/Probes drives: env GSTREAMER_PROBE_OFF=<site id> turns that kept refusal off. Never for a release build])],
  [no],
  [no])

if test "$PHP_GSTREAMER" != "no"; then
  if test "$PHP_GSTREAMER_PROBES" != "no"; then
    AC_DEFINE([GSTREAMER_PROBES], [1], [Kept refusal sites can be turned off through env GSTREAMER_PROBE_OFF])
  fi

  dnl macOS: Homebrew's gstreamer, which shares Homebrew's GLib with the other extensions. The official
  dnl GStreamer.framework SDK carries its own GLib: two GLibs in one PHP crash (ext-gtk), so it is not searched.
  dnl The floor is GStreamer 1.26.2 (Debian trixie on the Pi); the API bound is 1.26's.
  PKG_CHECK_MODULES([GSTREAMER], [gstreamer-1.0 >= 1.26.2 gstreamer-app-1.0 >= 1.26.2 gstreamer-video-1.0 >= 1.26.2 gstreamer-audio-1.0 >= 1.26.2 gstreamer-pbutils-1.0 >= 1.26.2])
  PHP_EVAL_INCLINE([$GSTREAMER_CFLAGS])
  PHP_EVAL_LIBLINE([$GSTREAMER_LIBS], [GSTREAMER_SHARED_LIBADD])
  PHP_SUBST([GSTREAMER_SHARED_LIBADD])

  PHP_NEW_EXTENSION([gstreamer],
    [src/gstreamer.c src/runtime.c src/fields.c src/gst.c src/app.c src/video.c src/audio.c src/pbutils.c],
    [$ext_shared],, [-DZEND_ENABLE_STATIC_TSRMLS_CACHE=1])
  PHP_ADD_BUILD_DIR([$ext_builddir/src])
fi

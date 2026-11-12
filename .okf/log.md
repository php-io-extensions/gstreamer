# Log

## 2026-11-11

* **Pi 5** (Debian 13.7, GStreamer 1.26.2, PHP 8.4.27 ZTS): `install-debian-trixie.sh` clean (no warnings), installed; Pest 29 passed, 2 skipped (probes, release build); probe build `tests/Probes` 2 passed. Mac (Homebrew 1.28.9) NTS and ZTS: 29 passed, 2 skipped; probe builds 2 passed. Not run: CI on GitHub (no remote).
* **Docs, support list, CI.** README, AGENTS, SECURITY, `.okf`, `scripts/support.php` (81 / 2702 counted functions of GStreamer 1.26.2; `gst_discoverer_info_unref` is a macro, listed apart), CI (macOS 15 Homebrew; `debian:trixie`).
* **Homebrew GStreamer, `GstError`, `GstObject` as top class.** Under `zhp` the GStreamer.framework SDK's own GLib crashed next to ext-gtk; ext-gtk also owns the PHP classes `GError` and `GObject`, so gstreamer's registrations of them failed. Build against Homebrew GStreamer; the exception is `GstError`; no `GObject` class; `GObject *` / `gpointer` parameters take any bound GObject class (`gstreamer_gobject_arg`, marshal).
* **Kept refusal `gst-field-released`** in `gstreamer_field` (`src/fields.c`), probe `tests/Probes/FieldReleasedTest.php` (SIGSEGV with the site off). Dropped after probes: released handle into GStreamer, call before init, bad or double unmap.
* **The 82 functions** over five modules, the handle classes, 257 enum members both 1.26 and 1.28 declare, `GstMapInfo`, the GError translation.
* **Build skeleton**: `config.m4` against GStreamer ≥ 1.26.2, version-only module (0.11.0).

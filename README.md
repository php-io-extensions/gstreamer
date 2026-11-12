# gstreamer

[![CI](https://img.shields.io/github/actions/workflow/status/php-io-extensions/gstreamer/ci.yml?style=flat-square&label=CI)](https://github.com/php-io-extensions/gstreamer/actions/workflows/ci.yml)
[![GStreamer API](https://img.shields.io/badge/GStreamer_API-3.0%25_%2881%2F2702%29-blue?style=flat-square)](SUPPORT.md)

1:1 PHP bindings of GStreamer: gstreamer, gstreamer-app, gstreamer-video, gstreamer-audio and gstreamer-pbutils. Version 0.11.0. Linux and macOS.

The extension builds against GStreamer 1.26.2 or newer and binds only functions GStreamer 1.26 declares. Function and constant names are the C names. It covers what ext-ffmpeg does: open a source, read its streams, decode, convert pixels and resample audio, seek, and hand raw frames to PHP.

## Requirements

- GStreamer 1.26.2 or newer, with gst-plugins-base and gst-plugins-good
- PHP 8.4, NTS or ZTS
- macOS: `brew install gstreamer`. Not the GStreamer.framework SDK from gstreamer.freedesktop.org: it carries its own GLib, and a second GLib in PHP crashes next to ext-gtk.
- Debian trixie and Raspberry Pi OS: `apt install libgstreamer1.0-dev libgstreamer-plugins-base1.0-dev gstreamer1.0-plugins-good`

## Install

macOS, into Homebrew `php@8.4` and `php@8.4-zts`:

```bash
./install-macos.sh
```

Debian trixie and Raspberry Pi OS, into the PHP on `PATH`:

```bash
./install-debian-trixie.sh
```

`php --ri gstreamer` shows the extension's version and GStreamer's.

## Basic usage

Decode a file to 320 × 240 RGBA frames and read each frame's bytes:

```php
$argv = null;
gst_init_check($argv);

$pipeline = gst_parse_launch('uridecodebin uri=file:///path/clip.mp4 ! videoconvert ! videoscale ! video/x-raw,format=RGBA,width=320,height=240 ! appsink name=sink');
$sink = gst_bin_get_by_name($pipeline, 'sink');
gst_element_set_state($pipeline, GST_STATE_PLAYING);

while (($sample = gst_app_sink_pull_sample($sink)) !== null) {
    $buffer = gst_sample_get_buffer($sample);
    $map = new GstMapInfo();
    if (gst_buffer_map($buffer, $map, GST_MAP_READ)) {
        $rgba = $map->data;            // 320 * 240 * 4 bytes
        $pts = $buffer->pts();         // nanoseconds
        gst_buffer_unmap($buffer, $map);
    }
    gst_sample_unref($sample);
}

gst_element_set_state($pipeline, GST_STATE_NULL);
gst_object_unref($sink);
gst_object_unref($pipeline);
```

Read the streams first with the discoverer:

```php
$discoverer = gst_discoverer_new(5 * GST_SECOND);
$info = gst_discoverer_discover_uri($discoverer, 'file:///path/clip.mp4');
$duration = gst_discoverer_info_get_duration($info);
foreach (gst_discoverer_info_get_video_streams($info) as $video) {
    echo gst_discoverer_video_info_get_width($video), '×', gst_discoverer_video_info_get_height($video), "\n";
}
```

A handle is one PHP object per native pointer. Dropping it does not unref the native object: `gst_object_unref`, `gst_*_unref` and `gst_*_free` do. A returned object has the most derived bound class it is (`gst_parse_launch` gives a `GstPipeline`, `gst_bin_get_by_name` an appsink as `GstAppSink`). Fields are methods named as the C fields (`$message->type()`, `$buffer->pts()`, `$info->width()`). A GError GStreamer reports is thrown as `GstError` after the call.

## Coverage

[SUPPORT.md](SUPPORT.md) lists every counted function, bound or not. `php84 scripts/support.php` writes it and the badge.

## License

The extension is MIT. GStreamer is LGPL 2.1 or later.

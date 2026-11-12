<?php

declare(strict_types=1);

require_once __DIR__ . '/../scripts/support.php';

it('counts GST_*_API exports and static inline definitions, once each', function (): void {
    $header = "#define GST_X 1\n"
        . "/** gst_fake (void) in a comment */\n"
        . "GST_API\nGstElement * gst_bin_get_by_name (GstBin *bin, const gchar *name);\n"
        . "GST_APP_API\nGstSample * gst_app_sink_pull_sample (GstAppSink *appsink);\n"
        . "GST_VIDEO_API\ngboolean gst_video_info_from_caps (GstVideoInfo *info, const GstCaps * caps) G_GNUC_WARN_UNUSED_RESULT;\n"
        . "static inline void\ngst_caps_unref (GstCaps * caps)\n{\n  gst_mini_object_unref (GST_MINI_OBJECT_CAST (caps));\n}\n"
        . "GST_API\nGstElement * gst_bin_get_by_name (GstBin *bin, const gchar *name);\n";

    expect(support_header_functions($header))
        ->toBe(['gst_app_sink_pull_sample', 'gst_bin_get_by_name', 'gst_caps_unref', 'gst_video_info_from_caps']);
});

it('does not count macros, typedefs, struct fields or functions without an export', function (): void {
    $header = "#define gst_discoverer_info_unref(info) (g_object_unref((GObject*)info))\n"
        . "typedef gboolean (*GstBusFunc) (GstBus * bus, GstMessage * message, gpointer user_data);\n"
        . "struct _GstBinClass {\n  gboolean (*add_element) (GstBin *bin, GstElement *element);\n};\n"
        . "void gst_internal_helper (void);\n"
        . "GST_API_IMPORT const gchar * gst_imported (void);\n";

    expect(support_header_functions($header))->toBe([]);
});

it('keeps only headers that export something', function (): void {
    expect(support_counted(['gst/gstbin.h' => "GST_API\nGstElement * gst_bin_new (const gchar *name);\n", 'gst/gstmacros.h' => "#define GST_X 1\n"]))
        ->toBe(['gst/gstbin.h' => ['gst_bin_new']]);
});

it('renders one line per function and lists the bindings that match none', function (): void {
    $md = support_render(['gst/gstbin.h' => ['gst_bin_add', 'gst_bin_new']], ['gst_bin_add' => true, 'gst_discoverer_info_unref' => true], '2026-11-11');

    expect($md)->toContain('- [x] `gst_bin_add`')
        ->toContain('- [ ] `gst_bin_new`')
        ->toContain('## gst/gstbin.h (1 / 2)')
        ->toContain('GStreamer 1.26.2 — 1 / 2 members bound (50.0%) — 2026-11-11')
        ->toContain('- `gst_discoverer_info_unref`');
});

it('computes the badge from the counts', function (): void {
    expect(support_badge(81, 2702))
        ->toBe('[![GStreamer API](https://img.shields.io/badge/GStreamer_API-3.0%25_%2881%2F2702%29-blue?style=flat-square)](SUPPORT.md)');
});

it('compares a support list without its date', function (): void {
    expect(support_same("GStreamer — 2 / 4 members bound (50.0%) — 2026-11-11\n", "GStreamer — 2 / 4 members bound (50.0%) — 2026-11-12\n"))->toBeTrue()
        ->and(support_same("GStreamer — 2 / 4 members bound (50.0%) — 2026-11-11\n", "GStreamer — 3 / 4 members bound (75.0%) — 2026-11-11\n"))->toBeFalse();
});

it('finds SUPPORT.md and the badge current', function (): void {
    exec(escapeshellarg(PHP_BINARY) . ' ' . escapeshellarg(__DIR__ . '/../scripts/support.php') . ' --check', $out, $code);

    expect($code)->toBe(0)
        ->and(implode("\n", $out))->toBe('SUPPORT.md and the badge are current.');
});

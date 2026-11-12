<?php

declare(strict_types=1);

it('pulls RGBA frames through videoconvert into appsink', function (): void {
    $pipeline = gst_parse_launch('videotestsrc num-buffers=3 ! video/x-raw,width=64,height=48 ! videoconvert ! video/x-raw,format=RGBA ! appsink name=sink');
    $sink = gst_bin_get_by_name($pipeline, 'sink');
    expect($pipeline)->toBeInstanceOf(GstPipeline::class)
        ->and($sink)->toBeInstanceOf(GstAppSink::class)
        ->and(gst_object_get_name($sink))->toBe('sink');

    gst_element_set_state($pipeline, GST_STATE_PLAYING);
    $frames = 0;
    while (($sample = gst_app_sink_pull_sample($sink)) !== null) {
        if ($frames === 0) {
            $info = gst_video_info_new();
            expect(gst_video_info_from_caps($info, gst_sample_get_caps($sample)))->toBeTrue()
                ->and([$info->width(), $info->height(), $info->finfo()])->toBe([64, 48, GST_VIDEO_FORMAT_RGBA])
                ->and($info->stride())->toBe([256, 0, 0, 0])
                ->and($info->size())->toBe(64 * 48 * 4);
            gst_video_info_free($info);

            $buffer = gst_sample_get_buffer($sample);
            expect(gst_buffer_get_size($buffer))->toBe(12288)
                ->and($buffer->pts())->toBe(0);

            $map = new GstMapInfo();
            expect(gst_buffer_map($buffer, $map, GST_MAP_READ))->toBeTrue()
                ->and(strlen($map->data))->toBe(12288)
                ->and($map->size)->toBe(12288);
            gst_buffer_unmap($buffer, $map);

            expect(gst_buffer_extract($buffer, 0, $bytes, 16))->toBe(16)
                ->and($bytes)->toBe(substr($map->data, 0, 16));
        }
        gst_sample_unref($sample);
        $frames++;
    }

    expect($frames)->toBe(3)
        ->and(gst_app_sink_is_eos($sink))->toBeTrue();

    gst_element_set_state($pipeline, GST_STATE_NULL);
    gst_object_unref($sink);
    gst_object_unref($pipeline);
});

it('negotiates the caps set on the appsink', function (): void {
    $pipeline = gst_parse_launch('videotestsrc num-buffers=1 ! videoconvert ! appsink name=sink');
    $sink = gst_bin_get_by_name($pipeline, 'sink');
    $caps = gst_caps_from_string('video/x-raw,format=GRAY8,width=16,height=16');
    gst_app_sink_set_caps($sink, $caps);
    gst_caps_unref($caps);

    gst_element_set_state($pipeline, GST_STATE_PLAYING);
    $sample = gst_app_sink_pull_sample($sink);
    expect(gst_buffer_get_size(gst_sample_get_buffer($sample)))->toBe(256);

    gst_sample_unref($sample);
    gst_element_set_state($pipeline, GST_STATE_NULL);
    gst_object_unref($sink);
    gst_object_unref($pipeline);
});

it('names video formats both ways', function (): void {
    expect(gst_video_format_to_string(GST_VIDEO_FORMAT_I420))->toBe('I420')
        ->and(gst_video_format_from_string('NV12'))->toBe(GST_VIDEO_FORMAT_NV12)
        ->and(gst_video_format_from_string('nonsense'))->toBe(GST_VIDEO_FORMAT_UNKNOWN);
});

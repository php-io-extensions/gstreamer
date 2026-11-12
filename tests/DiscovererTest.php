<?php

declare(strict_types=1);

it('discovers a WAV: result, duration, its one audio stream', function (): void {
    $uri = 'file://'.wavFixture();
    $discoverer = gst_discoverer_new(5 * GST_SECOND);
    $info = gst_discoverer_discover_uri($discoverer, $uri);

    expect(gst_discoverer_info_get_result($info))->toBe(GST_DISCOVERER_OK)
        ->and(gst_discoverer_info_get_uri($info))->toBe($uri)
        ->and(gst_discoverer_info_get_duration($info))->toBeGreaterThan(0)
        ->and(gst_discoverer_info_get_seekable($info))->toBeTrue()
        ->and(gst_discoverer_info_get_video_streams($info))->toBe([]);

    $streams = gst_discoverer_info_get_audio_streams($info);
    expect($streams)->toHaveCount(1)
        ->and($streams[0])->toBeInstanceOf(GstDiscovererAudioInfo::class)
        ->and(gst_discoverer_audio_info_get_channels($streams[0]))->toBe(1)
        ->and(gst_discoverer_audio_info_get_sample_rate($streams[0]))->toBe(44100)
        ->and(gst_discoverer_audio_info_get_bitrate($streams[0]))->toBeGreaterThanOrEqual(0)
        ->and(gst_discoverer_stream_info_get_stream_id($streams[0]))->toBeString();

    $caps = gst_discoverer_stream_info_get_caps($streams[0]);
    expect(gst_caps_to_string($caps))->toBe('audio/x-wav');
    gst_caps_unref($caps);

    gst_discoverer_stream_info_list_free($streams);
    expect($streams[0]->pointer())->toBe(0);

    gst_discoverer_info_unref($info);
    gst_object_unref($discoverer);
});

it('discovers a video stream\'s size and frame rate', function (): void {
    $path = sys_get_temp_dir().'/ext-gstreamer-'.getmypid().'.avi';
    $pipeline = gst_parse_launch("videotestsrc num-buffers=5 ! video/x-raw,width=32,height=24,framerate=25/1 ! jpegenc ! avimux ! filesink location=$path");
    $message = runToEnd($pipeline);
    gst_message_unref($message);
    gst_element_set_state($pipeline, GST_STATE_NULL);
    gst_object_unref($pipeline);

    $discoverer = gst_discoverer_new(5 * GST_SECOND);
    $info = gst_discoverer_discover_uri($discoverer, "file://$path");
    $streams = gst_discoverer_info_get_video_streams($info);

    expect($streams)->toHaveCount(1)
        ->and(gst_discoverer_video_info_get_width($streams[0]))->toBe(32)
        ->and(gst_discoverer_video_info_get_height($streams[0]))->toBe(24)
        ->and(gst_discoverer_video_info_get_framerate_num($streams[0]))->toBe(25)
        ->and(gst_discoverer_video_info_get_framerate_denom($streams[0]))->toBe(1);

    gst_discoverer_stream_info_list_free($streams);
    gst_discoverer_info_unref($info);
    gst_object_unref($discoverer);
    unlink($path);
});

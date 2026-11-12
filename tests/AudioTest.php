<?php

declare(strict_types=1);

it('resamples to S16LE 48 kHz stereo through a pipeline built element by element', function (): void {
    $pipeline = gst_pipeline_new('audio');
    $src = gst_element_factory_make('audiotestsrc', null);
    $convert = gst_element_factory_make('audioconvert', null);
    $resample = gst_element_factory_make('audioresample', null);
    $sink = gst_element_factory_make('appsink', null);
    gst_util_set_object_arg($src, 'num-buffers', '2');
    foreach ([$src, $convert, $resample, $sink] as $element) {
        expect(gst_bin_add($pipeline, $element))->toBeTrue();
    }

    $caps = gst_caps_from_string('audio/x-raw,format=S16LE,rate=48000,channels=2,layout=interleaved');
    expect(gst_element_link($src, $convert))->toBeTrue()
        ->and(gst_element_link($convert, $resample))->toBeTrue()
        ->and(gst_element_link_filtered($resample, $sink, $caps))->toBeTrue();
    gst_caps_unref($caps);
    gst_app_sink_set_max_buffers($sink, 4);
    gst_app_sink_set_drop($sink, false);

    gst_element_set_state($pipeline, GST_STATE_PLAYING);
    $sample = gst_app_sink_try_pull_sample($sink, 5 * GST_SECOND);
    $info = gst_audio_info_new();

    expect($sample)->toBeInstanceOf(GstSample::class)
        ->and(gst_audio_info_from_caps($info, gst_sample_get_caps($sample)))->toBeTrue()
        ->and([$info->finfo(), $info->rate(), $info->channels(), $info->bpf()])->toBe([GST_AUDIO_FORMAT_S16LE, 48000, 2, 4]);

    gst_audio_info_free($info);
    gst_sample_unref($sample);
    gst_element_set_state($pipeline, GST_STATE_NULL);
    gst_object_unref($pipeline);
});

it('names audio formats both ways', function (): void {
    expect(gst_audio_format_to_string(GST_AUDIO_FORMAT_F32LE))->toBe('F32LE')
        ->and(gst_audio_format_from_string('S16LE'))->toBe(GST_AUDIO_FORMAT_S16LE);
});

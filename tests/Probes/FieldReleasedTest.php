<?php

declare(strict_types=1);

// Site gst-field-released (outcome 1): the handle classes' field getters read the struct themselves, not
// through a GStreamer call. A released handle's pointer is NULL, which the getter would dereference.

beforeEach(fn () => requireProbeBuild());

it('refuses a field of a freed video info, which the getter reads through NULL (SIGSEGV) without the refusal', function (): void {
    $code = <<<'PHP'
        $info = gst_video_info_new();
        gst_video_info_free($info);
        $info->width();
    PHP;

    $kept = gstreamerProbe($code, null);
    $off = gstreamerProbe($code, 'gst-field-released');

    expect($kept['signal'])->toBeNull()
        ->and($kept['stdout'])->toContain('REFUSED ValueError: GstVideoInfo has been released')
        ->and($off['signal'])->toBeIn([PROBE_SIGSEGV, PROBE_SIGBUS]);
});

it('refuses the source of an unreffed message, which the getter reads through NULL (SIGSEGV) without the refusal', function (): void {
    $code = <<<'PHP'
        $pipeline = gst_parse_launch('fakesrc num-buffers=1 ! fakesink');
        gst_element_set_state($pipeline, GST_STATE_PLAYING);
        $bus = gst_element_get_bus($pipeline);
        $message = gst_bus_timed_pop_filtered($bus, 5 * GST_SECOND, GST_MESSAGE_EOS);
        gst_message_unref($message);
        $message->src();
    PHP;

    $kept = gstreamerProbe($code, null);
    $off = gstreamerProbe($code, 'gst-field-released');

    expect($kept['signal'])->toBeNull()
        ->and($kept['stdout'])->toContain('REFUSED ValueError: GstMessage has been released')
        ->and($off['signal'])->toBeIn([PROBE_SIGSEGV, PROBE_SIGBUS]);
});

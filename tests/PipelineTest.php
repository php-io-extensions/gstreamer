<?php

declare(strict_types=1);

it('throws the GError gst_parse_launch reports', function (): void {
    expect(fn () => gst_parse_launch('no_such_element_xyz'))->toThrow(GstError::class);
});

it('reports EOS on the bus, from the pipeline', function (): void {
    $pipeline = gst_parse_launch('fakesrc num-buffers=1 ! fakesink');
    $message = runToEnd($pipeline);

    expect($message->type())->toBe(GST_MESSAGE_EOS)
        ->and(gst_message_type_get_name($message->type()))->toBe('eos')
        ->and($message->src())->toBe($pipeline);

    gst_message_unref($message);
    gst_element_set_state($pipeline, GST_STATE_NULL);
    gst_object_unref($pipeline);
});

it('parses a state change from the bus', function (): void {
    $pipeline = gst_parse_launch('fakesrc num-buffers=1 ! fakesink');
    gst_element_set_state($pipeline, GST_STATE_READY);
    $bus = gst_element_get_bus($pipeline);
    $message = gst_bus_timed_pop_filtered($bus, 5 * GST_SECOND, GST_MESSAGE_STATE_CHANGED);
    gst_message_parse_state_changed($message, $old, $new, $pending);

    expect([$old, $new, $pending])->toBe([GST_STATE_NULL, GST_STATE_READY, GST_STATE_VOID_PENDING]);

    gst_message_unref($message);
    gst_object_unref($bus);
    gst_element_set_state($pipeline, GST_STATE_NULL);
    gst_object_unref($pipeline);
});

it('throws the GError of a bus error message, after filling debug', function (): void {
    $pipeline = gst_parse_launch('filesrc location=/nonexistent/file ! fakesink');
    $message = runToEnd($pipeline);
    expect($message->type())->toBe(GST_MESSAGE_ERROR);

    $debug = null;
    try {
        gst_message_parse_error($message, $debug);
        $thrown = null;
    } catch (GstError $e) {
        $thrown = $e;
    }

    expect($thrown?->domain)->toBe('gst-resource-error-quark')
        ->and($debug)->toBeString();

    gst_message_unref($message);
    gst_element_set_state($pipeline, GST_STATE_NULL);
    gst_object_unref($pipeline);
});

it('reads state changes, duration and position, and seeks', function (): void {
    $pipeline = gst_parse_launch('filesrc location='.wavFixture().' ! wavparse ! fakesink');
    gst_element_set_state($pipeline, GST_STATE_PAUSED);

    expect(gst_element_get_state($pipeline, $state, $pending, 5 * GST_SECOND))->toBe(GST_STATE_CHANGE_SUCCESS)
        ->and($state)->toBe(GST_STATE_PAUSED)
        ->and(gst_element_state_get_name($state))->toBe('PAUSED')
        ->and(gst_element_state_change_return_get_name(GST_STATE_CHANGE_ASYNC))->toBe('ASYNC')
        ->and(gst_element_query_duration($pipeline, GST_FORMAT_TIME, $duration))->toBeTrue()
        ->and($duration)->toBeGreaterThan(0)
        ->and(gst_element_seek_simple($pipeline, GST_FORMAT_TIME, GST_SEEK_FLAG_FLUSH | GST_SEEK_FLAG_KEY_UNIT, intdiv($duration, 2)))->toBeTrue();

    gst_element_get_state($pipeline, $state, $pending, 5 * GST_SECOND);
    expect(gst_element_query_position($pipeline, GST_FORMAT_TIME, $position))->toBeTrue()
        ->and($position)->toBeGreaterThanOrEqual(0)
        ->and(gst_format_get_name(GST_FORMAT_TIME))->toBe('time');

    gst_element_set_state($pipeline, GST_STATE_NULL);
    gst_object_unref($pipeline);
});

it('reads caps and their structures', function (): void {
    $caps = gst_caps_from_string('video/x-raw,width=320,framerate=30/1');
    $structure = gst_caps_get_structure($caps, 0);

    expect(gst_caps_get_size($caps))->toBe(1)
        ->and(gst_structure_get_name($structure))->toBe('video/x-raw')
        ->and(gst_structure_get_int($structure, 'width', $width))->toBeTrue()
        ->and($width)->toBe(320)
        ->and(gst_structure_get_fraction($structure, 'framerate', $n, $d))->toBeTrue()
        ->and([$n, $d])->toBe([30, 1])
        ->and(gst_caps_to_string($caps))->toContain('video/x-raw')
        ->and(gst_structure_to_string($structure))->toContain('width=(int)320');

    gst_caps_unref($caps);
});

it('unlinks and removes elements', function (): void {
    $bin = gst_pipeline_new(null);
    $a = gst_element_factory_make('fakesrc', null);
    $b = gst_element_factory_make('fakesink', null);
    gst_bin_add($bin, $a);
    gst_bin_add($bin, $b);
    gst_element_link($a, $b);
    gst_element_unlink($a, $b);

    expect(gst_bin_remove($bin, $b))->toBeTrue()
        ->and($b->pointer())->toBe(0)
        ->and(gst_object_ref($a))->toBe($a);

    gst_object_unref($a);
    gst_object_unref($bin);
});

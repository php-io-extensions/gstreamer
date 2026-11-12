<?php

declare(strict_types=1);

it('reports its version and GStreamer\'s', function (): void {
    gst_version($major, $minor, $micro, $nano);

    expect(phpversion('gstreamer'))->toBe('0.11.0')
        ->and(gst_version_string())->toBe("GStreamer $major.$minor.$micro")
        ->and([$major, $minor])->toBe([GST_VERSION_MAJOR, GST_VERSION_MINOR]);
});

it('takes its own options out of argv on the first gst_init_check', function (): void {
    // This process initialized GStreamer in tests/Pest.php, after which argv is left alone: a fresh child shows the first call.
    $so = getenv('GSTREAMER_SO') ?: ini_get('extension_dir').'/gstreamer.so';
    $code = '$argv = ["app", "--gst-debug-level=0", "keep"]; var_export([gst_init_check($argv), $argv]);';
    $out = shell_exec(escapeshellarg(PHP_BINARY).' -n -d extension='.escapeshellarg($so).' -r '.escapeshellarg($code));

    expect($out)->toBe("array (\n  0 => true,\n  1 => \n  array (\n    0 => 'app',\n    1 => 'keep',\n  ),\n)");
});

it('leaves argv alone once GStreamer is initialized', function (): void {
    $argv = ['app', '--gst-debug-level=0'];

    expect(gst_init_check($argv))->toBeTrue()
        ->and($argv)->toBe(['app', '--gst-debug-level=0']);
});

it('mirrors the GObject hierarchy', function (): void {
    expect(is_subclass_of(GstPipeline::class, GstBin::class))->toBeTrue()
        ->and(is_subclass_of(GstBin::class, GstElement::class))->toBeTrue()
        ->and(is_subclass_of(GstElement::class, GstObject::class))->toBeTrue()
        ->and(get_parent_class(GstObject::class))->toBeFalse()
        ->and(is_subclass_of(GstAppSink::class, GstElement::class))->toBeTrue()
        ->and(is_subclass_of(GstBus::class, GstObject::class))->toBeTrue()
        ->and(is_subclass_of(GstDiscovererAudioInfo::class, GstDiscovererStreamInfo::class))->toBeTrue()
        ->and(is_subclass_of(GstError::class, RuntimeException::class))->toBeTrue();
});

it('declares no class ext-gtk owns', function (): void {
    foreach (['GObject', 'GError'] as $name) {
        expect(class_exists($name) ? (new ReflectionClass($name))->getExtensionName() : null)->not->toBe('gstreamer');
    }
});

it('takes only bound GObject handles where C takes a GObject or gpointer', function (): void {
    expect(fn () => gst_object_unref(new stdClass()))->toThrow(TypeError::class, 'must be of type GstObject|GstDiscoverer|GstDiscovererInfo|GstDiscovererStreamInfo, stdClass given');
});

it('has the C enum values', function (): void {
    expect(GST_STATE_PLAYING)->toBe(4)
        ->and(GST_MESSAGE_EOS)->toBe(1)
        ->and(GST_SECOND)->toBe(1_000_000_000)
        ->and(GST_CLOCK_TIME_NONE)->toBe(-1)
        ->and(GST_VIDEO_FORMAT_RGBA)->toBe(11)
        ->and(GST_AUDIO_FORMAT_S16LE)->toBe(4)
        ->and(GST_DISCOVERER_MISSING_PLUGINS)->toBe(5);
});

it('keeps handles private, unique and address-backed', function (): void {
    $pipeline = gst_pipeline_new('p');

    expect(fn () => new GstElement())->toThrow(Error::class)
        ->and(GstPipeline::fromPointer(0))->toBeNull()
        ->and(GstPipeline::fromPointer($pipeline->pointer()))->toBe($pipeline);

    gst_object_unref($pipeline);
    expect($pipeline->pointer())->toBe(0);
});

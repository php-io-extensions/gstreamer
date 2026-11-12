<?php

declare(strict_types=1);

if (! extension_loaded('gstreamer')) {
    throw new RuntimeException('The gstreamer extension is not loaded; run ./install-macos.sh or ./install-debian-trixie.sh');
}

$argv0 = null;
gst_init_check($argv0) || throw new RuntimeException('gst_init_check failed');

/** Plays $pipeline to EOS or ERROR (5 s at most) and answers that message, or null on timeout. */
function runToEnd(GstElement $pipeline): ?GstMessage
{
    gst_element_set_state($pipeline, GST_STATE_PLAYING);
    $bus = gst_element_get_bus($pipeline);
    $message = gst_bus_timed_pop_filtered($bus, 5 * GST_SECOND, GST_MESSAGE_EOS | GST_MESSAGE_ERROR);
    gst_object_unref($bus);

    return $message;
}

/** A mono 44.1 kHz WAV of $buffers test-tone buffers, written by GStreamer into the temp directory and deleted when the run ends. */
function wavFixture(int $buffers = 20): string
{
    $path = sys_get_temp_dir().'/ext-gstreamer-'.getmypid().'-'.$buffers.'.wav';
    if (! is_file($path)) {
        register_shutdown_function(static fn () => @unlink($path));
        $pipeline = gst_parse_launch("audiotestsrc num-buffers=$buffers ! audio/x-raw,rate=44100,channels=1 ! wavenc ! filesink location=$path");
        $message = runToEnd($pipeline);
        ($message !== null && $message->type() === GST_MESSAGE_EOS) || throw new RuntimeException('writing the WAV fixture failed');
        gst_message_unref($message);
        gst_element_set_state($pipeline, GST_STATE_NULL);
        gst_object_unref($pipeline);
    }

    return $path;
}

/** macOS signal numbers a kept refusal's probe dies by. */
const PROBE_SIGBUS = 10;
const PROBE_SIGSEGV = 11;

/** Skips a tests/Probes test unless the loaded ext-gstreamer is a probe build (--enable-gstreamer-probes). */
function requireProbeBuild(): void
{
    if (! defined('GSTREAMER_PROBES')) {
        test()->markTestSkipped('ext-gstreamer is not a probe build (configure --enable-gstreamer-probes): GSTREAMER_PROBES is undefined');
    }
}

/**
 * Runs $code in a child of this PHP with only ext-gstreamer loaded (from GSTREAMER_SO when set), after
 * gst_init_check. $siteOff names the kept site GSTREAMER_PROBE_OFF turns off, null keeps every site.
 *
 * @return array{signal: ?int, stdout: string}
 */
function gstreamerProbe(string $code, ?string $siteOff): array
{
    $script = "<?php\ndeclare(strict_types=1);\n\$argv0 = null;\ngst_init_check(\$argv0);\ntry {\n".$code."\n} catch (Throwable \$t) {\n    echo 'REFUSED ', get_class(\$t), ': ', \$t->getMessage(), \"\\n\";\n}\necho \"SURVIVED\\n\";\n";
    $file = tempnam(sys_get_temp_dir(), 'gstreamer-probe');
    file_put_contents($file, $script);

    $env = getenv();
    unset($env['GSTREAMER_PROBE_OFF']);
    $env['XDEBUG_MODE'] = 'off';
    if ($siteOff !== null) {
        $env['GSTREAMER_PROBE_OFF'] = $siteOff;
    }

    $so = getenv('GSTREAMER_SO') ?: ini_get('extension_dir').'/gstreamer.so';
    $command = [PHP_BINARY, '-n', '-d', 'memory_limit=128M', '-d', 'extension='.$so, $file];
    $process = proc_open($command, [0 => ['file', '/dev/null', 'r'], 1 => ['pipe', 'w'], 2 => ['file', '/dev/null', 'w']], $pipes, null, $env);
    $stdout = (string) stream_get_contents($pipes[1]);
    fclose($pipes[1]);
    do {
        $status = proc_get_status($process);
        if ($status['running']) {
            usleep(20_000);
        }
    } while ($status['running']);
    proc_close($process);
    @unlink($file);

    return ['signal' => $status['signaled'] ? $status['termsig'] : null, 'stdout' => $stdout];
}

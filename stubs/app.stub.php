<?php

/** @generate-class-entries */

/** @not-serializable */
final class GstAppSink extends GstElement
{
}

function gst_app_sink_pull_sample(GstAppSink $appsink): ?GstSample {}

function gst_app_sink_try_pull_sample(GstAppSink $appsink, int $timeout): ?GstSample {}

function gst_app_sink_is_eos(GstAppSink $appsink): bool {}

function gst_app_sink_set_caps(GstAppSink $appsink, ?GstCaps $caps): void {}

function gst_app_sink_set_max_buffers(GstAppSink $appsink, int $max): void {}

function gst_app_sink_set_drop(GstAppSink $appsink, bool $drop): void {}

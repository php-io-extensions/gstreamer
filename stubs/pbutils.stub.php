<?php

/** @generate-class-entries */

/** @var int
 * @cvalue GST_DISCOVERER_OK */
const GST_DISCOVERER_OK = UNKNOWN;
/** @var int
 * @cvalue GST_DISCOVERER_URI_INVALID */
const GST_DISCOVERER_URI_INVALID = UNKNOWN;
/** @var int
 * @cvalue GST_DISCOVERER_ERROR */
const GST_DISCOVERER_ERROR = UNKNOWN;
/** @var int
 * @cvalue GST_DISCOVERER_TIMEOUT */
const GST_DISCOVERER_TIMEOUT = UNKNOWN;
/** @var int
 * @cvalue GST_DISCOVERER_BUSY */
const GST_DISCOVERER_BUSY = UNKNOWN;
/** @var int
 * @cvalue GST_DISCOVERER_MISSING_PLUGINS */
const GST_DISCOVERER_MISSING_PLUGINS = UNKNOWN;

/** @not-serializable */
final class GstDiscoverer
{
    private function __construct() {}

    public function pointer(): int {}

    public static function fromPointer(int $pointer): ?static {}
}

/** @not-serializable */
final class GstDiscovererInfo
{
    private function __construct() {}

    public function pointer(): int {}

    public static function fromPointer(int $pointer): ?static {}
}

/** @not-serializable */
class GstDiscovererStreamInfo
{
    private function __construct() {}

    public function pointer(): int {}

    public static function fromPointer(int $pointer): ?static {}
}

/** @not-serializable */
final class GstDiscovererVideoInfo extends GstDiscovererStreamInfo
{
}

/** @not-serializable */
final class GstDiscovererAudioInfo extends GstDiscovererStreamInfo
{
}

/** @throws GstError */
function gst_discoverer_new(int $timeout): ?GstDiscoverer {}

/** @throws GstError */
function gst_discoverer_discover_uri(GstDiscoverer $discoverer, string $uri): ?GstDiscovererInfo {}

function gst_discoverer_info_unref(GstDiscovererInfo $info): void {}

function gst_discoverer_info_get_result(GstDiscovererInfo $info): int {}

function gst_discoverer_info_get_uri(GstDiscovererInfo $info): string {}

function gst_discoverer_info_get_duration(GstDiscovererInfo $info): int {}

function gst_discoverer_info_get_seekable(GstDiscovererInfo $info): bool {}

/** @return list<GstDiscovererStreamInfo> */
function gst_discoverer_info_get_video_streams(GstDiscovererInfo $info): array {}

/** @return list<GstDiscovererStreamInfo> */
function gst_discoverer_info_get_audio_streams(GstDiscovererInfo $info): array {}

/** infos is a list from gst_discoverer_info_get_video_streams() or gst_discoverer_info_get_audio_streams(). */
function gst_discoverer_stream_info_list_free(array $infos): void {}

function gst_discoverer_stream_info_get_caps(GstDiscovererStreamInfo $info): ?GstCaps {}

function gst_discoverer_stream_info_get_stream_id(GstDiscovererStreamInfo $info): ?string {}

function gst_discoverer_video_info_get_width(GstDiscovererVideoInfo $info): int {}

function gst_discoverer_video_info_get_height(GstDiscovererVideoInfo $info): int {}

function gst_discoverer_video_info_get_framerate_num(GstDiscovererVideoInfo $info): int {}

function gst_discoverer_video_info_get_framerate_denom(GstDiscovererVideoInfo $info): int {}

function gst_discoverer_audio_info_get_channels(GstDiscovererAudioInfo $info): int {}

function gst_discoverer_audio_info_get_sample_rate(GstDiscovererAudioInfo $info): int {}

function gst_discoverer_audio_info_get_bitrate(GstDiscovererAudioInfo $info): int {}

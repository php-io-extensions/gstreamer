<?php

/** @generate-class-entries */

/** @var int
 * @cvalue GST_AUDIO_FORMAT_UNKNOWN */
const GST_AUDIO_FORMAT_UNKNOWN = UNKNOWN;
/** @var int
 * @cvalue GST_AUDIO_FORMAT_ENCODED */
const GST_AUDIO_FORMAT_ENCODED = UNKNOWN;
/** @var int
 * @cvalue GST_AUDIO_FORMAT_S8 */
const GST_AUDIO_FORMAT_S8 = UNKNOWN;
/** @var int
 * @cvalue GST_AUDIO_FORMAT_U8 */
const GST_AUDIO_FORMAT_U8 = UNKNOWN;
/** @var int
 * @cvalue GST_AUDIO_FORMAT_S16LE */
const GST_AUDIO_FORMAT_S16LE = UNKNOWN;
/** @var int
 * @cvalue GST_AUDIO_FORMAT_S16BE */
const GST_AUDIO_FORMAT_S16BE = UNKNOWN;
/** @var int
 * @cvalue GST_AUDIO_FORMAT_U16LE */
const GST_AUDIO_FORMAT_U16LE = UNKNOWN;
/** @var int
 * @cvalue GST_AUDIO_FORMAT_U16BE */
const GST_AUDIO_FORMAT_U16BE = UNKNOWN;
/** @var int
 * @cvalue GST_AUDIO_FORMAT_S24_32LE */
const GST_AUDIO_FORMAT_S24_32LE = UNKNOWN;
/** @var int
 * @cvalue GST_AUDIO_FORMAT_S24_32BE */
const GST_AUDIO_FORMAT_S24_32BE = UNKNOWN;
/** @var int
 * @cvalue GST_AUDIO_FORMAT_U24_32LE */
const GST_AUDIO_FORMAT_U24_32LE = UNKNOWN;
/** @var int
 * @cvalue GST_AUDIO_FORMAT_U24_32BE */
const GST_AUDIO_FORMAT_U24_32BE = UNKNOWN;
/** @var int
 * @cvalue GST_AUDIO_FORMAT_S32LE */
const GST_AUDIO_FORMAT_S32LE = UNKNOWN;
/** @var int
 * @cvalue GST_AUDIO_FORMAT_S32BE */
const GST_AUDIO_FORMAT_S32BE = UNKNOWN;
/** @var int
 * @cvalue GST_AUDIO_FORMAT_U32LE */
const GST_AUDIO_FORMAT_U32LE = UNKNOWN;
/** @var int
 * @cvalue GST_AUDIO_FORMAT_U32BE */
const GST_AUDIO_FORMAT_U32BE = UNKNOWN;
/** @var int
 * @cvalue GST_AUDIO_FORMAT_S24LE */
const GST_AUDIO_FORMAT_S24LE = UNKNOWN;
/** @var int
 * @cvalue GST_AUDIO_FORMAT_S24BE */
const GST_AUDIO_FORMAT_S24BE = UNKNOWN;
/** @var int
 * @cvalue GST_AUDIO_FORMAT_U24LE */
const GST_AUDIO_FORMAT_U24LE = UNKNOWN;
/** @var int
 * @cvalue GST_AUDIO_FORMAT_U24BE */
const GST_AUDIO_FORMAT_U24BE = UNKNOWN;
/** @var int
 * @cvalue GST_AUDIO_FORMAT_S20LE */
const GST_AUDIO_FORMAT_S20LE = UNKNOWN;
/** @var int
 * @cvalue GST_AUDIO_FORMAT_S20BE */
const GST_AUDIO_FORMAT_S20BE = UNKNOWN;
/** @var int
 * @cvalue GST_AUDIO_FORMAT_U20LE */
const GST_AUDIO_FORMAT_U20LE = UNKNOWN;
/** @var int
 * @cvalue GST_AUDIO_FORMAT_U20BE */
const GST_AUDIO_FORMAT_U20BE = UNKNOWN;
/** @var int
 * @cvalue GST_AUDIO_FORMAT_S18LE */
const GST_AUDIO_FORMAT_S18LE = UNKNOWN;
/** @var int
 * @cvalue GST_AUDIO_FORMAT_S18BE */
const GST_AUDIO_FORMAT_S18BE = UNKNOWN;
/** @var int
 * @cvalue GST_AUDIO_FORMAT_U18LE */
const GST_AUDIO_FORMAT_U18LE = UNKNOWN;
/** @var int
 * @cvalue GST_AUDIO_FORMAT_U18BE */
const GST_AUDIO_FORMAT_U18BE = UNKNOWN;
/** @var int
 * @cvalue GST_AUDIO_FORMAT_F32LE */
const GST_AUDIO_FORMAT_F32LE = UNKNOWN;
/** @var int
 * @cvalue GST_AUDIO_FORMAT_F32BE */
const GST_AUDIO_FORMAT_F32BE = UNKNOWN;
/** @var int
 * @cvalue GST_AUDIO_FORMAT_F64LE */
const GST_AUDIO_FORMAT_F64LE = UNKNOWN;
/** @var int
 * @cvalue GST_AUDIO_FORMAT_F64BE */
const GST_AUDIO_FORMAT_F64BE = UNKNOWN;
/** @var int
 * @cvalue GST_AUDIO_FORMAT_S16 */
const GST_AUDIO_FORMAT_S16 = UNKNOWN;
/** @var int
 * @cvalue GST_AUDIO_FORMAT_U16 */
const GST_AUDIO_FORMAT_U16 = UNKNOWN;
/** @var int
 * @cvalue GST_AUDIO_FORMAT_S24_32 */
const GST_AUDIO_FORMAT_S24_32 = UNKNOWN;
/** @var int
 * @cvalue GST_AUDIO_FORMAT_U24_32 */
const GST_AUDIO_FORMAT_U24_32 = UNKNOWN;
/** @var int
 * @cvalue GST_AUDIO_FORMAT_S32 */
const GST_AUDIO_FORMAT_S32 = UNKNOWN;
/** @var int
 * @cvalue GST_AUDIO_FORMAT_U32 */
const GST_AUDIO_FORMAT_U32 = UNKNOWN;
/** @var int
 * @cvalue GST_AUDIO_FORMAT_S24 */
const GST_AUDIO_FORMAT_S24 = UNKNOWN;
/** @var int
 * @cvalue GST_AUDIO_FORMAT_U24 */
const GST_AUDIO_FORMAT_U24 = UNKNOWN;
/** @var int
 * @cvalue GST_AUDIO_FORMAT_S20 */
const GST_AUDIO_FORMAT_S20 = UNKNOWN;
/** @var int
 * @cvalue GST_AUDIO_FORMAT_U20 */
const GST_AUDIO_FORMAT_U20 = UNKNOWN;
/** @var int
 * @cvalue GST_AUDIO_FORMAT_S18 */
const GST_AUDIO_FORMAT_S18 = UNKNOWN;
/** @var int
 * @cvalue GST_AUDIO_FORMAT_U18 */
const GST_AUDIO_FORMAT_U18 = UNKNOWN;
/** @var int
 * @cvalue GST_AUDIO_FORMAT_F32 */
const GST_AUDIO_FORMAT_F32 = UNKNOWN;
/** @var int
 * @cvalue GST_AUDIO_FORMAT_F64 */
const GST_AUDIO_FORMAT_F64 = UNKNOWN;

/**
 * Made by gst_audio_info_new(), freed by gst_audio_info_free(). finfo() is the format.
 *
 * @not-serializable
 */
final class GstAudioInfo
{
    private function __construct() {}

    public function pointer(): int {}

    public static function fromPointer(int $pointer): ?static {}

    public function finfo(): int {}

    public function flags(): int {}

    public function layout(): int {}

    public function rate(): int {}

    public function channels(): int {}

    public function bpf(): int {}
}

function gst_audio_info_new(): GstAudioInfo {}

function gst_audio_info_free(GstAudioInfo $info): void {}

function gst_audio_info_from_caps(GstAudioInfo $info, GstCaps $caps): bool {}

function gst_audio_format_to_string(int $format): ?string {}

function gst_audio_format_from_string(string $format): int {}

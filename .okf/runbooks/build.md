---
type: Runbook
title: Build, install, test
description: The floor, why Homebrew GStreamer on macOS, the two installers, CI, Pest, the support list.
resource: install-macos.sh
tags: [build, linux, macos, pest]
status: draft
generated: { by: claude-opus/5.5, at: 2026-11-12T00:00:00Z }
sources:
  - id: m4
    resource: config.m4
    title: config.m4
  - id: mac
    resource: install-macos.sh
    title: install-macos.sh
  - id: debian
    resource: install-debian-trixie.sh
    title: install-debian-trixie.sh
  - id: ci
    resource: .github/workflows/ci.yml
    title: CI
  - id: support
    resource: scripts/support.php
    title: Support list
---

# Overview

The floor is GStreamer 1.26.2, the version Debian trixie ships. `config.m4` asks pkg-config for gstreamer-1.0, gstreamer-app-1.0, gstreamer-video-1.0, gstreamer-audio-1.0 and gstreamer-pbutils-1.0, each ≥ 1.26.2.[^m4] Homebrew ships a newer GStreamer (1.28.9 on 2026-11-11). GStreamer 1.x never removes API, so a function the 1.26 headers declare builds on both.

# macOS: Homebrew, not the SDK

`brew install gstreamer`. The GStreamer.framework SDK from gstreamer.freedesktop.org carries its own GLib (2.82). The other extensions link Homebrew's GLib, and `zhp` loads them all: with the SDK, two GLibs in one process crashed next to ext-gtk (SIGSEGV) and gave GErrors the wrong domain next to ext-qt and ext-harfbuzz (2026-11-11). `install-macos.sh` refuses a GStreamer pkg-config finds outside Homebrew.[^mac] The SDK's runtime installer also removes the devel package's headers when it runs after it.

# Install

- macOS: `./install-macos.sh` builds in a disposable copy for Homebrew `php@8.4` and `php@8.4-zts`, re-signs the .so ad hoc and writes `30-gstreamer.ini`.[^mac]
- Debian trixie / Raspberry Pi OS: `./install-debian-trixie.sh` (needs `libgstreamer1.0-dev libgstreamer-plugins-base1.0-dev gstreamer1.0-plugins-good`).[^debian]
- Probe build: `GSTREAMER_CONFIGURE=--enable-gstreamer-probes` with either installer. Never ship one.

# Test

Pest v4 at `-d memory_limit=128M`. Media are made by GStreamer in the test (a WAV by `wavenc`, an AVI by `jpegenc ! avimux`); output goes only to `appsink`, `fakesink` or `filesink`. `tests/Probes` runs only on a probe build (`GSTREAMER_SO` names the module for the child processes). `composer install` is temporary: remove `vendor/` and `composer.lock` after.

# CI

macOS 15 (PHP 8.4 / 8.5, NTS / ZTS, Homebrew GStreamer) and `debian:trixie` (PHP 8.4, GStreamer 1.26): build and load. Ubuntu 24.04's GStreamer 1.24 is below the floor.[^ci]

# Support list

`php84 scripts/support.php` counts every function the 1.26.2 public headers of the five modules export (`GST_*_API`) or define `static inline`, fetched once from the GStreamer monorepo into `scripts/.support-cache/`, and writes `SUPPORT.md` and the README badge; `--check` exits 1 when either is stale.[^support] `gst_discoverer_info_unref` is a macro, listed apart and not counted.

[^m4]: config.m4
[^mac]: install-macos.sh
[^debian]: install-debian-trixie.sh
[^ci]: .github/workflows/ci.yml
[^support]: scripts/support.php

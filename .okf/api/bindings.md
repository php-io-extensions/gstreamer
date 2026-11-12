---
type: API
title: Bindings
description: The decode path bound 1:1 — pipelines, appsink, caps, buffers, video and audio info, the discoverer — with the handle classes, their fields and lifetimes.
resource: stubs/gst.stub.php
tags: [gstreamer, api, decode]
status: draft
generated: { by: claude-opus/5.5, at: 2026-11-12T00:00:00Z }
sources:
  - id: stubs
    resource: stubs/gst.stub.php
    title: The five stubs
  - id: spec
    resource: docs/superpowers/specs/2026-11-11-gstreamer-design.md
    title: Design spec
  - id: fields
    resource: src/fields.c
    title: Field getters and the kept refusal
  - id: probe
    resource: tests/Probes/FieldReleasedTest.php
    title: Probe for gst-field-released
---

# Overview

82 GStreamer functions, one stub per module, each declared in GStreamer 1.26.[^stubs] They cover what ext-ffmpeg's 42 do: build a pipeline (`gst_parse_launch`, or `gst_element_factory_make` + `gst_bin_add` + `gst_element_link*`, options by `gst_util_set_object_arg`), decode with `uridecodebin`, convert with `videoconvert ! videoscale` / `audioconvert ! audioresample` and caps, pull samples from `appsink`, read bytes by `gst_buffer_map` / `gst_buffer_extract`, seek, query position and duration, read the bus, and read streams with `GstDiscoverer`.[^spec]

| Module | Functions |
|---|---|
| gstreamer-1.0 | 47 |
| gstreamer-app-1.0 | 6 |
| gstreamer-video-1.0 | 5 |
| gstreamer-audio-1.0 | 5 |
| gstreamer-pbutils-1.0 | 19 |

Every call runs on the PHP thread: pull-mode appsink and `gst_bus_timed_pop_filtered`. No signal, pad probe or callback is bound.

# Classes

`GstObject` → `GstElement` → `GstBin` → `GstPipeline`; `GstAppSink` and `GstBus` under it. `GstDiscoverer`, `GstDiscovererInfo` and `GstDiscovererStreamInfo` (→ `GstDiscovererVideoInfo`, `GstDiscovererAudioInfo`) are top classes. The mini objects `GstMessage`, `GstCaps`, `GstStructure`, `GstSample`, `GstBuffer`, and `GstVideoInfo` / `GstAudioInfo`, are handles. `GstMapInfo` is made with `new`. A returned GObject gets the most derived bound class its GType is.

There is no `GObject` and no `GError` class: ext-gtk owns those PHP names, and a second registration fails silently (seen 2026-11-11: under `zhp` it corrupted `GstObject`'s parent and crashed). Where C takes `GObject *` or `gpointer`, the parameter is `GstObject|GstDiscoverer|GstDiscovererInfo|GstDiscovererStreamInfo` (`typemap`), checked by `gstreamer_gobject_arg`.

# Lifetimes

The binding counts the references it has seen (creation, `gst_object_ref`, transfer-full returns); the unref that brings the count to 0 sets the handle's pointer to 0. `gst_bin_add` of a floating element hands it to the bin; `gst_bin_remove` of such an element releases its handle. Borrowed returns (`gst_sample_get_buffer`, `gst_caps_get_structure`) are valid while their owner lives, as in C.

# Errors

A GError a call reports is thrown as `GstError` (`RuntimeException`, readonly `domain`) after the call; an object returned with it is unreffed. `gst_message_parse_error` / `_warning` throw the message's GError after assigning `$debug`.

# Refusals

One kept: `gst-field-released`. Field getters (all `gstreamer_field`) read the struct, and a released handle's pointer is NULL: SIGSEGV with the check off.[^fields][^probe] Dropped after probes, no crash: a released handle into GStreamer (GStreamer's `GST_IS_*` assertion), a call before init (a GError), a bad or double unmap.

[^stubs]: stubs/gst.stub.php
[^spec]: docs/superpowers/specs/2026-11-11-gstreamer-design.md
[^fields]: src/fields.c
[^probe]: tests/Probes/FieldReleasedTest.php

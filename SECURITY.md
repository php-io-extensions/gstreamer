# Security Policy

## Supported versions

ext-gstreamer is pre-1.0. No 0.x release receives security fixes or advisories; fixes land in
the next release line. Security support starts with 1.0.

| Version | Security fixes |
|---------|----------------|
| < 1.0   | No             |

## Reporting a vulnerability

Please don't open a public issue for a security problem.

Report it privately through GitHub: the **Report a vulnerability** button on the
[php-io-extensions/gstreamer](https://github.com/php-io-extensions/gstreamer) repository's
**Security** tab. If that isn't available, email **info@projectsaturnstudios.com**.

Include what you found, the affected version, your platform, PHP build (NTS or ZTS) and the
GStreamer version (`php --ri gstreamer` shows it), and steps to reproduce. Reports are read and
weighed for the release line in development; before 1.0 there is no response-time commitment.

A defect in GStreamer or one of its plugins belongs with that project. Report it here as well when
ext-gstreamer should guard against it.

## Security model

ext-gstreamer builds and runs GStreamer pipelines on behalf of the PHP process. What a pipeline
reads, writes or opens (files, URIs, network sources, devices) is what its description and
elements say: `gst_parse_launch` and `gst_discoverer_discover_uri` given untrusted text or URIs
open whatever that text names, with the plugins installed on the machine. The extension itself
reads no files and makes no network requests.

- **Addresses.** `fromPointer()` takes an address as an int and trusts it: an address from another
  extension is passed through as given.
- **Handles.** A field getter on a handle the binding released (`gst_*_unref` to zero,
  `gst_*_free`) throws `ValueError` instead of reading freed memory. A released handle passed to a
  GStreamer function reaches GStreamer as NULL, which GStreamer checks. A handle another object
  owns (a buffer of a sample, a structure of caps, an element of a bin) is valid while its owner
  lives, as in C.
- **Threads.** Every call runs on the PHP thread. GStreamer's streaming threads never enter PHP:
  the extension installs no signal handler, pad probe or callback.
- **Memory.** Mapped buffer bytes are copied into a PHP string at map time; PHP code never writes
  GStreamer's memory.

A report is in scope when ext-gstreamer itself reads or writes memory it should not, leaks, or
crashes: a field read through a freed handle, a string or list copied past its length, PHP entered
from a GStreamer thread.

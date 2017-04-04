News for kodo-cpp
=================

This file lists the major changes between versions. For a more detailed list
of every change, see the Git log.

Latest
------
* tbd

7.0.1
-----
* Patch: Fixed the installation of kodoc.h

7.0.0
-----
* Major: Upgrade to waf-tools 4
* Major: Upgrade to kodo-c 11
* Minor: Upgrade to gtest 4

6.0.0
-----
* Major: Upgrade to kodo-c 9

5.0.0
-----
* Major: Switched to the ``kodocpp::codec`` and ``kodocpp::field`` enum classes
  to enhance the type safety in the API.
* Major: Upgrade to kodo-c 8

4.0.0
-----
* Major: Upgrade to kodo-c 7
* Major: Upgrade to waf-tools 3
* Minor: Upgrade to gtest 3
* Major: Coders are now only available using shallow storage.
* Major: Tracing is now always available.
* Major: Renamed ``set_symbols`` to ``set_const_symbols`` for encoders.
* Major: Renamed ``set_symbols`` to ``set_mutable_symbols`` for decoders.
* Major: Removed ``copy_from_symbol`` and ``copy_from_symbols`` since they
  are not used with shallow storage.
* Minor: Added basic API for the fulcrum codec.
* Minor: Added unit tests for all codecs.

3.3.0
-----
* Patch: Removed the unsafe usage of the this pointer in ``set_trace_callback``.
  The callback function is now stored on the heap, and it can be accessed even
  after the coder instance is copied and destroyed.
* Minor: Changed the ``test_basic_api`` helper function to test coder instances
  that are created in different functions.

3.2.0
-----
* Minor: Allowed the default constructor for the encoder and decoder classes.

3.1.0
-----
* Minor: Added ``kodocpp_static_includes``.

3.0.0
-----
* Major: Store coders and factories as shared pointers in cpp wrappers.
* Minor: Added perpetual stack.
* Major: Upgrade to kodo 30.
* Major: Upgrade to kodo-c 6.

2.0.0
-----
* Major: Renamed ``copy_symbol`` and ``copy_symbols`` to
  ``copy_from_symbol`` and ``copy_from_symbols`` to their name in kodo 29.
* Major: Renamed `trace` and `trace_callback` to the appropriate names in
  kodo 29.
* Minor: Added buildbot.py for coverage reports.
* Major: Upgrade to kodo 29.
* Major: Upgrade to fifi 20.
* Major: Upgrade to kodo-c 5.
* Major: Renamed ``symbol_pivot`` to ``is_symbol_pivot`` to match the
  function name in Kodo.

1.0.0
-----
* Major: Restructured the library to function as a thin C++ wrapper on top of
  the C API of the kodo-c library following to the Hourglass pattern that was
  presented at CppCon 2014: https://www.youtube.com/watch?v=PVYdHDm0q6Y.
* Major: Initial release.

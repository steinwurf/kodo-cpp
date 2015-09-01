News for kodo-cpp
=================

This file lists the major changes between versions. For a more detailed list
of every change, see the Git log.

Latest
------
* tbd

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

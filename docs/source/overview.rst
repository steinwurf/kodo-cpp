Overview
========

.. _overview:

Kodo implements several network coding algorithms and codecs, as well as
other error correcting codecs and approaches. Kodo is written in C++ and
it was designed to ensure high performance, testability, flexibility and
extendability.

A fast implementation of finite fields is a prerequisite for fast RLNC
and other linear block codes. Kodo relies on our
`Fifi <http://github.com/steinwurf/fifi>`_ library which supports multiple
finite fields with different sizes.

The kodo-cpp library exposes a simple C++ Application Programming Interface
(API) which allows the programmer to use Kodo without any concern for the
underlying implementation details. kodo-cpp actually uses the C API provided by
the kodo-c library which was designed for portability and interoperability.

Kodo supports various network coding codecs e.g. standard Random Linear Network
Coding (RLNC), systematic RLNC, sparse RLNC. Each algorithm offers unique
advantages and drawbacks as well as a different set of parameters that can be
tuned in real time.


Features
--------

Recoding
    One of the most prominent features of Network Coding is the
    possibility to use coding at the intermediate network nodes
    (recoding) and not only at the sender (encoding) and the receiver
    (decoding).

Systematic coding
    The sender can send some or all of the original symbols within a
    given block uncoded. Coded packets can be generated later to repair
    any packet losses. Systematic coding is useful in simple topologies
    as it increases the decoding throughput and decreases the coding
    overhead.

On-the-fly coding
    The sender can encode over a growing block of data. This is useful
    for live content where the data becomes available over time,
    potentially at a variable rate.

Partial decoding
    The receiver can decode some of the original symbols before the
    entire data block is decoded. This approach is more compatible with
    error-resilient codecs (video, audio) as instead of receiving the
    whole data block or nothing, a partial data block can be retrieved.

Real-time adjustable density
    The density at the sender can be adjusted in real-time which permits
    adaptation to changing network conditions.

Symbol pruning
    The encoder can drop certain symbols which were already decoded at
    the decoder.

Zero-copy API
    The encoder and decoder can operate directly on user-provided buffers,
    eliminating the need for costly copy operations.

Object pooling
    The library can re-use existing encoder and decoder instances to
    facilitate efficient memory management.

Hardware optimized (on select hardware)
    Optimizations for various CPU architectures, using SIMD instructions
    and various coding algorithms to provide the best performance.


Random Linear Network Coding codecs
...................................

Standard RLNC
    All symbols are combined uniformly at random. In general, this type
    of coding is "dense", since the symbols in the data block are mixed
    as much as possible. Density is lower for small field sizes.

Sparse RLNC with uniform density
    Some symbols are excluded with a given probability during encoding.
    The remaining symbols are combined as in the standard RLNC case.
    This is typically useful when the block size is very high. The density
    can be reduced significantly without any negative effect and
    the decoding throughput can be increased substantially at the same time.

Seed-based RLNC
    Instead of sending the full coding vector, a small random seed can
    be sent to represent the coding vector. This reduces the overhead,
    but it can only be used when recoding is not necessary.

On-the-fly RLNC
    Symbols can be encoded as they are made available and data is released from
    the decoder as decoding progresses. This is different from traditional block
    codes where all data has to be available before encoding or decoding takes
    place. This codec is well suited for low-delay services such as messaging,
    voice over IP or video streaming.

Perpetual RLNC
    A sparse and structured code where the non-zero coding coefficients are
    localized to a specific part of the coding vector. The width of this
    non-zero part is analogous to the density parameter of random sparse codes.
    This approach allows for structured decoding, which can yield a
    substantially higher throughput compared to random sparse codes, especially
    for large generation sizes.

Fulcrum RLNC
    The Fulcrum network codes use a concatenated code structure with an "outer"
    and an "inner" code. They provide an end-to-end performance that is close
    to that of a large field size network coding system for high–end receivers,
    while simultaneously catering to low–end ones that can only decode in GF(2).
    For a detailed description of the Fulcrum codec, see the following
    `paper <http://arxiv.org/abs/1404.6620>`_ by Lucani et. al.

Other codecs
............

Reed-Solomon code
    Traditional Reed-Solomon (RS) code which does not support recoding. The
    current implementation uses a systematic Vandermonde matrix as described in
    `RFC 5510 <http://tools.ietf.org/html/rfc5510>`_.

Platform Support
----------------

Kodo is portable to a wide range of platforms. The `Kodo Specifications`_
page provides an overview of the supported platforms and compilers.

We ensure compatibility with the supported platforms through a suite of unit
tests, the current status can be checked at the `Steinwurf Buildbot`_ page.
At the bottom of the main page, you can find detailed information
about which platforms and compilers are currently tested by Steinwurf.

.. _Steinwurf Buildbot: http://buildbot.steinwurf.com
.. _Kodo Specifications: http://steinwurf.com/kodo-specifications/

.. note:: The Buildbot is used for several different libraries. The
  Kodo-C library can be found in the overview on the main page.

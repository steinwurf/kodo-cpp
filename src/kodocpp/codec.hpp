// Copyright Steinwurf ApS 2016.
// Distributed under the "STEINWURF RESEARCH LICENSE 1.0".
// See accompanying file LICENSE.rst or
// http://www.steinwurf.com/licensing

#pragma once

#include <cstdint>

#include <kodoc/kodoc.h>

namespace kodocpp
{
/// Enum class specifying the available codecs
enum class codec: int32_t
{
    full_vector = kodoc_full_vector,
    on_the_fly = kodoc_on_the_fly,
    sliding_window = kodoc_sliding_window,
    sparse_full_vector = kodoc_sparse_full_vector,
    seed = kodoc_seed,
    sparse_seed = kodoc_sparse_seed,
    perpetual = kodoc_perpetual,
    fulcrum = kodoc_fulcrum,
    reed_solomon = kodoc_reed_solomon
};

/// Checks whether a given codec is available in the current configuration.
/// It is possible to enable or disable specific codecs when configuring
/// kodo-cpp.
/// To see the relevant options, execute "python waf --help"
/// @param codec The codec type that should be checked
/// @return true if the codec is available
inline bool has_codec(codec codec)
{
    return kodoc_has_codec((int32_t)codec) != 0;
}
}

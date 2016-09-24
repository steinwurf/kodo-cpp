// Copyright Steinwurf ApS 2016.
// Distributed under the "STEINWURF RESEARCH LICENSE 1.0".
// See accompanying file LICENSE.rst or
// http://www.steinwurf.com/licensing

#pragma once

#include <cstdint>

#include <kodoc/kodoc.h>

namespace kodocpp
{
/// Enum class specifying the available finite fields
enum class field: int32_t
{
    binary = kodoc_binary,
    binary4 = kodoc_binary4,
    binary8 = kodoc_binary8
};
}

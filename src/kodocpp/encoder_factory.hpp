// Copyright Steinwurf ApS 2011-2013.
// Distributed under the "STEINWURF RESEARCH LICENSE 1.0".
// See accompanying file LICENSE.rst or
// http://www.steinwurf.com/licensing

#pragma once

#include <cstdint>
#include <cassert>

#include <kodoc/kodoc.h>

#include "field.hpp"
#include "codec.hpp"
#include "factory.hpp"
#include "encoder.hpp"

namespace kodocpp
{
class encoder_factory : public factory
{
public:

    using coder_type = encoder;

public:

    /// Constructs a new encoder factory (for shallow storage encoders)
    /// @param codec This parameter determines the encoding algorithms used.
    /// @param field The finite field that should be used by the
    ///        encoder.
    /// @param max_symbols The maximum number of symbols supported by
    ///        encoders built with this factory.
    /// @param max_symbol_size The maximum symbol size in bytes supported
    ///        by encoders built using the returned factory.
    encoder_factory(codec codec, field field,
                    uint32_t max_symbols, uint32_t max_symbol_size) :
        factory(kodoc_new_encoder_factory(
            (int32_t)codec, (int32_t)field, max_symbols, max_symbol_size),
            [](kodoc_factory_t factory) { kodoc_delete_factory(factory); })
    { }

    /// Builds a new encoder with the factory using the specified parameters
    /// @return The new encoder
    coder_type build()
    {
        kodoc_coder_t coder = kodoc_factory_build_coder(m_factory.get());
        return coder_type(coder);
    }
};
}

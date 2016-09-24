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
#include "decoder.hpp"

namespace kodocpp
{
class decoder_factory : public factory
{
public:

    using coder_type = decoder;

public:

    /// Constructs a new decoder factory (for shallow storage decoders)
    /// @param codec This parameter determines the decoding algorithms used.
    /// @param field The finite field that should be used by the
    ///        decoder.
    /// @param max_symbols The maximum number of symbols supported by
    ///        decoders built with this factory.
    /// @param max_symbol_size The maximum symbol size in bytes supported
    ///        by decoders built using the returned factory
    decoder_factory(codec codec, field field,
                    uint32_t max_symbols, uint32_t max_symbol_size) :
        factory(kodoc_new_decoder_factory(
            (int32_t)codec, (int32_t)field, max_symbols, max_symbol_size),
            [](kodoc_factory_t factory) { kodoc_delete_factory(factory); })
    { }

    /// Builds a new decoder with the factory using the specified parameters
    /// @return The new decoder
    coder_type build()
    {
        kodoc_coder_t coder = kodoc_factory_build_coder(m_factory.get());
        return coder_type(coder);
    }
};
}

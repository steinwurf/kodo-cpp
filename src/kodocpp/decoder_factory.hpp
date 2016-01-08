// Copyright Steinwurf ApS 2011-2013.
// Distributed under the "STEINWURF RESEARCH LICENSE 1.0".
// See accompanying file LICENSE.rst or
// http://www.steinwurf.com/licensing

#pragma once

#include <cstdint>
#include <cassert>

#include <kodoc/kodoc.h>

#include "factory.hpp"
#include "decoder.hpp"

namespace kodocpp
{
    class decoder_factory : public factory
    {
    public:

        using coder_type = decoder;

    public:

        decoder_factory(kodoc_codec code, kodoc_finite_field field,
                        uint32_t max_symbols, uint32_t max_symbol_size) :
            factory(kodoc_new_decoder_factory(code, field, max_symbols,
                    max_symbol_size), [](kodoc_factory_t factory)
                    {
                        kodoc_delete_factory(factory);
                    })
        { }

        coder_type build()
        {
            kodoc_coder_t coder = kodoc_factory_build_coder(m_factory.get());
            return coder_type(coder);
        }
    };
}

// Copyright Steinwurf ApS 2011-2013.
// Distributed under the "STEINWURF RESEARCH LICENSE 1.0".
// See accompanying file LICENSE.rst or
// http://www.steinwurf.com/licensing

#pragma once

#include <cstdint>
#include <cassert>

#include <kodoc/kodoc.h>

#include "factory.hpp"
#include "encoder.hpp"

namespace kodocpp
{
    class encoder_factory : public factory
    {
    public:

        encoder_factory(kodo_code_type code, kodo_finite_field field,
            uint32_t max_symbols, uint32_t max_symbol_size,
            bool trace_enabled = false) :
            factory(kodo_new_encoder_factory(code, field, max_symbols,
                max_symbol_size, trace_enabled), [](kodo_factory_t factory)
                {
                    kodo_delete_encoder_factory(factory);
                })
        { }

        encoder build()
        {
            kodo_coder_t coder = kodo_factory_new_encoder(m_factory.get());
            return encoder(coder);
        }
    };
}

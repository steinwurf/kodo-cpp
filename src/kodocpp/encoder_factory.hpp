// Copyright Steinwurf ApS 2011-2013.
// Distributed under the "STEINWURF RESEARCH LICENSE 1.0".
// See accompanying file LICENSE.rst or
// http://www.steinwurf.com/licensing

#pragma once

#include <cstdint>
#include <cassert>

#include <kodoc/kodoc.h>

#include "encoder.hpp"

namespace kodocpp
{
    class encoder_factory
    {
    public:

        encoder_factory(kodo_code_type code,
                        kodo_finite_field field,
                        uint32_t max_symbols,
                        uint32_t max_symbol_size,
                        bool trace_enabled = false)
        {
            m_factory = kodo_new_encoder_factory(
                code, field,
                max_symbols, max_symbol_size,
                trace_enabled);
            assert(m_factory);
        }

        ~encoder_factory()
        {
            assert(m_factory);
            kodo_delete_encoder_factory(m_factory);
        }

        encoder build()
        {
            kodo_coder_t coder = kodo_factory_new_encoder(m_factory);
            return encoder(coder);
        }

        void set_symbols(uint32_t symbols)
        {
            kodo_factory_set_symbols(m_factory, symbols);
        }

        void set_symbol_size(uint32_t symbol_size)
        {
            kodo_factory_set_symbol_size(m_factory, symbol_size);
        }

        uint32_t max_symbols() const
        {
            return kodo_factory_max_symbols(m_factory);
        }

        uint32_t max_symbol_size() const
        {
            return kodo_factory_max_symbol_size(m_factory);
        }

        uint32_t max_block_size() const
        {
            return kodo_factory_max_block_size(m_factory);
        }

        uint32_t max_payload_size() const
        {
            return kodo_factory_max_payload_size(m_factory);
        }

    private:

        kodo_factory_t m_factory;
    };
}

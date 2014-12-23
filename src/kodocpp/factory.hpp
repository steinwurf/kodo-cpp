// Copyright Steinwurf ApS 2011-2013.
// Distributed under the "STEINWURF RESEARCH LICENSE 1.0".
// See accompanying file LICENSE.rst or
// http://www.steinwurf.com/licensing

#pragma once

#include <cstdint>
#include <cassert>

#include <kodoc/kodoc.h>

namespace kodocpp
{
    class factory
    {
    protected:

        // Make sure that this base class cannot be instantiated
        factory()
        { }

    public:

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

    protected:

        kodo_factory_t m_factory;
    };
}

// Copyright Steinwurf ApS 2011-2013.
// Distributed under the "STEINWURF RESEARCH LICENSE 1.0".
// See accompanying file LICENSE.rst or
// http://www.steinwurf.com/licensing

#pragma once

#include <cstdint>
#include <cassert>
#include <memory>
#include <functional>

#include <kodoc/kodoc.h>

namespace kodocpp
{
    class factory
    {
    protected:

        // Make sure that this base class cannot be instantiated
        factory(kodo_factory_t factory,
                std::function<void(kodo_factory_t)> deleter) :
            m_factory(factory, deleter)
        { }

    public:

        void set_symbols(uint32_t symbols)
        {
            kodo_factory_set_symbols(m_factory.get(), symbols);
        }

        void set_symbol_size(uint32_t symbol_size)
        {
            kodo_factory_set_symbol_size(m_factory.get(), symbol_size);
        }

        uint32_t max_symbols() const
        {
            return kodo_factory_max_symbols(m_factory.get());
        }

        uint32_t max_symbol_size() const
        {
            return kodo_factory_max_symbol_size(m_factory.get());
        }

        uint32_t max_block_size() const
        {
            return kodo_factory_max_block_size(m_factory.get());
        }

        uint32_t max_payload_size() const
        {
            return kodo_factory_max_payload_size(m_factory.get());
        }

        uint32_t max_expansion() const
        {
            return kodo_factory_max_expansion(m_factory.get());
        }

        void set_expansion(uint32_t expansion)
        {
            kodo_factory_set_expansion(m_factory.get(), expansion);
        }

    protected:

        std::shared_ptr<kodo_factory> m_factory;
    };
}

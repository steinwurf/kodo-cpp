// Copyright Steinwurf ApS 2011-2013.
// Distributed under the "STEINWURF RESEARCH LICENSE 1.0".
// See accompanying file LICENSE.rst or
// http://www.steinwurf.com/licensing

#pragma once

#include "factory_interface.hpp"
namespace kodo
{
    class encoder_factory_interface : public factory_interface
    {
    public:
        encoder_wrapper* build()
        {
            return NULL;
        }

        virtual void set_symbols(uint32_t symbols) = 0;
        virtual void set_symbol_size(uint32_t symbol_size) = 0;

        virtual uint32_t max_symbols() const = 0;
        virtual uint32_t max_symbol_size() const = 0;
        virtual uint32_t max_block_size() const = 0;
        virtual uint32_t max_payload_size() const = 0;
    };
}

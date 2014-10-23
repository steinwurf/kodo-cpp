// Copyright Steinwurf ApS 2011-2013.
// Distributed under the "STEINWURF RESEARCH LICENSE 1.0".
// See accompanying file LICENSE.rst or
// http://www.steinwurf.com/licensing

#pragma once

#include <cstdint>
#include "../algorithms.hpp"
#include "../field_types.hpp"

namespace kodo
{
    class factory_interface
    {
    public:
//        virtual void* build() = 0;

        virtual void set_symbols(uint32_t symbols) = 0;
        virtual void set_symbol_size(uint32_t symbol_size) = 0;

        virtual uint32_t max_symbols() const = 0;
        virtual uint32_t max_symbol_size() const = 0;
        virtual uint32_t max_block_size() const = 0;
        virtual uint32_t max_payload_size() const = 0;

        virtual ~factory_interface(){}
    };
}

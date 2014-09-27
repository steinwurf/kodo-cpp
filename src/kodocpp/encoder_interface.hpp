// Copyright Steinwurf ApS 2011-2013.
// Distributed under the "STEINWURF RESEARCH LICENSE 1.0".
// See accompanying file LICENSE.rst or
// http://www.steinwurf.com/licensing

#pragma once

#include "coder.hpp"

namespace kodo
{
    /// Base class for an encoder implementation
    class encoder : public coder
    {
    public:

        virtual ~encoder() {}

        virtual uint32_t encode(uint8_t* data) = 0;

        virtual void set_symbols(
            const uint8_t* data, uint32_t size) = 0;

        virtual void set_symbol(
            uint32_t index, const uint8_t* data, uint32_t size) = 0;

        virtual bool has_systematic_encoder() const = 0;
        virtual bool is_systematic_on() const = 0;
        virtual void set_systematic_on() = 0;
        virtual void set_systematic_off() = 0;
        virtual void read_feedback(uint8_t* feedback) = 0;
    };
}

// Copyright Steinwurf ApS 2011-2013.
// Distributed under the "STEINWURF RESEARCH LICENSE 1.0".
// See accompanying file LICENSE.rst or
// http://www.steinwurf.com/licensing

#pragma once

#include "coder.hpp"

namespace kodo
{
    /// Base class for decoder implementation
    class decoder_interface : public coder_interface
    {
    public:

        virtual ~decoder_interface() {}

        virtual uint32_t recode(uint8_t* data) = 0;
        virtual void decode(uint8_t* data) = 0;
        virtual bool is_complete() const = 0;

        virtual void copy_symbols(uint8_t* data, uint32_t size) const = 0;

        virtual void copy_symbol(uint32_t index, uint8_t* data,
                                 uint32_t size) const = 0;

        virtual bool has_partial_decoding_tracker() const = 0;

        virtual bool is_partial_complete() const = 0;
        virtual bool is_symbol_uncoded(uint32_t) const = 0;

        virtual uint32_t symbols_uncoded() const = 0;
        virtual uint32_t symbols_seen() const = 0;
        virtual void write_feedback(uint8_t* feedback) = 0;

    };
}

// Copyright Steinwurf ApS 2011-2013.
// Distributed under the "STEINWURF RESEARCH LICENSE 1.0".
// See accompanying file LICENSE.rst or
// http://www.steinwurf.com/licensing

#pragma once

#include <cstdint>
#include <cassert>

#include <kodoc/kodoc.h>

#include "coder.hpp"
#include <iostream>

namespace kodocpp
{
    class decoder: public coder
    {
    public:

        decoder(kodo_coder_t coder_instance = 0) :
            coder(coder_instance, [](kodo_coder_t coder)
                {
                    if (coder != 0) kodo_delete_coder(coder);
                })
        { }

        void set_mutable_symbols(uint8_t* data, uint32_t size)
        {
            kodo_set_mutable_symbols(m_coder.get(), data, size);
        }

        void set_mutable_symbol(uint32_t index, uint8_t* data, uint32_t size)
        {
            kodo_set_mutable_symbol(m_coder.get(), index, data, size);
        }

        void read_payload(uint8_t* data)
        {
            kodo_read_payload(m_coder.get(), data);
        }

        bool is_complete() const
        {
            return kodo_is_complete(m_coder.get()) != 0;
        }

        bool has_partial_decoding_tracker() const
        {
            return kodo_has_partial_decoding_tracker(m_coder.get()) != 0;
        }

        bool is_partial_complete() const
        {
            return kodo_is_partial_complete(m_coder.get()) != 0;
        }

        bool is_symbol_uncoded(uint32_t index) const
        {
            return kodo_is_symbol_uncoded(m_coder.get(), index) != 0;
        }

        uint32_t symbols_uncoded() const
        {
            return kodo_symbols_uncoded(m_coder.get());
        }

        uint32_t symbols_seen() const
        {
            return kodo_symbols_seen(m_coder.get());
        }

        void write_feedback(uint8_t* feedback)
        {
            kodo_write_feedback(m_coder.get(), feedback);
        }
    };
}

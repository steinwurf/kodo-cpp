// Copyright Steinwurf ApS 2011-2013.
// Distributed under the "STEINWURF RESEARCH LICENSE 1.0".
// See accompanying file LICENSE.rst or
// http://www.steinwurf.com/licensing

#pragma once

#include <cstdint>
#include <cassert>

#include <kodoc/kodoc.h>

#include "coder.hpp"

namespace kodocpp
{
    class decoder: public coder
    {
    public:

        decoder(kodoc_coder_t coder_instance = 0) :
            coder(coder_instance, [](kodoc_coder_t coder)
                {
                    if (coder != 0) kodoc_delete_coder(coder);
                })
        { }

        void set_mutable_symbols(uint8_t* data, uint32_t size)
        {
            kodoc_set_mutable_symbols(m_coder.get(), data, size);
        }

        void set_mutable_symbol(uint32_t index, uint8_t* data, uint32_t size)
        {
            kodoc_set_mutable_symbol(m_coder.get(), index, data, size);
        }

        void read_payload(uint8_t* data)
        {
            kodoc_read_payload(m_coder.get(), data);
        }

        bool is_complete() const
        {
            return kodoc_is_complete(m_coder.get()) != 0;
        }

        bool has_partial_decoding_interface() const
        {
            return kodoc_has_partial_decoding_interface(m_coder.get()) != 0;
        }

        bool is_partially_complete() const
        {
            return kodoc_is_partially_complete(m_coder.get()) != 0;
        }

        bool is_symbol_uncoded(uint32_t index) const
        {
            return kodoc_is_symbol_uncoded(m_coder.get(), index) != 0;
        }

        uint32_t symbols_uncoded() const
        {
            return kodoc_symbols_uncoded(m_coder.get());
        }

        uint32_t symbols_partially_decoded() const
        {
            return kodoc_symbols_partially_decoded(m_coder.get());
        }

        void write_feedback(uint8_t* feedback)
        {
            kodoc_write_feedback(m_coder.get(), feedback);
        }
    };
}

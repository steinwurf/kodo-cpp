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

        decoder(kodo_coder_t coder_instance) :
            coder(coder_instance)
        {
            assert(m_coder);
        }

        ~decoder()
        {
            kodo_delete_decoder(m_coder);
        }

        void read_payload(uint8_t* data)
        {
            kodo_read_payload(m_coder, data);
        }

        bool is_complete() const
        {
            return kodo_is_complete(m_coder) != 0;
        }

        void copy_from_symbols(uint8_t* data, uint32_t size) const
        {
            kodo_copy_from_symbols(m_coder, data, size);
        }

        void copy_from_symbol(uint32_t index, uint8_t* data,
            uint32_t size) const
        {
            kodo_copy_from_symbol(m_coder, index, data, size);
        }

        bool has_partial_decoding_tracker() const
        {
            return kodo_has_partial_decoding_tracker(m_coder) != 0;
        }

        bool is_partial_complete() const
        {
            return kodo_is_partial_complete(m_coder) != 0;
        }

        bool is_symbol_uncoded(uint32_t index) const
        {
            return kodo_is_symbol_uncoded(m_coder, index) != 0;
        }

        uint32_t symbols_uncoded() const
        {
            return kodo_symbols_uncoded(m_coder);
        }

        uint32_t symbols_seen() const
        {
            return kodo_symbols_seen(m_coder);
        }

        void write_feedback(uint8_t* feedback)
        {
            kodo_write_feedback(m_coder, feedback);
        }
    };
}

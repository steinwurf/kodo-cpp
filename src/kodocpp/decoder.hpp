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
    class decoder
    {
    public:

        decoder(kodo_coder_t coder) :
            m_coder(coder)
        {
            assert(m_coder);
        }

        ~decoder()
        {
            kodo_delete_decoder(m_coder);
        }

        // Coder methods

        uint32_t block_size() const
        {
            return kodo_block_size(m_coder);
        }

        uint32_t payload_size() const
        {
            return kodo_payload_size(m_coder);
        }

        uint32_t rank() const
        {
            return kodo_rank(m_coder);
        }

        uint32_t symbol_size() const
        {
            return kodo_symbol_size(m_coder);
        }

        uint32_t symbols() const
        {
            return kodo_symbols(m_coder);
        }

        bool symbol_pivot(uint32_t index) const
        {
            return kodo_symbol_pivot(m_coder, index) != 0;
        }

        bool has_trace() const
        {
            return kodo_has_trace(m_coder) != 0;
        }

        void trace()
        {
            kodo_trace(m_coder);
        }

        void trace(kodo_trace_callback_t callback)
        {
            kodo_trace_callback(m_coder, callback);
        }

        bool has_feedback_size() const
        {
            return kodo_has_feedback_size(m_coder) != 0;
        }

        uint32_t feedback_size() const
        {
            return kodo_feedback_size(m_coder);
        }

        // Decoder methods
        uint32_t recode(uint8_t* data)
        {
            return kodo_recode(m_coder, data);
        }

        void decode(uint8_t* data)
        {
            kodo_decode(m_coder, data);
        }

        bool is_complete() const
        {
            return kodo_is_complete(m_coder) != 0;
        }

        void copy_symbols(uint8_t* data, uint32_t size) const
        {
            kodo_copy_symbols(m_coder, data, size);
        }

        void copy_symbol(uint32_t index, uint8_t* data, uint32_t size) const
        {
            kodo_copy_symbol(m_coder, index, data, size);
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

    private:

        kodo_coder_t m_coder;
    };
}

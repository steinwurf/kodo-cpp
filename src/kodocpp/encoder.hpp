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
    class encoder
    {
    public:

        encoder(kodo_coder_t coder) :
            m_coder(coder)
        {
            assert(m_coder);
        }

        ~encoder()
        {
            kodo_delete_encoder(m_coder);
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

        // Enoder methods

        uint32_t encode(uint8_t* payload)
        {
            return kodo_encode(m_coder, payload);
        }

        void set_symbols(const uint8_t* data, uint32_t size)
        {
            kodo_set_symbols(m_coder, data, size);
        }

        void set_symbol(
            uint32_t index, const uint8_t* data, uint32_t size)
        {
            kodo_set_symbol(m_coder, index, data, size);
        }

        bool has_systematic_encoder() const
        {
            return kodo_has_systematic_encoder(m_coder) != 0;
        }

        bool is_systematic_on() const
        {
            return kodo_is_systematic_on(m_coder) != 0;
        }

        void set_systematic_on()
        {
            kodo_set_systematic_on(m_coder);
        }

        void set_systematic_off()
        {
            kodo_set_systematic_off(m_coder);
        }

        void read_feedback(uint8_t* feedback)
        {
            kodo_read_feedback(m_coder, feedback);
        }

    private:

        kodo_coder_t m_coder;
    };
}

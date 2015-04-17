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
    class coder
    {
    protected:

        // Make sure that this base class cannot be instantiated
        coder(kodo_coder_t coder) :
            m_coder(coder)
        {
            assert(m_coder);
        }

    public:

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

        bool is_symbol_pivot(uint32_t index) const
        {
            return kodo_is_symbol_pivot(m_coder, index) != 0;
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

        uint32_t write_payload(uint8_t* data)
        {
            return kodo_write_payload(m_coder, data);
        }

    protected:

        kodo_coder_t m_coder;
    };
}

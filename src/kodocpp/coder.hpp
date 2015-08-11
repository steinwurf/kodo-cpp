// Copyright Steinwurf ApS 2011-2013.
// Distributed under the "STEINWURF RESEARCH LICENSE 1.0".
// See accompanying file LICENSE.rst or
// http://www.steinwurf.com/licensing

#pragma once

#include <cstdint>
#include <cassert>
#include <string>
#include <functional>

#include <kodoc/kodoc.h>

namespace kodocpp
{
    class coder
    {

    private:

        using callback_type =
            std::function<void(const std::string&, const std::string&)>;

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

        bool has_set_trace_callback() const
        {
            return kodo_has_set_trace_callback(m_coder) != 0;
        }

        bool has_set_trace_stdout() const
        {
            return kodo_has_set_trace_stdout(m_coder) != 0;
        }

        bool has_set_trace_off() const
        {
            return kodo_has_set_trace_off(m_coder) != 0;
        }

        void set_trace_callback(callback_type callback)
        {
            m_callback = callback;

            auto c_callback = [](
                const char* zone,
                const char* data,
                void* _this)
            {
                ((coder*)_this)->m_callback(std::string(zone),
                    std::string(data));
            };

            kodo_set_trace_callback(m_coder, c_callback, this);
        }

        void set_trace_stdout()
        {
            kodo_set_trace_stdout(m_coder);
        }

        void set_trace_off()
        {
            kodo_set_trace_off(m_coder);
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

        uint32_t reference_count;
        kodo_coder_t m_coder;
        callback_type m_callback;

    };
}

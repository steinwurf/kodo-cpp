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
#include <memory>

namespace kodocpp
{
    class coder
    {
    private:

        using callback_type =
            std::function<void(const std::string&, const std::string&)>;

    protected:

        // Make sure that this base class cannot be instantiated
        coder(kodo_coder_t coder, std::function<void(kodo_coder_t)> deleter) :
            m_coder(coder, deleter)
        { }

    public:

        uint32_t block_size() const
        {
            return kodo_block_size(m_coder.get());
        }

        uint32_t payload_size() const
        {
            return kodo_payload_size(m_coder.get());
        }

        uint32_t rank() const
        {
            return kodo_rank(m_coder.get());
        }

        uint32_t symbol_size() const
        {
            return kodo_symbol_size(m_coder.get());
        }

        uint32_t symbols() const
        {
            return kodo_symbols(m_coder.get());
        }

        bool is_symbol_pivot(uint32_t index) const
        {
            return kodo_is_symbol_pivot(m_coder.get(), index) != 0;
        }

        bool has_set_trace_callback() const
        {
            return kodo_has_set_trace_callback(m_coder.get()) != 0;
        }

        bool has_set_trace_stdout() const
        {
            return kodo_has_set_trace_stdout(m_coder.get()) != 0;
        }

        bool has_set_trace_off() const
        {
            return kodo_has_set_trace_off(m_coder.get()) != 0;
        }

        void set_trace_callback(callback_type callback)
        {
            // This function object will be allocated on the heap, and its
            // address remain valid until the shared pointer is destroyed.
            // Therefore it is safe to use this callback even after the coder
            // object is copied and destroyed (i.e. its this pointer becomes
            // invalid).
            m_callback.reset(new callback_type(callback));

            auto c_callback = [](const char* zone, const char* data,
                                 void* context)
            {
                callback_type heap_callback = *((callback_type*)context);
                heap_callback(zone, data);
            };

            kodo_set_trace_callback(m_coder.get(), c_callback,
                                    m_callback.get());
        }

        void set_trace_stdout()
        {
            kodo_set_trace_stdout(m_coder.get());
        }

        void set_trace_off()
        {
            kodo_set_trace_off(m_coder.get());
        }

        bool has_feedback_size() const
        {
            return kodo_has_feedback_size(m_coder.get()) != 0;
        }

        uint32_t feedback_size() const
        {
            return kodo_feedback_size(m_coder.get());
        }

        uint32_t write_payload(uint8_t* data)
        {
            return kodo_write_payload(m_coder.get(), data);
        }

    protected:

        std::shared_ptr<kodo_coder> m_coder;

    private:

        std::shared_ptr<callback_type> m_callback;
    };
}

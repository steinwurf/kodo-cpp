// Copyright Steinwurf ApS 2011-2013.
// Distributed under the "STEINWURF RESEARCH LICENSE 1.0".
// See accompanying file LICENSE.rst or
// http://www.steinwurf.com/licensing

#pragma once
#include "encoder_wrapper.hpp"

namespace kodo
{
    class encoder
    {
    public:
        encoder(encoder_interface* wrapper) : m_wrapper(wrapper)
        {

        }

        virtual uint32_t encode(uint8_t* data)
        {
            return m_wrapper.encode(data);
        }

        virtual void set_symbols(const uint8_t* data, uint32_t size)
        {
            m_wrapper.set_symbols(data, size);
        }

        virtual void set_symbol(uint32_t index, uint8_t* data, uint32_t size)
        {
            m_wrapper.set_symbol(index, data, size);
        }

        virtual bool has_systematic_encoder() const
        {
            return m_wrapper.has_systematic_encoder();
        }

        virtual bool is_systematic_on() const
        {
            return m_wrapper.is_systematic_on();
        }

        virtual void set_systematic_on()
        {
            m_wrapper.set_systematic_on(m_encoder);
        }
        virtual void set_systematic_off()
        {
            m_wrapper.set_systematic_off();
        }

        virtual void read_feedback(uint8_t* feedback)
        {
            m_wrapper.read_feedback(feedback);
        }

    private:
        encoder_interface* m_wrapper:
    }

}

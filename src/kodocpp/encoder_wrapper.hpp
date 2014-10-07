// Copyright Steinwurf ApS 2011-2013.
// Distributed under the "STEINWURF RESEARCH LICENSE 1.0".
// See accompanying file LICENSE.rst or
// http://www.steinwurf.com/licensing

#pragma once
#include "encoder_interface.hpp"

namespace kodo
{

    template<class KodoStack>
    class encoder_wrapper : public encoder_interface
    {
    public:
        encoder_wrapper(KodoStack* stack) : m_encoder(stack)
        {

        }

        virtual uint32_t encode(uint8_t* data)
        {
            return m_encoder->encode(data);
        }

        virtual void set_symbols(const uint8_t* data, uint32_t size)
        {
            m_encoder->set_symbols(data, size);
        }

        virtual void set_symbol(uint32_t index, uint8_t* data, uint32_t size)
        {
            m_encoder->set_symbol(index, data, size);
        }

        virtual bool has_systematic_encoder() const
        {
            return kodo::has_systematic_encoder<KodoStack>::value;
        }

        virtual bool is_systematic_on() const
        {
            return kodo::is_systematic_on(m_encoder);
        }

        virtual void set_systematic_on()
        {
            kodo::set_systematic_on(m_encoder);
        }
        virtual void set_systematic_off()
        {
            kodo::set_systematic_off(m_encoder);
        }

        virtual void read_feedback(uint8_t* feedback)
        {
            kodo::read_feedback(m_encoder, feedback);
        }

    private:
        typename KodoStack::pointer m_encoder;
    }
}

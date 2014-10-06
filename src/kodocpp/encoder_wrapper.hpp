// Copyright Steinwurf ApS 2011-2013.
// Distributed under the "STEINWURF RESEARCH LICENSE 1.0".
// See accompanying file LICENSE.rst or
// http://www.steinwurf.com/licensing

#pragma once
#include "encoder_interface.hpp"

namespace kodo
{

    template<class KodoStack>
    class encoder_wrapper
    {
    public:
        encoder_wrapper(KodoStack* stack) : mStack(stack)
        {

        }

        virtual uint32_t encode(uint8_t* data)
        {
            return mStack->encode(data);
        }

        virtual void set_symbols(const uint8_t* data, uint32_t size)
        {
            mStack->set_symbols(data, size);
        }

        virtual void set_symbol(uint32_t index, uint8_t* data, uint32_t size)
        {
            mStack->set_symbol(index, data, size);
        }

        //ASK JEPPE
        virtual bool has_systematic_encoder() const
        {
            return mStack->has_systematic_encoder();
        }


        virtual bool is_systematic_on() const
        {
            return mStack->is_systematic_on();
        }
        //

        virtual void set_systematic_on()
        {
            kodo::set_systematic_on();
        }
        virtual void set_systematic_off()
        {
            kodo::set_systematic_off();
        }

        virtual void read_feedback(uint8_t* feedback)
        {
            kodo::read_feedback(stack, feedback);
        }

    private:
        KodoStack* mStack;
    }
}

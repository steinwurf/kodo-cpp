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
            return mStack.encode(data);
        }

    private:
        KodoStack* mStack;
    }



}

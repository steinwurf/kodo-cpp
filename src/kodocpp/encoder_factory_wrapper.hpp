
// Copyright Steinwurf ApS 2011-2013.
// Distributed under the "STEINWURF RESEARCH LICENSE 1.0".
// See accompanying file LICENSE.rst or
// http://www.steinwurf.com/licensing

#pragma once

#include "factory_wrapper.hpp"
#include "encoder_wrapper.hpp"

namespace kodo
{
    template<class KodoStack>
    class encoder_factory_wrapper : public factory_wrapper<KodoStack>
    {
    public:

        encoder_factory_wrapper(uint32_t max_symbols,
                                uint32_t max_symbol_size) :
            factory_wrapper<KodoStack>(max_symbols, max_symbol_size)
        { }

        //example new constructor
        //kodo::factory f = kodo::factory(kodo::full_rlnc,
        //kodo::binary8, 32, 1024, false);
        void encoder_factory_semi_constructor(uint32_t max_symbols,
                                              uint32_t max_symbol_size,
                                              bool trace_enabled)
        {

        }
        virtual void* build()
        {
            auto encoder = m_factory.build();
            auto wrapper = new encoder_wrapper<KodoStack>(encoder);

            return wrapper;
        }

    private:

        using factory_wrapper<KodoStack>::m_factory;
    };
}

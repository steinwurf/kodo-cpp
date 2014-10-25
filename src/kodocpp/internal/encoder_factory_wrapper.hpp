// Copyright Steinwurf ApS 2011-2013.
// Distributed under the "STEINWURF RESEARCH LICENSE 1.0".
// See accompanying file LICENSE.rst or
// http://www.steinwurf.com/licensing

#pragma once

#include "factory_wrapper.hpp"
#include "encoder_factory_interface.hpp"
#include "encoder_wrapper.hpp"

namespace kodocpp
{
    template<class KodoStack>
    class encoder_factory_wrapper : public
        factory_wrapper<KodoStack, encoder_factory_interface>
    {
    public:

        using Super = factory_wrapper<KodoStack, encoder_factory_interface>;

    public:

        encoder_factory_wrapper(uint32_t max_symbols,
                                uint32_t max_symbol_size) :
            Super(max_symbols, max_symbol_size)
        { }

        virtual encoder_interface* build()
        {
            auto encoder = m_factory.build();
            auto wrapper = new encoder_wrapper<KodoStack>(encoder);

            return wrapper;
        }

    private:

        using Super::m_factory;
    };
}

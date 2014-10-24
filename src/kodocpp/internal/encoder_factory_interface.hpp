// Copyright Steinwurf ApS 2011-2013.
// Distributed under the "STEINWURF RESEARCH LICENSE 1.0".
// See accompanying file LICENSE.rst or
// http://www.steinwurf.com/licensing

#pragma once

#include "factory_interface.hpp"
namespace kodo
{
    class encoder_factory_interface : public factory_interface
    {
    public:
        virtual encoder_interface* build() = 0;
    };
}

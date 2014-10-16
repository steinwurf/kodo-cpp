// Copyright Steinwurf ApS 2011-2013.
// Distributed under the "STEINWURF RESEARCH LICENSE 1.0".
// See accompanying file LICENSE.rst or
// http://www.steinwurf.com/licensing

#pragma once

class decoder_factory : public factory
{
public:
    decoder_factory(size_t decoder_type) : factory(decoder_type)
    {

    }

    decoder build()
    {
        return decoder(new decoder_wrapper(m_wrapper.build()));
    }
}

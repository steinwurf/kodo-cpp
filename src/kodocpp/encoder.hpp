// Copyright Steinwurf ApS 2011-2013.
// Distributed under the "STEINWURF RESEARCH LICENSE 1.0".
// See accompanying file LICENSE.rst or
// http://www.steinwurf.com/licensing

#pragma once

#include <cstdint>
#include <cassert>

#include <kodoc/kodoc.h>

#include "coder.hpp"

namespace kodocpp
{
    class encoder: public coder
    {
    public:

        encoder(kodo_coder_t coder_instance) :
            coder(coder_instance)
        {
            assert(m_coder);
        }

        ~encoder()
        {
            kodo_delete_encoder(m_coder);
        }

        void set_symbols(uint8_t* data, uint32_t size)
        {
            kodo_set_symbols(m_coder, data, size);
        }

        void set_symbol(uint32_t index, uint8_t* data, uint32_t size)
        {
            kodo_set_symbol(m_coder, index, data, size);
        }

        bool has_set_systematic_off() const
        {
            return kodo_has_set_systematic_off(m_coder) != 0;
        }

        bool is_systematic_on() const
        {
            return kodo_is_systematic_on(m_coder) != 0;
        }

        void set_systematic_on()
        {
            kodo_set_systematic_on(m_coder);
        }

        void set_systematic_off()
        {
            kodo_set_systematic_off(m_coder);
        }

        void read_feedback(uint8_t* feedback)
        {
            kodo_read_feedback(m_coder, feedback);
        }
    };
}

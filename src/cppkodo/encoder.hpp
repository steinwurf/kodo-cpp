// Copyright Steinwurf ApS 2011-2013.
// Distributed under the "STEINWURF RESEARCH LICENSE 1.0".
// See accompanying file LICENSE.rst or
// http://www.steinwurf.com/licensing

#pragma once

#include "internal/encoder_wrapper.hpp"
#include "coder.hpp"

namespace kodo
{

    class encoder : public coder
    {
    public:
        encoder(encoder_interface* wrapper) : coder(wrapper), m_wrapper(wrapper)
        {

        }

        uint32_t encode(uint8_t* payload);

        void set_symbols(const uint8_t* data, uint32_t size);

        void set_symbol(
            uint32_t index, const uint8_t* data, uint32_t size);

        bool has_systematic_encoder() const;

        bool is_systematic_on() const;

        void set_systematic_on();

        void set_systematic_off();

        void read_feedback(uint8_t* feedback);

    private:
    encoder_interface* m_wrapper;
    };
}

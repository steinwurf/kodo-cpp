// Copyright Steinwurf ApS 2011-2013.
// Distributed under the "STEINWURF RESEARCH LICENSE 1.0".
// See accompanying file LICENSE.rst or
// http://www.steinwurf.com/licensing

#include "internal/encoder_wrapper.hpp"

namespace kodo
{

    class encoder
    {
    public:
        encoder(encoder_interface* wrapper) : m_wrapper(wrapper)
        {

        }

        virtual uint32_t encode(uint8_t* payload);

        virtual void set_symbols(const uint8_t* data, uint32_t size);

        virtual void set_symbol(
            uint32_t index, const uint8_t* data, uint32_t size);

        virtual bool has_systematic_encoder() const;

        virtual bool is_systematic_on() const;

        virtual void set_systematic_on();

        virtual void set_systematic_off();

        virtual void read_feedback(uint8_t* feedback);
    private:
    encoder_interface* m_wrapper;
    };
}

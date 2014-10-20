// Copyright Steinwurf ApS 2011-2013.
// Distributed under the "STEINWURF RESEARCH LICENSE 1.0".
// See accompanying file LICENSE.rst or
// http://www.steinwurf.com/licensing

#include "internal/decoder_wrapper.hpp"

namespace kodo
{
    class decoder
    {
    public:
        decoder(decoder_interface* wrapper) : m_wrapper(wrapper)
        {

        }

        ~decoder_interface() {}

        uint32_t recode(uint8_t* data);
        void decode(uint8_t* data);
        bool is_complete() const;

        void copy_symbols(uint8_t* data, uint32_t size) const;

        void copy_symbol(uint32_t index, uint8_t* data,
                                 uint32_t size) const;

        bool has_partial_decoding_tracker() const;

        bool is_partial_complete() const;
        bool is_symbol_uncoded(uint32_t index) const;

        uint32_t symbols_uncoded() const;
        uint32_t symbols_seen() const;
        void write_feedback(uint8_t* feedback);

    private:
        decoder_wrapper* m_wrapper;
    }
}

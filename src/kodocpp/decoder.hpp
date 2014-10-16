// Copyright Steinwurf ApS 2011-2013.
// Distributed under the "STEINWURF RESEARCH LICENSE 1.0".
// See accompanying file LICENSE.rst or
// http://www.steinwurf.com/licensing

namespace kodo
{
    class decoder
    {
    public:
        decoder(decoder_interface* wrapper) : m_wrapper(wrapper)
        {

        }

        ~decoder_interface() {}

        uint32_t recode(uint8_t* data) = 0;
        void decode(uint8_t* data) = 0;
        bool is_complete() const = 0;

        void copy_symbols(uint8_t* data, uint32_t size) const = 0;

        void copy_symbol(uint32_t index, uint8_t* data,
                                 uint32_t size) const = 0;

        bool has_partial_decoding_tracker() const = 0;

        bool is_partial_complete() const = 0;
        bool is_symbol_uncoded(uint32_t) const = 0;

        uint32_t symbols_uncoded() const = 0;
        uint32_t symbols_seen() const = 0;
        void write_feedback(uint8_t* feedback) = 0;
    private:
        decoder_wrapper* m_wrapper;
    }
}

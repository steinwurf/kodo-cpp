// Copyright Steinwurf ApS 2011-2013.
// Distributed under the "STEINWURF RESEARCH LICENSE 1.0".
// See accompanying file LICENSE.rst or
// http://www.steinwurf.com/licensing

#pragma once

#include <cstdint>

#include <functional>
#include <string>

#include "api_config.hpp"

namespace kodocpp
{
    class decoder_interface;

    class KODOCPP_API decoder
    {
    public:

        decoder(decoder_interface* wrapper);
        ~decoder();

        // Coder methods
        uint32_t block_size() const;
        uint32_t payload_size() const;
        uint32_t rank() const;
        uint32_t symbol_size() const;
        uint32_t symbols() const;
        bool symbol_pivot(uint32_t) const;

        bool has_trace() const;
        void trace(std::function<bool (std::string)>);

        bool has_feedback_size() const;
        uint32_t feedback_size() const;

        // Decoder methods
        uint32_t recode(uint8_t* data);

        void decode(uint8_t* data);

        bool is_complete() const;

        void copy_symbols(uint8_t* data, uint32_t size) const;

        void copy_symbol(uint32_t index, uint8_t* data, uint32_t size) const;

        bool has_partial_decoding_tracker() const;

        bool is_partial_complete() const;
        bool is_symbol_uncoded(uint32_t index) const;

        uint32_t symbols_uncoded() const;
        uint32_t symbols_seen() const;
        void write_feedback(uint8_t* feedback);

    private:

        decoder_interface* m_wrapper;
    };
}

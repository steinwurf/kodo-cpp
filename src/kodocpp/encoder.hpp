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
    class encoder_interface;

    class KODOCPP_API encoder
    {
    public:

        encoder(encoder_interface* wrapper);
        ~encoder();

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

        // Enoder methods
        uint32_t encode(uint8_t* payload);

        void set_symbols(const uint8_t* data, uint32_t size);

        void set_symbol(uint32_t index, const uint8_t* data, uint32_t size);

        bool has_systematic_encoder() const;

        bool is_systematic_on() const;

        void set_systematic_on();

        void set_systematic_off();

        void read_feedback(uint8_t* feedback);

    private:

        encoder_interface* m_wrapper;
    };
}

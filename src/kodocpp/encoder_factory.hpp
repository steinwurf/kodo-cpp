// Copyright Steinwurf ApS 2011-2013.
// Distributed under the "STEINWURF RESEARCH LICENSE 1.0".
// See accompanying file LICENSE.rst or
// http://www.steinwurf.com/licensing

#pragma once

#include <kodo/rlnc/full_rlnc_codes.hpp>
#include <kodo/rlnc/on_the_fly_codes.hpp>

#include <kodo/rlnc/sliding_window_encoder.hpp>
#include <kodo/rlnc/sliding_window_decoder.hpp>



namespace kodo
{
    class encoder_factory
    {
    public:
        encoder_factory(size_t encoder_type, size_t field_type,
                        bool trace_enabled, uint32_t max_symbols,
                        uint32_t max_symbol_size)
        {
            if(encoder_type == kodo_full_rlnc)
            {
                if(trace_enabled)
                {
                    if(field_type == kodo_binary)
                    {
//                        m_encoder<fifi::binary, kodo::enable_trace>
                    }
                }
            }

        }
    private:
        encoder_interface m_encoder;
    }

}

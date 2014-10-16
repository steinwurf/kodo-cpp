// Copyright Steinwurf ApS 2011-2012.
// Distributed under the "STEINWURF RESEARCH LICENSE 1.0".
// See accompanying file LICENSE.rst or
// http://www.steinwurf.com/licensing

#include <iostream>

#include "kodocpp/kodocpp.hpp"

namespace kodo
{
    int main(void)
    {
        //Remember to seed random

        uint32_t max_symbols = 42;
        uint32_t max_symbol_size = 160;

        bool enabled_trace = true;

        encoder_factory encoder_factory = encoder_factory(
            kodo::algorithm.kodo_full_rlnc,
            kodo::field_type.binary,
            max_symbols,
            max_symbol_size,
            enabled_trace);

        encoder encoder = encoder_factory.build();

        decoder_factory decoder_factory = decoder_factory(
            kodo::algorithm.kodo_full_rlnc,
            kodo::field_type.binary,
            max_symbols,
            max_symbol_size,
            enable_trace);

        decoder decoder = decoder_factory.build();

        // Allocate some data to encode. In this case we make a buffer
        // with the same size as the encoder's block size (the max.
        // amount a single encoder can encode)
        ////Change to the encoder :)
        std::vector<uint8_t> data_in(200);

        for(auto &e: data_in)
        {
            e = rand() % 256;
        }
        return 0;
    }
}

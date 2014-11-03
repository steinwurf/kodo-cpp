// Copyright Steinwurf ApS 2014.
// Distributed under the "STEINWURF RESEARCH LICENSE 1.0".
// See accompanying file LICENSE.rst or
// http://www.steinwurf.com/licensing

#include <cstdlib>
#include <ctime>
#include <iostream>
#include <vector>
#include <algorithm>
#include <set>

#include <kodocpp/kodocpp.hpp>

/// @example use_trace_layers.cpp
///
/// Simple example showing how to use some of the trace layers defined
/// in Kodo.

int main(void)
{
    // Seed random number generator to produce different results every time
    srand(static_cast<uint32_t>(time(0)));

    // Set the number of symbols (i.e. the generation size in RLNC
    // terminology) and the size of a symbol in bytes
    uint32_t max_symbols = 8;
    uint32_t max_symbol_size = 33;

    bool trace_enabled = true;

    // Initilization of encoder and decoder
    kodocpp::encoder_factory encoder_factory(
        kodocpp::code_type::full_rlnc,
        kodocpp::finite_field::binary8,
        max_symbols,
        max_symbol_size,
        trace_enabled);

    kodocpp::encoder encoder = encoder_factory.build();

    kodocpp::decoder_factory decoder_factory(
        kodocpp::code_type::full_rlnc,
        kodocpp::finite_field::binary8,
        max_symbols,
        max_symbol_size,
        trace_enabled);

    kodocpp::decoder decoder = decoder_factory.build();

    // Allocate some storage for a "payload" the payload is what we would
    // eventually send over a network
    std::vector<uint8_t> payload(encoder.payload_size());

    // Allocate some data to encode. In this case we make a buffer
    // with the same size as the encoder's block size (the max.
    // amount a single encoder can encode)
    std::vector<uint8_t> data_in(encoder.block_size());

    // Just for fun - fill the data with random data
    std::generate(data_in.begin(), data_in.end(), rand);

    encoder.set_symbols(data_in.data(), encoder.block_size());

    while (!decoder.is_complete())
    {
        encoder.encode(payload.data());

        if (encoder.has_trace())
        {
            std::cout << "Tace encoder:" << std::endl;
            encoder.trace(nullptr);
        }

        if ((rand() % 2) == 0)
        {
            continue;
        }

        decoder.decode(payload.data());

        if (decoder.has_trace())
        {
            // Define filter function
            auto filter = [](const std::string& zone)
            {
                std::set<std::string> filters =
                    {"decoder_state", "input_symbol_coefficients"};
                return filters.count(zone) != 0;
            };

            std::cout << "Trace decoder:" << std::endl;
            decoder.trace(filter);
        }
    }

    std::vector<uint8_t> data_out(decoder.block_size());

    decoder.copy_symbols(data_out.data(), decoder.block_size());

    // Check if we properly decoded the data
    if (std::equal(data_out.begin(), data_out.end(), data_in.begin()))
    {
        std::cout << "Data decoded correctly" << std::endl;
    }
    else
    {
        std::cout << "Unexpected failure to decode, "
                  << "please file a bug report :)" << std::endl;
    }

    return 0;
}

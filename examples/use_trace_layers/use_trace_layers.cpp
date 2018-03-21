// Copyright Steinwurf ApS 2014.
// Distributed under the "STEINWURF EVALUATION LICENSE 1.0".
// See accompanying file LICENSE.rst or
// http://www.steinwurf.com/licensing

/// @example use_trace_layers.cpp
///
/// Simple example showing how to use some of the trace layers defined
/// in Kodo.

#include <cstdint>
#include <cstdlib>
#include <ctime>
#include <algorithm>
#include <iostream>
#include <set>
#include <vector>

#include <kodocpp/kodocpp.hpp>

int main(void)
{
    // Seed random number generator to produce different results every time
    srand((uint32_t)time(0));

    // Set the number of symbols (i.e. the generation size in RLNC
    // terminology) and the size of a symbol in bytes
    uint32_t max_symbols = 6;
    uint32_t max_symbol_size = 32;

    // Initilization of encoder and decoder
    kodocpp::encoder_factory encoder_factory(
        kodocpp::codec::full_vector,
        kodocpp::field::binary8,
        max_symbols,
        max_symbol_size);

    kodocpp::encoder encoder = encoder_factory.build();

    kodocpp::decoder_factory decoder_factory(
        kodocpp::codec::full_vector,
        kodocpp::field::binary8,
        max_symbols,
        max_symbol_size);

    kodocpp::decoder decoder = decoder_factory.build();

    // Allocate some storage for a "payload" the payload is what we would
    // eventually send over a network
    std::vector<uint8_t> payload(encoder.payload_size());

    // Allocate input and output data buffers
    std::vector<uint8_t> data_in(encoder.block_size());
    std::vector<uint8_t> data_out(decoder.block_size());

    // Fill the input buffer with random data
    std::generate(data_in.begin(), data_in.end(), rand);

    // Set the symbol storage for the encoder and decoder
    encoder.set_const_symbols(data_in.data(), encoder.block_size());
    decoder.set_mutable_symbols(data_out.data(), decoder.block_size());

    // Install the default trace function for encoder (writes to stdout)
    encoder.set_trace_stdout();

    // Install a custom trace function for the decoder
    auto callback = [](const std::string& zone, const std::string& data)
    {
        std::set<std::string> filters =
            {
                "decoder_state", "symbol_coefficients_before_read_symbol",
                "symbol_index_before_read_uncoded_symbol"
            };

        if (filters.count(zone))
        {
            std::cout << zone << ":" << std::endl;
            std::cout << data << std::endl;
        }
    };

    decoder.set_trace_callback(callback);

    while (!decoder.is_complete())
    {
        encoder.write_payload(payload.data());

        // Simulate a lossy channel where we are losing 50% of the packets
        if ((rand() % 2) == 0)
        {
            continue;
        }

        decoder.read_payload(payload.data());
    }

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

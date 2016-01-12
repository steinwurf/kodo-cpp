// Copyright Steinwurf ApS 2016.
// Distributed under the "STEINWURF RESEARCH LICENSE 1.0".
// See accompanying file LICENSE.rst or
// http://www.steinwurf.com/licensing

/// @example is_symbol_pivot_counter.cpp
///
/// Simple example showing how to track how many symbols are needed at
/// the decoder before a symbol becomes pivot.

#include <cstdint>
#include <cstdlib>
#include <ctime>
#include <algorithm>
#include <iostream>
#include <vector>

#include <kodocpp/kodocpp.hpp>

int main()
{
    // Seed the random number generator to produce different data every time
    srand((uint32_t)time(0));

    // Set the number of symbols and the symbol size
    uint32_t symbols = 10;
    uint32_t symbol_size = 100;

    // Create encoder/decoder factories that we will use to build the actual
    // encoder and decoder
    kodocpp::encoder_factory encoder_factory(
        kodocpp::codec::full_vector,
        kodocpp::field::binary8,
        symbols, symbol_size);

    kodocpp::encoder encoder = encoder_factory.build();

    kodocpp::decoder_factory decoder_factory(
        kodocpp::codec::full_vector,
        kodocpp::field::binary8,
        symbols, symbol_size);

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

    // Track the number of symbols received before we have a pivot
    std::vector<uint32_t> symbols_until_pivot(symbols, 0U);

    // Install a custom trace function for the decoder
    auto callback = [](const std::string& zone, const std::string& data)
    {
        // To confirm the numbers it can be useful to check what the
        // decoding matrix looks like. Here we use a trace filter to remove
        // everything but the decoder_state (the decoding matrix).

        if (zone == "decoder_state")
        {
            std::cout << zone << ":" << std::endl;
            std::cout << data << std::endl;
        }
    };
    decoder.set_trace_callback(callback);

    while (!decoder.is_complete())
    {
        // Encode a packet into the payload buffer
        encoder.write_payload(payload.data());

        // Lose a packet with 50% probability
        if (rand() % 2)
            continue;

        // For all the packets that are not already pivot, we needed
        // one more packet
        for (uint32_t i = 0; i < symbols; ++i)
        {
            if (!decoder.is_symbol_pivot(i))
            {
                ++symbols_until_pivot[i];
            }
        }

        // Pass that packet to the decoder
        decoder.read_payload(payload.data());
    }

    // Lets print out the result
    for (uint32_t i = 0; i < symbols; ++i)
    {
        std::cout << "index = " << i << " needed symbols = "
                  << symbols_until_pivot[i] << std::endl;
    }

    // Check we properly decoded the data
    if (std::equal(data_out.begin(), data_out.end(), data_in.begin()))
    {
        std::cout << "Data decoded correctly" << std::endl;
    }
    else
    {
        std::cout << "Unexpected failure to decode "
                  << "please file a bug report :)" << std::endl;
    }
}

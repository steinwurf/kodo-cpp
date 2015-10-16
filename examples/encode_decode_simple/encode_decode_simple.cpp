// Copyright Steinwurf ApS 2014.
// Distributed under the "STEINWURF RESEARCH LICENSE 1.0".
// See accompanying file LICENSE.rst or
// http://www.steinwurf.com/licensing

#include <cstdlib>
#include <ctime>
#include <iostream>
#include <vector>
#include <algorithm>

#include <kodocpp/kodocpp.hpp>

/// @example encode_decode_simple.cpp
///
/// Simple example showing how to encode and decode a block of memory.

int main(void)
{
    // Seed random number generator to produce different results every time
    srand(static_cast<uint32_t>(time(0)));

    // Set the number of symbols (i.e. the generation size in RLNC
    // terminology) and the size of a symbol in bytes
    uint32_t max_symbols = 10;
    uint32_t max_symbol_size = 100;

    //Initilization of encoder and decoder
    kodocpp::encoder_factory encoder_factory(
        kodo_full_vector,
        kodo_binary8,
        max_symbols,
        max_symbol_size);

    kodocpp::encoder encoder = encoder_factory.build();

    kodocpp::decoder_factory decoder_factory(
        kodo_full_vector,
        kodo_binary8,
        max_symbols,
        max_symbol_size);

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

    // Assign the data buffer to the encoder so that we may start
    // to produce encoded symbols from it
    encoder.set_const_symbols(data_in.data(), encoder.block_size());

    // Set the storage for the decoder
    std::vector<uint8_t> data_out(decoder.block_size());
    decoder.set_mutable_symbols(data_out.data(), decoder.block_size());

    while (!decoder.is_complete())
    {
        // Encode the packet into the payload buffer
        encoder.write_payload(payload.data());

        // Pass that packet to the decoder
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

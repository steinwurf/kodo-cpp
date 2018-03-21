// Copyright Steinwurf ApS 2014.
// Distributed under the "STEINWURF EVALUATION LICENSE 1.0".
// See accompanying file LICENSE.rst or
// http://www.steinwurf.com/licensing

/// @example symbol_status_updater.cpp
///
/// Simple example showing the result of enabling the symbol status updater.

#include <cstdint>
#include <cstdlib>
#include <ctime>
#include <iostream>
#include <vector>
#include <algorithm>

#include <kodocpp/kodocpp.hpp>

int main(void)
{
    // Seed random number generator to produce different results every time
    srand((uint32_t)time(0));

    // Set the number of symbols (i.e. the generation size in RLNC
    // terminology) and the size of a symbol in bytes
    uint32_t max_symbols = 50;
    uint32_t max_symbol_size = 160;

    // To show the effect of the symbol status updater we need to use a lower
    // sized field - the lower the better.
    auto field = kodocpp::field::binary;

    // Initilization of encoder and decoder
    kodocpp::encoder_factory encoder_factory(
        kodocpp::codec::full_vector,
        field,
        max_symbols,
        max_symbol_size);

    auto encoder = encoder_factory.build();

    kodocpp::decoder_factory decoder_factory(
        kodocpp::codec::full_vector,
        field,
        max_symbols,
        max_symbol_size);

    // create two decoders, one which has the status updater turned on, and one
    // which has it off.
    auto decoder1 = decoder_factory.build();
    auto decoder2 = decoder_factory.build();

    decoder2.set_status_updater_on();

    std::cout << "decoder 1 status updater: "
              << decoder1.is_status_updater_enabled() << std::endl;
    std::cout << "decoder 2 status updater: "
              << decoder2.is_status_updater_enabled() << std::endl;

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

    // Skip the systematic phase as the effect of the symbol status decoder is
    // only visible when reading coded packets.
    encoder.set_systematic_off();

    // Set the storage for the decoder
    std::vector<uint8_t> data_out1(decoder1.block_size());
    decoder1.set_mutable_symbols(data_out1.data(), decoder1.block_size());

    std::vector<uint8_t> data_out2(decoder2.block_size());
    decoder2.set_mutable_symbols(data_out2.data(), decoder2.block_size());

    while (!decoder1.is_complete())
    {
        // Encode the packet into the payload buffer
        encoder.write_payload(payload.data());

        // Pass that packet to the decoder
        auto payload_copy = payload;
        decoder1.read_payload(payload.data());
        decoder2.read_payload(payload_copy.data());
        std::cout << "decoder 1: " << decoder1.symbols_uncoded() << std::endl;
        std::cout << "decoder 2: " << decoder2.symbols_uncoded() << std::endl;
        std::cout << "-----------------" << std::endl;
    }

    // Check if we properly decoded the data
    if (data_out1 == data_in && data_out2 == data_in)
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

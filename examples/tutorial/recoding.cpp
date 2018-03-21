// Copyright Steinwurf ApS 2016.
// Distributed under the "STEINWURF EVALUATION LICENSE 1.0".
// See accompanying file LICENSE.rst or
// http://www.steinwurf.com/licensing

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

    // Set the number of symbols (i.e. the generation size in RLNC
    // terminology) and the size of a symbol in bytes
    uint32_t max_symbols = 16;
    uint32_t max_symbol_size = 1400;

    //! [0]
    // In the following we will make an encoder/decoder factory.
    // The factories are used to build actual encoders/decoders
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

    kodocpp::decoder decoder1 = decoder_factory.build();
    kodocpp::decoder decoder2 = decoder_factory.build();
    //! [1]

    std::vector<uint8_t> payload(encoder.payload_size());
    std::vector<uint8_t> data_in(encoder.block_size());
    // Just for fun - fill the data with random data
    std::generate(data_in.begin(), data_in.end(), rand);
    // Assign the data buffer to the encoder so that we may start
    // to produce encoded symbols from it
    encoder.set_const_symbols(data_in.data(), encoder.block_size());
    // Create a buffer which will contain the decoded data, and we assign
    // that buffer to the decoder
    std::vector<uint8_t> data_out1(decoder1.block_size());
    std::vector<uint8_t> data_out2(decoder2.block_size());
    decoder1.set_mutable_symbols(data_out1.data(), decoder1.block_size());
    decoder2.set_mutable_symbols(data_out2.data(), decoder2.block_size());

    uint32_t encoded_count = 0;
    uint32_t dropped_count = 0;

    // We switch any systematic operations off so the encoder produces
    // coded symbols from the beginning
    if (encoder.is_systematic_on())
        encoder.set_systematic_off();

    //! [2]
    while (!decoder2.is_complete())
    {
        // Encode a packet into the payload buffer
        encoder.write_payload(payload.data());

        ++encoded_count;

        if (rand() % 2)
        {
            ++dropped_count;
        }
        else
        {
            // Pass that packet to the decoder1
            decoder1.read_payload(payload.data());
        }

        // Create a recoded packet from decoder1
        decoder1.write_payload(payload.data());

        if (rand() % 2)
        {
            ++dropped_count;
        }
        else
        {
            // Pass the recoded packet to decoder two
            decoder2.read_payload(payload.data());
        }
    }
    //! [3]
    std::cout << "Encoded count = " << encoded_count << std::endl;
    std::cout << "Dropped count = " << dropped_count << std::endl;

    // Check if we properly decoded the data
    if (data_in == data_out2)
    {
        std::cout << "Data decoded correctly" << std::endl;
    }

    return 0;
}

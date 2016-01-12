// Copyright Steinwurf ApS 2016.
// Distributed under the "STEINWURF RESEARCH LICENSE 1.0".
// See accompanying file LICENSE.rst or
// http://www.steinwurf.com/licensing

#include <cstdint>
#include <algorithm>
#include <iostream>
#include <vector>

#include <kodocpp/kodocpp.hpp>

int main()
{
    //! [0]
    // Set the number of symbols (i.e. the generation size in RLNC
    // terminology) and the size of a symbol in bytes
    uint32_t max_symbols = 16;
    uint32_t max_symbol_size = 1400;
    //! [1]
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

    kodocpp::decoder decoder = decoder_factory.build();
    //! [2]
    std::vector<uint8_t> payload(encoder.payload_size());
    std::vector<uint8_t> data_in(encoder.block_size());

    // Just for fun - fill the data with random data
    std::generate(data_in.begin(), data_in.end(), rand);
    //! [3]
    // Assign the data buffer to the encoder so that we may start
    // to produce encoded symbols from it
    encoder.set_const_symbols(data_in.data(), encoder.block_size());
    //! [4]
    // Create a buffer which will contain the decoded data, and we assign
    // that buffer to the decoder
    std::vector<uint8_t> data_out(decoder.block_size());
    decoder.set_mutable_symbols(data_out.data(), decoder.block_size());
    //! [5]
    uint32_t encoded_count = 0;

    while (!decoder.is_complete())
    {
        // Encode a packet into the payload buffer
        uint32_t bytes_used = encoder.write_payload(payload.data());
        std::cout << "Bytes used = " << bytes_used << std::endl;

        ++encoded_count;

        // Pass that packet to the decoder
        decoder.read_payload(payload.data());
    }

    std::cout << "Encoded count = " << encoded_count << std::endl;
    //! [6]
    // Check if we properly decoded the data
    if (data_in == data_out)
    {
        std::cout << "Data decoded correctly" << std::endl;
    }
    //! [7]
    return 0;
}

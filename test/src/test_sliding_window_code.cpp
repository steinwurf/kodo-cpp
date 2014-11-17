// Copyright Steinwurf ApS 2011-2013.
// Distributed under the "STEINWURF RESEARCH LICENSE 1.0".
// See accompanying file LICENSE.rst or
// http://www.steinwurf.com/licensing

#include <cstdlib>
#include <iostream>
#include <vector>
#include <algorithm>

#include <gtest/gtest.h>

#include <kodocpp/kodocpp.hpp>

void test_basic_api(kodocpp::code_type code_type,
                    kodocpp::finite_field finite_field)
{
    uint32_t max_symbols = 32;
    uint32_t max_symbol_size = 160;
    bool trace_enabled = false;
    //Initilization of encoder and decoder
    kodocpp::encoder_factory encoder_factory(
        code_type,
        finite_field,
        max_symbols,
        max_symbol_size,
        trace_enabled);

    kodocpp::encoder encoder = encoder_factory.build();

    kodocpp::decoder_factory decoder_factory(
        code_type,
        finite_field,
        max_symbols,
        max_symbol_size,
        trace_enabled);

    kodocpp::decoder decoder = decoder_factory.build();

    EXPECT_TRUE(max_symbols == encoder_factory.max_symbols());
    EXPECT_TRUE(max_symbol_size == encoder_factory.max_symbol_size());
    EXPECT_TRUE(max_symbols == encoder.symbols());
    EXPECT_TRUE(max_symbol_size == encoder.symbol_size());

    EXPECT_TRUE(max_symbols == decoder_factory.max_symbols());
    EXPECT_TRUE(max_symbol_size == decoder_factory.max_symbol_size());
    EXPECT_TRUE(max_symbols == decoder.symbols());
    EXPECT_TRUE(max_symbol_size == decoder.symbol_size());

    EXPECT_TRUE(encoder.block_size() == max_symbols * max_symbol_size);
    EXPECT_TRUE(decoder.block_size() == max_symbols * max_symbol_size);

    EXPECT_TRUE(encoder_factory.max_payload_size() >=
                encoder.payload_size());

    EXPECT_TRUE(decoder_factory.max_payload_size() >=
                decoder.payload_size());

    EXPECT_EQ(encoder_factory.max_payload_size(),
              decoder_factory.max_payload_size());

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
    encoder.set_symbols(data_in.data(), encoder.block_size());

    while (!decoder.is_complete())
    {
        // Encode the packet into the payload buffer
        uint32_t payload_used = encoder.encode(payload.data());
        EXPECT_TRUE(payload_used <= encoder.payload_size());

        // Pass that packet to the decoder
        decoder.decode(payload.data());
        EXPECT_TRUE(decoder.is_partial_complete());
    }
    EXPECT_TRUE(decoder.is_complete());

    // The decoder is complete, now copy the symbols from the decoder
    std::vector<uint8_t> data_out(decoder.block_size());
    decoder.copy_symbols(data_out.data(), decoder.block_size());

    // Check if we properly decoded the data
    EXPECT_TRUE(data_out == data_in);
}

TEST(TestSlidingWindowCodes, invoke_api)
{
    test_basic_api(kodocpp::code_type::sliding_window,
                   kodocpp::finite_field::binary);

    test_basic_api(kodocpp::code_type::sliding_window,
                   kodocpp::finite_field::binary8);

    test_basic_api(kodocpp::code_type::sliding_window,
                   kodocpp::finite_field::binary16);
}

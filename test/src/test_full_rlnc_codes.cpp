// Copyright Steinwurf ApS 2011-2013.
// Distributed under the "STEINWURF RESEARCH LICENSE 1.0".
// See accompanying file LICENSE.rst or
// http://www.steinwurf.com/licensing

#include <kodocpp/kodocpp.hpp>

#include <cstdlib>
#include <vector>
#include <algorithm>

#include <gtest/gtest.h>

#include "test_helper.hpp"

void test_basic_api(uint32_t symbols, uint32_t symbol_size,
                    kodo_code_type code_type,
                    kodo_finite_field finite_field)
{
    bool trace_flag = false;

    //Initilization of encoder and decoder
    kodocpp::encoder_factory encoder_factory(
        code_type,
        finite_field,
        symbols,
        symbol_size,
        trace_flag);

    kodocpp::encoder encoder = encoder_factory.build();

    kodocpp::decoder_factory decoder_factory(
        code_type,
        finite_field,
        symbols,
        symbol_size,
        trace_flag);

    kodocpp::decoder decoder = decoder_factory.build();

    EXPECT_TRUE(symbols == encoder_factory.max_symbols());
    EXPECT_TRUE(symbol_size == encoder_factory.max_symbol_size());
    EXPECT_TRUE(symbols == encoder.symbols());
    EXPECT_TRUE(symbol_size == encoder.symbol_size());

    EXPECT_TRUE(symbols == decoder_factory.max_symbols());
    EXPECT_TRUE(symbol_size == decoder_factory.max_symbol_size());
    EXPECT_TRUE(symbols == decoder.symbols());
    EXPECT_TRUE(symbol_size == decoder.symbol_size());

    EXPECT_TRUE(encoder.block_size() == symbols * symbol_size);
    EXPECT_TRUE(decoder.block_size() == symbols * symbol_size);

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
        uint32_t payload_used = encoder.write_payload(payload.data());
        EXPECT_TRUE(payload_used <= encoder.payload_size());

        // Pass that packet to the decoder
        decoder.read_payload(payload.data());
    }
    EXPECT_TRUE(decoder.is_complete());

    // The decoder is complete, now copy the symbols from the decoder
    std::vector<uint8_t> data_out(decoder.block_size());
    decoder.copy_from_symbols(data_out.data(), decoder.block_size());

    // Check if we properly decoded the data
    EXPECT_TRUE(data_out == data_in);
}

TEST(TestFullRlncCodes, invoke_api)
{
    uint32_t max_symbols = rand_symbols();
    uint32_t max_symbol_size = rand_symbol_size();

    test_basic_api(max_symbols, max_symbol_size,
                   kodo_full_rlnc, kodo_binary);

    test_basic_api(max_symbols, max_symbol_size,
                   kodo_full_rlnc, kodo_binary4);

    test_basic_api(max_symbols, max_symbol_size,
                   kodo_full_rlnc, kodo_binary8);

    test_basic_api(max_symbols, max_symbol_size,
                   kodo_full_rlnc, kodo_binary16);
}

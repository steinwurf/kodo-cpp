// Copyright Steinwurf ApS 2016.
// Distributed under the "STEINWURF EVALUATION LICENSE 1.0".
// See accompanying file LICENSE.rst or
// http://www.steinwurf.com/licensing

#include <kodocpp/kodocpp.hpp>

#include <cstdint>
#include <vector>

#include <gtest/gtest.h>

#include "test_helper.hpp"

static void test_read_write_uncoded(
    uint32_t symbols, uint32_t symbol_size,
    kodocpp::codec codec, kodocpp::field finite_field)
{
    using namespace kodocpp;

    // Initilization of encoder and decoder
    encoder_factory encoder_factory(codec, finite_field, symbols, symbol_size);

    decoder_factory decoder_factory(codec, finite_field, symbols, symbol_size);

    encoder encoder = encoder_factory.build();
    decoder decoder = decoder_factory.build();

    EXPECT_EQ(symbols, encoder_factory.max_symbols());
    EXPECT_EQ(symbol_size, encoder_factory.max_symbol_size());
    EXPECT_EQ(symbols, encoder.symbols());
    EXPECT_EQ(symbol_size, encoder.symbol_size());

    EXPECT_EQ(symbols, decoder_factory.max_symbols());
    EXPECT_EQ(symbol_size, decoder_factory.max_symbol_size());
    EXPECT_EQ(symbols, decoder.symbols());
    EXPECT_EQ(symbol_size, decoder.symbol_size());

    EXPECT_EQ(symbols * symbol_size, encoder.block_size());
    EXPECT_EQ(symbols * symbol_size, decoder.block_size());

    EXPECT_GE(encoder_factory.max_payload_size(), encoder.payload_size());
    EXPECT_GE(decoder_factory.max_payload_size(), decoder.payload_size());

    std::vector<uint8_t> payload(encoder.payload_size());
    std::vector<uint8_t> test_symbol(symbol_size);

    // Allocate symbols in non-contiguous buffers
    std::vector<std::vector<uint8_t>> input_symbols(symbols);
    std::vector<std::vector<uint8_t>> output_symbols(symbols);

    uint32_t i, j;
    // Create the original symbols and store them in the encoder
    for (i = 0; i < symbols; ++i)
    {
        // Create the individual symbols for the encoder
        input_symbols[i].resize(symbol_size);

        // Randomize input data
        for (j = 0; j < symbol_size; ++j)
            input_symbols[i][j] = rand() % 256;

        // Store the symbol pointer in the encoder
        encoder.set_const_symbol(i, input_symbols[i].data(), symbol_size);
    }

    // Transfer the original symbols to the decoder with some losses
    uint32_t lost_symbols = 0;
    for (i = 0; i < symbols; ++i)
    {
        // Create the output symbol buffers for the decoder
        output_symbols[i].resize(symbol_size);

        // Specify the output buffers used for decoding
        decoder.set_mutable_symbol(i, output_symbols[i].data(), symbol_size);

        // Simulate a channel with a 50% loss rate
        if (rand() % 2)
        {
            lost_symbols++;
            continue;
        }

        // We test that write_uncoded_symbol() writes the original symbol
        // to the test buffer
        encoder.write_uncoded_symbol(test_symbol.data(), i);
        // Compare input_symbols[i] with test_symbol
        EXPECT_EQ(input_symbols[i], test_symbol);

        // If the symbol was not lost, then insert that symbol into the decoder
        // using the raw symbol data (no additional headers are needed)
        // This will copy the data from input_symbols[i] to output_symbols[i]
        decoder.read_uncoded_symbol(input_symbols[i].data(), i);

        EXPECT_EQ(i + 1 - lost_symbols, decoder.rank());
    }

    // Now we generate coded packets with the encoder in order to recover the
    // lost packets on the decoder side
    while (!decoder.is_complete())
    {
        encoder.write_payload(payload.data());
        decoder.read_payload(payload.data());
    }

    EXPECT_TRUE(decoder.is_complete());

    // Compare the input and output symbols one-by-one
    for (i = 0; i < symbols; ++i)
    {
        EXPECT_EQ(input_symbols[i], output_symbols[i]);
    }
}

TEST(test_read_write_uncoded_symbol, uncoded_symbols)
{
    using namespace kodocpp;

    if (has_codec(codec::full_vector) == false)
        return;

    uint32_t symbols = rand_symbols();
    uint32_t symbol_size = rand_symbol_size();

    test_read_write_uncoded(
        symbols, symbol_size, codec::full_vector, field::binary);

    test_read_write_uncoded(
        symbols, symbol_size, codec::full_vector, field::binary4);

    test_read_write_uncoded(
        symbols, symbol_size, codec::full_vector, field::binary8);
}

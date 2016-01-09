// Copyright Steinwurf ApS 2016.
// Distributed under the "STEINWURF RESEARCH LICENSE 1.0".
// See accompanying file LICENSE.rst or
// http://www.steinwurf.com/licensing

#include <kodocpp/kodocpp.hpp>

#include <algorithm>
#include <cstdint>
#include <vector>

#include <gtest/gtest.h>

#include "test_helper.hpp"

static void test_read_write_symbol(
    uint32_t symbols, uint32_t symbol_size,
    kodoc_codec codec, kodoc_finite_field finite_field)
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

    std::vector<uint8_t> coded_symbol(symbol_size);

    // Allocate symbols in non-contiguous buffers
    std::vector<std::vector<uint8_t>> input_symbols(symbols);
    std::vector<std::vector<uint8_t>> output_symbols(symbols);

    // To illustrate decoding, random data has been filled into the
    // matrices below. It is crucial that the equation below is correct
    // if the purpose is to test if the decoder decodes correctly as this
    // example evaluates in the end of the example.
    //
    // For additional information, please see the article
    //
    //   Christina Fragouli, Jean-Yves Le Boudec, and Jörg Widmer.
    //   Network Coding: An Instant Primer.
    //   SIGCOMM Comput. Commun. Rev., 36(1):63-68, January 2006.
    //
    // from which the notation in the example is based on.
    //
    //
    //
    // original_symbols (M):    Symbols we expect to obtain from decoding
    //                          encoded_symbols using the symbol_coefficients.
    // symbol_coefficients (G): Coefficients used to encode/decode between
    //                          original_symbols and encoded_symbols.
    // encoded_symbols (X):     Symbols that has been encoded from
    //                          original_symbols using the symbol_coefficients.
    //
    //
    //                          X = G M
    //
    //                        X^j = sum_{i=1}^{n} g_i^j M^i
    //
    //                |   X^1   |   | g^1_1 g^1_2 g^1_3 | |   M^1   |
    //                |   X^2   | = | g^2_1 g^2_2 g^2_3 | |   M^2   |
    //                |   X^3   |   | g^3_1 g^3_2 g^3_3 | |   M^3   |
    //
    //       | encoded symbol 1 |   | encoding vect 1 | | original symbol 1 |
    //       | encoded symbol 2 | = | encoding vect 2 | | original symbol 2 |
    //       | encoded symbol 3 |   | encoding vect 3 | | original symbol 3 |
    //
    //        | 0 1 0 1 1 1 0 0 |   | 0 1 0 | | 1 1 1 0 1 1 0 1 |
    //        | 1 0 1 1 0 0 0 1 | = | 1 1 0 | | 0 1 0 1 1 1 0 0 |
    //        | 0 1 1 0 1 0 1 1 |   | 1 0 1 | | 1 0 0 0 0 1 1 0 |
    //
    // From the above matrix, the first encoded symbol is just the second
    // original symbol M_2. The second encoded symbol is M_1 bitwise xor M_2,
    // and the third encoded symbol is M_1 bitwise xor M_3.

    // The computer reads the bits in the opposite direction of how the
    // elements are written matematically in the matrices above.
    // Therefore, it may be easier to find the hex values, which we input into
    // the variables below, if the matrices above are rewritten with the bits
    // in the direction which they are stored in memory. This is shown in the
    // matrices below:
    //
    //        | 0 0 1 1 1 0 1 0 |   | 0 1 0 | | 1 0 1 1 0 1 1 1 |
    //        | 1 0 0 0 1 1 0 1 | = | 0 1 1 | | 0 0 1 1 1 0 1 0 |
    //        | 1 1 0 1 0 1 1 0 |   | 1 0 1 | | 0 1 1 0 0 0 0 1 |

    uint8_t original_symbols[] = { 0xb7, 0x3a, 0x61 };
    uint8_t symbol_coefficients[] = { 0x02, 0x03, 0x05 };
    uint8_t encoded_symbols[] = { 0x3a, 0x8d, 0xd6 };

    uint32_t i, j;
    // Initialize the symbol storage of the encoder and decoder
    for (i = 0; i < symbols; ++i)
    {
        // Create the individual symbols for the encoder
        input_symbols[i].resize(symbol_size);

        // Use the predefined input data
        for (j = 0; j < symbol_size; ++j)
            input_symbols[i][j] = original_symbols[i];

        // Store the symbol pointer in the encoder
        encoder.set_const_symbol(i, input_symbols[i].data(), symbol_size);

        // Create the output symbol buffers for the decoder
        output_symbols[i].resize(symbol_size);

        // Specify the output buffers used for decoding
        decoder.set_mutable_symbol(i, output_symbols[i].data(), symbol_size);
    }

    EXPECT_FALSE(decoder.is_complete());

    // Generate coded symbols and feed them to the decoder
    for (i = 0; i < symbols; ++i)
    {
        encoder.write_symbol(coded_symbol.data(), &symbol_coefficients[i]);

        // We test that write_symbol() writes the pre-computed symbol
        // to the coded_symbol buffer
        EXPECT_TRUE(std::equal(coded_symbol.begin(), coded_symbol.end(),
                               &encoded_symbols[i]));

        // Pass the i'th symbol and coefficients to decoder
        decoder.read_symbol(coded_symbol.data(), &symbol_coefficients[i]);

        EXPECT_EQ(i + 1, decoder.rank());
    }

    EXPECT_TRUE(decoder.is_complete());

    // Compare the input and output symbols one-by-one
    for (i = 0; i < symbols; ++i)
    {
        EXPECT_EQ(input_symbols[i], output_symbols[i]);
    }
}

TEST(test_read_write_symbol, uncoded_symbols)
{
    using namespace kodocpp;

    if (has_codec(kodoc_full_vector) == false)
        return;

    uint32_t symbols = rand_symbols();
    uint32_t symbol_size = rand_symbol_size();

    test_read_write_symbol(3, 1, kodoc_full_vector, kodoc_binary);
}

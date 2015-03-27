// Copyright Steinwurf ApS 2014.
// Distributed under the "STEINWURF RESEARCH LICENSE 1.0".
// See accompanying file LICENSE.rst or
// http://www.steinwurf.com/licensing

#include <kodocpp/kodocpp.hpp>

#include <cstdint>
#include <vector>
#include <algorithm>

#include <gtest/gtest.h>

#include "test_helper.hpp"

void test_on_the_fly(uint32_t max_symbols, uint32_t max_symbol_size,
                     kodo_code_type code_type,
                     kodo_finite_field finite_field)
{
    bool trace_enabled = false;

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

    uint32_t payload_size = encoder.payload_size();
    std::vector<uint8_t> payload(payload_size);

    uint32_t block_size = encoder.block_size();
    std::vector<uint8_t> data_in(block_size);
    std::vector<uint8_t> data_out(block_size);

    std::generate(data_in.begin(), data_in.end(), rand);

    EXPECT_TRUE(decoder.is_complete() == 0);

    while (!decoder.is_complete())
    {
        EXPECT_GE(encoder.rank(), decoder.rank());

        // Randomly choose to add a new symbol (with 50% probability)
        // if the encoder rank is less than the maximum number of symbols
        if ((rand() % 2) && encoder.rank() < encoder.symbols())
        {
            // The rank of an encoder  indicates how many symbols have been
            // added, i.e. how many symbols are available for encoding
            uint32_t rank = encoder.rank();

            // Calculate the offset to the next symbol to insert
            uint8_t* symbol = data_in.data() + (rank * encoder.symbol_size());

            encoder.set_symbol(rank, symbol, encoder.symbol_size());
        }

        encoder.write_payload(payload.data());

        if (rand() % 2)
        {
            continue;
        }

        decoder.read_payload(payload.data());

        // Check if the decoder is partially complete
        // The decoder has to support partial decoding tracker for
        // on-the-fly decoding
        if (decoder.has_partial_decoding_tracker() &&
            decoder.is_partial_complete())
        {
            for (uint32_t i = 0; i < decoder.symbols(); ++i)
            {
                if (decoder.is_symbol_uncoded(i))
                {
                    uint8_t* original = data_in.data() + i * max_symbol_size;
                    uint8_t* target = data_out.data() + i * max_symbol_size;

                    // Copy the decoded symbol and verify it against the
                    // original data
                    decoder.copy_symbol(i, target, max_symbol_size);
                    EXPECT_EQ(memcmp(original, target, max_symbol_size), 0);
                }
            }
        }
    }

    decoder.copy_symbols(data_out.data(), block_size);

    EXPECT_TRUE(std::equal(data_out.begin(), data_out.end(), data_in.begin()));
}

TEST(TestOnTheFlyCodes, invoke_api)
{
    uint32_t max_symbols = rand_symbols();
    uint32_t max_symbol_size = rand_symbol_size();

    test_on_the_fly(max_symbols, max_symbol_size,
                    kodo_on_the_fly,
                    kodo_binary);

    test_on_the_fly(max_symbols, max_symbol_size,
                    kodo_on_the_fly,
                    kodo_binary8);

    test_on_the_fly(max_symbols, max_symbol_size,
                    kodo_on_the_fly,
                    kodo_binary16);
}

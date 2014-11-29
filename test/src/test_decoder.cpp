// Copyright Steinwurf ApS 2014.
// Distributed under the "STEINWURF RESEARCH LICENSE 1.0".
// See accompanying file LICENSE.rst or
// http://www.steinwurf.com/licensing

#include <kodocpp/decoder.hpp>

#include <cstdint>

#include <gtest/gtest.h>

#include "test_helper.hpp"

static void test_decoder(uint32_t symbols, uint32_t symbol_size,
                         kodocpp::code_type code_type,
                         kodocpp::finite_field finite_field,
                         bool trace_enabled)
{
    kodocpp::decoder_factory decoder_factory(
        code_type,
        finite_field,
        symbols,
        symbol_size,
        trace_enabled);

    kodocpp::decoder decoder = decoder_factory.build();

    // Coder methods

    EXPECT_EQ(symbols, decoder.symbols());
    EXPECT_EQ(symbol_size, decoder.symbol_size());
    EXPECT_EQ(symbols * symbol_size, decoder.block_size());
    EXPECT_GT(decoder.payload_size(), symbol_size);
    EXPECT_EQ(0U, decoder.rank());

    if (code_type == kodocpp::code_type::full_rlnc ||
        code_type == kodocpp::code_type::on_the_fly)
    {
        EXPECT_FALSE(decoder.has_feedback_size());
    }
    else if (code_type == kodocpp::code_type::sliding_window)
    {
        EXPECT_TRUE(decoder.has_feedback_size());
        EXPECT_GT(decoder.feedback_size(), 0U);
    }

    EXPECT_EQ(trace_enabled, decoder.has_trace());


    // Decoder methods

    if (code_type == kodocpp::code_type::on_the_fly ||
        code_type == kodocpp::code_type::sliding_window)
    {
        EXPECT_TRUE(decoder.has_partial_decoding_tracker());
    }
    else if (code_type == kodocpp::code_type::full_rlnc)
    {
        EXPECT_FALSE(decoder.has_partial_decoding_tracker());
    }
}

TEST(TestDecoder, invoke_api)
{
    uint32_t symbols = 32;
    uint32_t symbol_size = 160;

    test_combinations(
        test_decoder,
        symbols, symbol_size, false);

    test_combinations(
        test_decoder,
        symbols, symbol_size, true);
}

// Copyright Steinwurf ApS 2014.
// Distributed under the "STEINWURF RESEARCH LICENSE 1.0".
// See accompanying file LICENSE.rst or
// http://www.steinwurf.com/licensing

#include <kodocpp/encoder.hpp>

#include <cstdint>

#include <gtest/gtest.h>

#include "test_helper.hpp"

static void test_encoder(uint32_t symbols, uint32_t symbol_size,
                         kodocpp::code_type code_type,
                         kodocpp::finite_field finite_field,
                         bool trace_enabled)
{
    kodocpp::encoder_factory encoder_factory(
        code_type,
        finite_field,
        symbols,
        symbol_size,
        trace_enabled);

    kodocpp::encoder encoder = encoder_factory.build();

    // Coder methods

    EXPECT_EQ(symbols, encoder.symbols());
    EXPECT_EQ(symbol_size, encoder.symbol_size());
    EXPECT_EQ(symbols * symbol_size, encoder.block_size());
    EXPECT_GT(encoder.payload_size(), symbol_size);
    EXPECT_EQ(0U, encoder.rank());

    if (code_type == kodocpp::code_type::full_rlnc ||
        code_type == kodocpp::code_type::on_the_fly)
    {
        EXPECT_FALSE(encoder.has_feedback_size());
    }
    else if (code_type == kodocpp::code_type::sliding_window)
    {
        EXPECT_TRUE(encoder.has_feedback_size());

        EXPECT_GT(encoder.feedback_size(), 0U);
    }

    EXPECT_EQ(trace_enabled, encoder.has_trace());


    // Enoder methods

    EXPECT_TRUE(encoder.has_systematic_encoder());

    EXPECT_TRUE(encoder.is_systematic_on());
    encoder.set_systematic_off();
    EXPECT_FALSE(encoder.is_systematic_on());
    encoder.set_systematic_on();
    EXPECT_TRUE(encoder.is_systematic_on());
}

TEST(TestEncoder, invoke_api)
{
    uint32_t symbols = 32;
    uint32_t symbol_size = 160;

    test_combinations(
        test_encoder,
        symbols, symbol_size, false);

    test_combinations(
        test_encoder,
        symbols, symbol_size, true);
}

// Copyright Steinwurf ApS 2014.
// Distributed under the "STEINWURF RESEARCH LICENSE 1.0".
// See accompanying file LICENSE.rst or
// http://www.steinwurf.com/licensing

#include <kodocpp/encoder.hpp>

#include <cstdint>

#include <gtest/gtest.h>

#include "test_helper.hpp"

namespace kodocpp
{
namespace
{
    void test_encoder(uint32_t symbols, uint32_t symbol_size,
        kodo_code_type code_type, kodo_finite_field finite_field,
        bool trace_enabled)
    {
        encoder_factory encoder_factory(
            code_type,
            finite_field,
            symbols,
            symbol_size,
            trace_enabled);

        encoder encoder = encoder_factory.build();

        // Coder methods

        EXPECT_EQ(symbols, encoder.symbols());
        EXPECT_EQ(symbol_size, encoder.symbol_size());
        EXPECT_EQ(symbols * symbol_size, encoder.block_size());
        EXPECT_GT(encoder.payload_size(), symbol_size);
        EXPECT_EQ(0U, encoder.rank());

        if (code_type == kodo_full_vector ||
            code_type == kodo_on_the_fly)
        {
            EXPECT_FALSE(encoder.has_feedback_size());
        }
        else if (code_type == kodo_sliding_window)
        {
            EXPECT_TRUE(encoder.has_feedback_size());

            EXPECT_GT(encoder.feedback_size(), 0U);
        }

        EXPECT_EQ(trace_enabled, encoder.has_set_trace_stdout());
        EXPECT_EQ(trace_enabled, encoder.has_set_trace_callback());
        EXPECT_EQ(trace_enabled, encoder.has_set_trace_off());
        if (trace_enabled)
        {
            encoder.set_trace_stdout();
            encoder.set_trace_off();
        }

        // Encoder methods

        if (encoder.has_set_systematic_off())
        {
            EXPECT_TRUE(encoder.is_systematic_on());
            encoder.set_systematic_off();
            EXPECT_FALSE(encoder.is_systematic_on());
            encoder.set_systematic_on();
            EXPECT_TRUE(encoder.is_systematic_on());
        }
    }
}
}

TEST(test_encoder, invoke_api)
{
    uint32_t symbols = kodocpp::rand_symbols();
    uint32_t symbol_size = kodocpp::rand_symbol_size();

    kodocpp::test_combinations(
        kodocpp::test_encoder,
        symbols, symbol_size, false);

    kodocpp::test_combinations(
        kodocpp::test_encoder,
        symbols, symbol_size, true);
}

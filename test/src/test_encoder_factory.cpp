// Copyright Steinwurf ApS 2014.
// Distributed under the "STEINWURF RESEARCH LICENSE 1.0".
// See accompanying file LICENSE.rst or
// http://www.steinwurf.com/licensing

#include <kodocpp/encoder_factory.hpp>

#include <cstdint>

#include <gtest/gtest.h>

#include "test_helper.hpp"

static void test_encoder_factory(uint32_t max_symbols, uint32_t max_symbol_size,
                                 kodo_code_type code_type,
                                 kodo_finite_field finite_field,
                                 bool trace_enabled)
{
    kodocpp::encoder_factory encoder_factory(
        code_type,
        finite_field,
        max_symbols,
        max_symbol_size,
        trace_enabled);

    // Test the max_* properties
    EXPECT_EQ(max_symbols, encoder_factory.max_symbols());
    EXPECT_EQ(max_symbol_size, encoder_factory.max_symbol_size());
    EXPECT_EQ(max_symbol_size * max_symbols,
              encoder_factory.max_block_size());
    EXPECT_GT(encoder_factory.max_payload_size(), max_symbol_size);

    // Build an encoder with the default settings
    auto encoder = encoder_factory.build();

    EXPECT_EQ(max_symbols, encoder.symbols());
    EXPECT_EQ(max_symbol_size, encoder.symbol_size());

    // Lower the number of symbols and the symbol_size
    uint32_t new_symbols = max_symbols / 2;
    encoder_factory.set_symbols(new_symbols);

    uint32_t new_symbol_size = max_symbol_size - 4;
    encoder_factory.set_symbol_size(new_symbol_size);

    // Test that the max_* properties are not changed
    EXPECT_EQ(max_symbols, encoder_factory.max_symbols());
    EXPECT_EQ(max_symbol_size, encoder_factory.max_symbol_size());
    EXPECT_EQ(max_symbol_size * max_symbols,
              encoder_factory.max_block_size());
    EXPECT_GT(encoder_factory.max_payload_size(), max_symbol_size);

    // Build an encoder with the changed settings
    auto encoder2 = encoder_factory.build();

    EXPECT_EQ(new_symbols, encoder2.symbols());
    EXPECT_EQ(new_symbol_size, encoder2.symbol_size());
}

TEST(TestEncoderFactory, invoke_api)
{
    // Make sure that we can lower these values in the test
    uint32_t max_symbols = rand_symbols() + 1;
    uint32_t max_symbol_size = rand_symbol_size() + 4;

    test_combinations(
        test_encoder_factory,
        max_symbols, max_symbol_size, false);
}

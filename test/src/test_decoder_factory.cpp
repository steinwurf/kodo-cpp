// Copyright Steinwurf ApS 2014.
// Distributed under the "STEINWURF RESEARCH LICENSE 1.0".
// See accompanying file LICENSE.rst or
// http://www.steinwurf.com/licensing

#include <kodocpp/decoder_factory.hpp>

#include <cstdint>

#include <gtest/gtest.h>

#include "test_helper.hpp"

namespace kodocpp
{
namespace
{
    void test_decoder_factory(uint32_t max_symbols, uint32_t max_symbol_size,
        kodo_code_type code_type, kodo_finite_field finite_field,
        bool trace_enabled)
    {
        decoder_factory decoder_factory(
            code_type,
            finite_field,
            max_symbols,
            max_symbol_size,
            trace_enabled);

        // Test the max_* properties
        EXPECT_EQ(max_symbols, decoder_factory.max_symbols());
        EXPECT_EQ(max_symbol_size, decoder_factory.max_symbol_size());
        EXPECT_EQ(max_symbol_size * max_symbols,
                  decoder_factory.max_block_size());
        EXPECT_GT(decoder_factory.max_payload_size(), max_symbol_size);

        // Build an decoder with the default settings
        auto decoder = decoder_factory.build();

        EXPECT_EQ(max_symbols, decoder.symbols());
        EXPECT_EQ(max_symbol_size, decoder.symbol_size());

        // Lower the number of symbols and the symbol_size
        uint32_t new_symbols = max_symbols / 2;
        decoder_factory.set_symbols(new_symbols);

        uint32_t new_symbol_size = max_symbol_size - 4;
        decoder_factory.set_symbol_size(new_symbol_size);

        // Test that the max_* properties are not changed
        EXPECT_EQ(max_symbols, decoder_factory.max_symbols());
        EXPECT_EQ(max_symbol_size, decoder_factory.max_symbol_size());
        EXPECT_EQ(max_symbol_size * max_symbols,
                  decoder_factory.max_block_size());
        EXPECT_GT(decoder_factory.max_payload_size(), max_symbol_size);

        // Build an decoder with the changed settings
        auto decoder2 = decoder_factory.build();

        EXPECT_EQ(new_symbols, decoder2.symbols());
        EXPECT_EQ(new_symbol_size, decoder2.symbol_size());
    }
}
}

TEST(test_decoder_factory, invoke_api)
{
    // Make sure that we can lower these values in the test
    uint32_t max_symbols = kodocpp::rand_symbols() + 1;
    uint32_t max_symbol_size = kodocpp::rand_symbol_size() + 4;

    kodocpp::test_combinations(
        kodocpp::test_decoder_factory,
        max_symbols, max_symbol_size, false);
}

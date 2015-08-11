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
    void test_encoder(uint32_t max_symbols, uint32_t max_symbol_size,
        kodo_code_type code_type, kodo_finite_field finite_field,
        bool trace)
    {
        encoder_factory encoder_factory(
            code_type,
            finite_field,
            max_symbols,
            max_symbol_size,
            trace);

        encoder encoder = encoder_factory.build();
        test_coder(encoder, max_symbols, max_symbol_size, code_type, trace);

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
    uint32_t max_symbols = kodocpp::rand_symbols();
    uint32_t max_symbol_size = kodocpp::rand_symbol_size();

    kodocpp::test_combinations(kodocpp::test_encoder, max_symbols,
        max_symbol_size, false);

    kodocpp::test_combinations(kodocpp::test_encoder, max_symbols,
        max_symbol_size, true);
}

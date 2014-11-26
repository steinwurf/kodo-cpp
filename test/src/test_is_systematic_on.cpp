// Copyright Steinwurf ApS 2014.
// Distributed under the "STEINWURF RESEARCH LICENSE 1.0".
// See accompanying file LICENSE.rst or
// http://www.steinwurf.com/licensing

#include <cstdint>

#include <gtest/gtest.h>

#include <kodocpp/kodocpp.hpp>

#include "test_helper.hpp"

void test_is_systematic_on_encoder(uint32_t symbols, uint32_t symbol_size,
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

    auto encoder = encoder_factory.build();

    EXPECT_TRUE(encoder.is_systematic_on());
    encoder.set_systematic_off();
    EXPECT_FALSE(encoder.is_systematic_on());
}

TEST(TextIsSystematicOn, invoke_api)
{
    uint32_t max_symbols = 32;
    uint32_t max_symbol_size = 160;

    test_encoder_combinations(
        test_is_systematic_on_encoder,
        max_symbols, max_symbol_size, false);
}

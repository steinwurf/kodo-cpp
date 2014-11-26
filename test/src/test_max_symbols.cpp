// Copyright Steinwurf ApS 2014.
// Distributed under the "STEINWURF RESEARCH LICENSE 1.0".
// See accompanying file LICENSE.rst or
// http://www.steinwurf.com/licensing

#include <cstdint>

#include <gtest/gtest.h>

#include <kodocpp/kodocpp.hpp>

#include "test_helper.hpp"

void test_max_symbols_encoder(uint32_t max_symbols, uint32_t max_symbol_size,
                        kodocpp::code_type code_type,
                        kodocpp::finite_field finite_field,
                        bool trace_enabled)
{
    kodocpp::encoder_factory encoder_factory(
        code_type,
        finite_field,
        max_symbols,
        max_symbol_size,
        trace_enabled);

    auto encoder = encoder_factory.build();

    uint32_t new_symbols = 30;
    encoder_factory.set_symbols(new_symbols);

    EXPECT_EQ(max_symbols, encoder_factory.max_symbols());
}

void test_max_symbols_decoder(uint32_t max_symbols, uint32_t max_symbol_size,
                        kodocpp::code_type code_type,
                        kodocpp::finite_field finite_field,
                        bool trace_enabled)
{
    kodocpp::decoder_factory decoder_factory(
        code_type,
        finite_field,
        max_symbols,
        max_symbol_size,
        trace_enabled);

    auto decoder = decoder_factory.build();

    uint32_t new_symbols = 30;
    decoder_factory.set_symbols(new_symbols);

    EXPECT_EQ(max_symbols, decoder_factory.max_symbols());

}


TEST(TestMaxSymbols, invoke_api)
{
    //This is what is expectede for coder.symbol_size()
    uint32_t max_symbols = 32;
    uint32_t max_symbol_size = 160;

    test_encoder_combinations(
        test_max_symbols_encoder,
        max_symbols, max_symbol_size, false);

    test_decoder_combinations(
        test_max_symbols_decoder,
        max_symbols, max_symbol_size, false);
}

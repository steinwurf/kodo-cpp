// Copyright Steinwurf ApS 2014.
// Distributed under the "STEINWURF RESEARCH LICENSE 1.0".
// See accompanying file LICENSE.rst or
// http://www.steinwurf.com/licensing

#include <cstdint>

#include <gtest/gtest.h>

#include <kodocpp/kodocpp.hpp>

#include "test_helper.hpp"

void test_set_symbols_encoder(uint32_t symbols, uint32_t symbol_size,
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

    uint32_t new_symbols = 30;
    encoder_factory.set_symbols(new_symbols);

    auto encoder_2 = encoder_factory.build();

    EXPECT_EQ(new_symbols, encoder_2.symbols());
}

void test_set_symbols_decoder(uint32_t symbols, uint32_t symbol_size,
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

    auto decoder = decoder_factory.build();

    uint32_t new_symbols = 30;
    decoder_factory.set_symbols(new_symbols);

    auto decoder_2 = decoder_factory.build();

    EXPECT_EQ(new_symbols, decoder_2.symbols());

}


TEST(TestSetSymbols, invoke_api)
{
    //This is what is expectede for coder.symbol_size()
    uint32_t max_symbols = 32;
    uint32_t max_symbol_size = 160;

    test_encoder_combinations(
        test_set_symbols_encoder,
        max_symbols, max_symbol_size, false);

    test_encoder_combinations(
        test_set_symbols_decoder,
        max_symbols, max_symbol_size, false);
}

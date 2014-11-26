// Copyright Steinwurf ApS 2014.
// Distributed under the "STEINWURF RESEARCH LICENSE 1.0".
// See accompanying file LICENSE.rst or
// http://www.steinwurf.com/licensing

#include <cstdint>

#include <gtest/gtest.h>

#include <kodocpp/kodocpp.hpp>

#include "test_helper.hpp"

void test_has_trace_encoder(uint32_t symbols, uint32_t symbol_size,
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
    EXPECT_EQ(trace_enabled, encoder.has_trace());
}

void test_has_trace_decoder(uint32_t symbols, uint32_t symbol_size,
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
    EXPECT_EQ(trace_enabled, decoder.has_trace());
}

TEST(TestHasTrace, detect)
{
    uint32_t max_symbols = 32;
    uint32_t max_symbol_size = 160;

    bool trace_enabled = true;

    test_encoder_combinations(
        test_has_trace_encoder,
        max_symbols, max_symbol_size, trace_enabled);

    test_decoder_combinations(
        test_has_trace_decoder,
        max_symbols, max_symbol_size, trace_enabled);

    trace_enabled = false;

    test_encoder_combinations(
        test_has_trace_encoder,
        max_symbols, max_symbol_size, trace_enabled);

    test_decoder_combinations(
        test_has_trace_decoder,
        max_symbols, max_symbol_size, trace_enabled);

}

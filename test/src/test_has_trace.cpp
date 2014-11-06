// Copyright Steinwurf ApS 2014.
// Distributed under the "STEINWURF RESEARCH LICENSE 1.0".
// See accompanying file LICENSE.rst or
// http://www.steinwurf.com/licensing

#include <gtest/gtest.h>

#include <cstdint>

#include <kodocpp/kodocpp.hpp>

void test_trace_encoder(uint32_t symbols, uint32_t symbol_size,
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
    EXPECT_FALSE(encoder.has_trace());
}

TEST(TestHasTrace, detect)
{
    uint32_t max_symbols = 8;
    uint32_t max_symbol_size = 33;
    bool trace_enabled = true;
    test_trace_encoder(max_symbols,
                       max_symbol_size,
                       kodocpp::code_type::full_rlnc,
                       kodocpp::finite_field::binary8,
                       trace_enabled);

}

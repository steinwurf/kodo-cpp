// Copyright Steinwurf ApS 2014.
// Distributed under the "STEINWURF RESEARCH LICENSE 1.0".
// See accompanying file LICENSE.rst or
// http://www.steinwurf.com/licensing

#include <cstdint>

#include <gtest/gtest.h>

#include <kodocpp/kodocpp.hpp>

#include "test_helper.hpp"

void test_has_partial_decoding_tracker_decoder(
    uint32_t symbols,
    uint32_t symbol_size,
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

    if (code_type == kodocpp::code_type::full_rlnc)
    {
        EXPECT_FALSE(decoder.has_partial_decoding_tracker());
    }
    else if (code_type == kodocpp::code_type::on_the_fly ||
             code_type == kodocpp::code_type::sliding_window)
    {
        EXPECT_TRUE(decoder.has_partial_decoding_tracker());
    }
}


TEST(TestHasPartialDecodingTracker, invoke_api)
{
    uint32_t max_symbols = 32;
    uint32_t max_symbol_size = 160;

    test_decoder_combinations(
        test_has_partial_decoding_tracker_decoder,
        max_symbols, max_symbol_size, false);
}

// Copyright Steinwurf ApS 2014.
// Distributed under the "STEINWURF RESEARCH LICENSE 1.0".
// See accompanying file LICENSE.rst or
// http://www.steinwurf.com/licensing

#include <kodocpp/decoder.hpp>

#include <cstdint>

#include <gtest/gtest.h>

#include "test_helper.hpp"

namespace kodocpp
{
static void test_decoder(uint32_t max_symbols, uint32_t max_symbol_size,
                         codec code, field field)
{
    decoder_factory decoder_factory(
        code,
        field,
        max_symbols,
        max_symbol_size);

    decoder decoder = decoder_factory.build();
    test_coder(decoder, max_symbols, max_symbol_size, code);

    // Decoder methods
    // Some codecs do not provide write_payload, i.e. recoding
    if (code == codec::seed || code == codec::sparse_seed ||
        code == codec::fulcrum || code == codec::reed_solomon)
    {
        EXPECT_FALSE(decoder.has_write_payload());
    }
    else
    {
        EXPECT_TRUE(decoder.has_write_payload());
    }

    EXPECT_GE(0U, decoder.symbols_uncoded());
    EXPECT_GE(0U, decoder.symbols_partially_decoded());

    if (code == codec::on_the_fly ||
        code == codec::sliding_window)
    {
        EXPECT_TRUE(decoder.has_partial_decoding_interface());
        EXPECT_FALSE(decoder.is_partially_complete());
        for (uint32_t i = 0; i < decoder.symbols(); ++i)
        {
            EXPECT_FALSE(decoder.is_symbol_pivot(i));
        }
    }
    else if (code == codec::full_vector ||
             code == codec::perpetual)
    {
        EXPECT_FALSE(decoder.has_partial_decoding_interface());
    }
}
}

TEST(test_decoder, invoke_api)
{
    using namespace kodocpp;

    uint32_t max_symbols = rand_symbols();
    uint32_t max_symbol_size = rand_symbol_size();

    test_combinations(test_decoder, max_symbols, max_symbol_size);
}

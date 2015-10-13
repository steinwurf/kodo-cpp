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
namespace
{
    void test_decoder(uint32_t max_symbols, uint32_t max_symbol_size,
        kodo_code_type code_type, kodo_finite_field finite_field)
    {
        decoder_factory decoder_factory(
            code_type,
            finite_field,
            max_symbols,
            max_symbol_size);

        decoder decoder = decoder_factory.build();
        test_coder(decoder, max_symbols, max_symbol_size, code_type);

        // Decoder methods
        EXPECT_GE(0U, decoder.symbols_uncoded());
        EXPECT_GE(0U, decoder.symbols_seen());

        if (code_type == kodo_on_the_fly ||
            code_type == kodo_sliding_window)
        {
            EXPECT_TRUE(decoder.has_partial_decoding_tracker());
            EXPECT_FALSE(decoder.is_partial_complete());
            for (uint32_t i = 0; i < decoder.symbols(); ++i)
            {
                EXPECT_FALSE(decoder.is_symbol_pivot(i));
            }
        }
        else if (code_type == kodo_full_vector ||
                 code_type == kodo_perpetual)
        {
            EXPECT_FALSE(decoder.has_partial_decoding_tracker());
        }
    }
}
}

TEST(test_decoder, invoke_api)
{
    using namespace kodocpp;

    uint32_t max_symbols = rand_symbols();
    uint32_t max_symbol_size = rand_symbol_size();

    test_combinations(test_decoder, max_symbols, max_symbol_size);

    test_combinations(test_decoder, max_symbols, max_symbol_size);
}

// Copyright Steinwurf ApS 2014.
// Distributed under the "STEINWURF RESEARCH LICENSE 1.0".
// See accompanying file LICENSE.rst or
// http://www.steinwurf.com/licensing

#include <kodocpp/encoder_factory.hpp>

#include <cstdint>

#include <gtest/gtest.h>

#include "test_helper.hpp"

TEST(test_encoder_factory, invoke_api)
{
    using namespace kodocpp;

    // Make sure that we can lower these values in the test
    uint32_t max_symbols = rand_symbols() + 1;
    uint32_t max_symbol_size = rand_symbol_size() + 4;

    test_combinations(test_coder_factory<encoder_factory>, max_symbols,
                      max_symbol_size);
}

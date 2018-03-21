// Copyright Steinwurf ApS 2016.
// Distributed under the "STEINWURF EVALUATION LICENSE 1.0".
// See accompanying file LICENSE.rst or
// http://www.steinwurf.com/licensing

#include <kodocpp/kodocpp.hpp>

#include <gtest/gtest.h>

#include "test_helper.hpp"

TEST(test_sparse_seed_codes, basic_api)
{
    using namespace kodocpp;

    if (has_codec(codec::sparse_seed) == false)
        return;

    // Make sure that the decoding can complete with a lower density
    uint32_t max_symbols = rand_symbols() + 10;
    uint32_t max_symbol_size = rand_symbol_size();

    test_basic_api(codec::sparse_seed, max_symbols, max_symbol_size);
}

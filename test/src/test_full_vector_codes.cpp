// Copyright Steinwurf ApS 2015.
// Distributed under the "STEINWURF RESEARCH LICENSE 1.0".
// See accompanying file LICENSE.rst or
// http://www.steinwurf.com/licensing

#include <kodocpp/kodocpp.hpp>

#include <gtest/gtest.h>

#include "test_helper.hpp"


TEST(test_full_vector_codes, basic_api)
{
    using namespace kodocpp;

    uint32_t max_symbols = rand_symbols();
    uint32_t max_symbol_size = rand_symbol_size();

    test_basic_api(kodo_full_vector, max_symbols, max_symbol_size);
}

TEST(test_full_vector_codes, sparse_api)
{
    using namespace kodocpp;

    // Make sure that the decoding can complete with a lower density
    uint32_t max_symbols = rand_symbols() + 10;
    uint32_t max_symbol_size = rand_symbol_size();

    test_basic_api(kodo_sparse_full_vector, kodo_full_vector, max_symbols,
                   max_symbol_size);
}

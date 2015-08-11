// Copyright Steinwurf ApS 2015.
// Distributed under the "STEINWURF RESEARCH LICENSE 1.0".
// See accompanying file LICENSE.rst or
// http://www.steinwurf.com/licensing

#pragma once

#include <kodocpp/kodocpp.hpp>

#include <gtest/gtest.h>

#include <functional>


namespace kodocpp
{

    using test_function_type = std::function<
        void(uint32_t, uint32_t, kodo_code_type, kodo_finite_field, bool)>;

    uint32_t rand_nonzero(uint32_t max_value);

    uint32_t rand_symbols(uint32_t max_symbols = 64);

    uint32_t rand_symbol_size(uint32_t max_symbol_size = 1600);

    void test_combinations(test_function_type test_function,
        uint32_t max_symbols, uint32_t max_symbol_size, bool trace_enabled);

    void test_basic_api(uint32_t max_symbols, uint32_t max_symbol_size,
        kodo_code_type code_type, kodo_finite_field finite_field);

    void test_coder(coder& coder, uint32_t symbols, uint32_t symbol_size,
        kodo_code_type code_type, bool trace_enabled);
}

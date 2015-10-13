// Copyright Steinwurf ApS 2015.
// Distributed under the "STEINWURF RESEARCH LICENSE 1.0".
// See accompanying file LICENSE.rst or
// http://www.steinwurf.com/licensing

#pragma once

#include <kodocpp/kodocpp.hpp>

#include <gtest/gtest.h>

#include <functional>
#include <cstdint>
#include <vector>

namespace kodocpp
{
    using test_function_type = std::function<
        void(uint32_t, uint32_t, kodo_code_type, kodo_finite_field)>;

    uint32_t rand_nonzero(uint32_t max_value);

    uint32_t rand_symbols(uint32_t max_symbols = 64);

    uint32_t rand_symbol_size(uint32_t max_symbol_size = 1600);

    void test_combinations(test_function_type test_function,
        uint32_t max_symbols, uint32_t max_symbol_size);

    void test_basic_api(uint32_t max_symbols, uint32_t max_symbol_size,
        kodo_code_type code_type, kodo_finite_field finite_field);

    void test_coder(coder& coder, uint32_t symbols, uint32_t symbol_size,
        kodo_code_type code_type);

    template<class Factory>
    void test_coder_factory(uint32_t max_symbols, uint32_t max_symbol_size,
        kodo_code_type code_type, kodo_finite_field field)
    {
        Factory factory(code_type, field, max_symbols, max_symbol_size);

        // Test the max_* properties
        EXPECT_EQ(max_symbols, factory.max_symbols());
        EXPECT_EQ(max_symbol_size, factory.max_symbol_size());
        EXPECT_EQ(max_symbol_size * max_symbols, factory.max_block_size());
        EXPECT_GT(factory.max_payload_size(), max_symbol_size);

        // Build a coder with the default settings
        auto coder = factory.build();

        EXPECT_EQ(max_symbols, coder.symbols());
        EXPECT_EQ(max_symbol_size, coder.symbol_size());

        // Lower the number of symbols and the symbol_size
        uint32_t new_symbols = max_symbols / 2;
        factory.set_symbols(new_symbols);

        uint32_t new_symbol_size = max_symbol_size - 4;
        factory.set_symbol_size(new_symbol_size);

        // Test that the max_* properties are not changed
        EXPECT_EQ(max_symbols, factory.max_symbols());
        EXPECT_EQ(max_symbol_size, factory.max_symbol_size());
        EXPECT_EQ(max_symbol_size * max_symbols, factory.max_block_size());
        EXPECT_GT(factory.max_payload_size(), max_symbol_size);

        // Build a coder with the changed settings
        auto coder_two = factory.build();

        EXPECT_EQ(new_symbols, coder_two.symbols());
        EXPECT_EQ(new_symbol_size, coder_two.symbol_size());

        // Use the default constructor and build the coder later
        typename Factory::coder_type coder_default;
        coder_default = factory.build();

        EXPECT_EQ(new_symbols, coder_default.symbols());
        EXPECT_EQ(new_symbol_size, coder_default.symbol_size());

        // Test copying factory
        auto factory_copy = factory;
        EXPECT_EQ(max_symbols, factory_copy.max_symbols());
        EXPECT_EQ(max_symbol_size, factory_copy.max_symbol_size());

        // Test copying coder
        auto coder_copy = coder;
        EXPECT_EQ(coder.symbols(), coder_copy.symbols());
        EXPECT_EQ(coder.symbol_size(), coder_copy.symbol_size());

        // Test store in vector
        std::vector<typename Factory::coder_type> coder_vector =
        {
            factory.build(),
            factory.build(),
            factory.build()
        };

        coder_vector.push_back(factory.build());

        for (auto& c : coder_vector)
        {
            EXPECT_EQ(new_symbols, c.symbols());
            EXPECT_EQ(new_symbol_size, c.symbol_size());
        }
    }
}

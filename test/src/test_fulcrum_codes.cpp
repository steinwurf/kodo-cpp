// Copyright Steinwurf ApS 2015.
// Distributed under the "STEINWURF EVALUATION LICENSE 1.0".
// See accompanying file LICENSE.rst or
// http://www.steinwurf.com/licensing

#include <kodocpp/kodocpp.hpp>

#include <gtest/gtest.h>

#include "test_helper.hpp"

TEST(test_fulcrum_codes, basic_api)
{
    using namespace kodocpp;

    if (has_codec(codec::fulcrum) == false)
        return;

    uint32_t max_symbols = rand_symbols();
    uint32_t max_symbol_size = rand_symbol_size();

    test_basic_api(codec::fulcrum, max_symbols, max_symbol_size);
}

template<class Factory>
static void test_fulcrum_api(Factory factory)
{
    using namespace kodocpp;

    uint32_t max_expansion = factory.max_expansion();
    EXPECT_EQ(10U, max_expansion);

    uint32_t max_symbols = factory.max_symbols();

    EXPECT_EQ(max_expansion + max_symbols, factory.max_inner_symbols());

    factory.set_expansion(max_expansion);

    auto coder = factory.build();
    EXPECT_EQ(max_expansion, coder.expansion());
    EXPECT_EQ(max_symbols + max_expansion, coder.inner_symbols());

    uint32_t other_expansion = max_expansion / 2;
    factory.set_expansion(other_expansion);

    auto other_coder = factory.build();
    EXPECT_EQ(other_expansion, other_coder.expansion());
    EXPECT_EQ(other_expansion + max_symbols, other_coder.inner_symbols());
}

TEST(test_fulcrum_codes, fulcrum_encoder_api)
{
    using namespace kodocpp;

    if (has_codec(codec::fulcrum) == false)
        return;

    uint32_t max_symbols = rand_symbols();
    uint32_t max_symbol_size = rand_symbol_size();

    encoder_factory factory(
        codec::fulcrum, field::binary8, max_symbols, max_symbol_size);
    test_fulcrum_api(factory);

    auto coder = factory.build();
    EXPECT_EQ(coder.symbols() + coder.expansion(), coder.nested_symbols());
    EXPECT_EQ(coder.symbol_size(), coder.nested_symbol_size());
}

TEST(test_fulcrum_codes, fulcrum_decoder_api)
{
    using namespace kodocpp;

    if (has_codec(codec::fulcrum) == false)
        return;

    uint32_t max_symbols = rand_symbols();
    uint32_t max_symbol_size = rand_symbol_size();

    decoder_factory factory(
        codec::fulcrum, field::binary8, max_symbols, max_symbol_size);
    test_fulcrum_api(factory);
}

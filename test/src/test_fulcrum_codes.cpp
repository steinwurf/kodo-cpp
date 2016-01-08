// Copyright Steinwurf ApS 2015.
// Distributed under the "STEINWURF RESEARCH LICENSE 1.0".
// See accompanying file LICENSE.rst or
// http://www.steinwurf.com/licensing

#include <kodocpp/kodocpp.hpp>

#include <gtest/gtest.h>

#include "test_helper.hpp"

TEST(test_fulcrum_codes, basic_api)
{
    using namespace kodocpp;

    uint32_t max_symbols = rand_symbols();
    uint32_t max_symbol_size = rand_symbol_size();

    test_basic_api(kodoc_fulcrum, max_symbols, max_symbol_size);
}

template<class Factory>
static void test_fulcrum_api()
{
    using namespace kodocpp;

    uint32_t max_symbols = rand_symbols();
    uint32_t max_symbol_size = rand_symbol_size();

    Factory factory(kodoc_fulcrum, kodoc_binary8, max_symbols, max_symbol_size);

    uint32_t max_expansion = factory.max_expansion();
    EXPECT_EQ(10U, max_expansion);
    factory.set_expansion(max_expansion);

    auto coder = factory.build();
    EXPECT_EQ(max_expansion, coder.expansion());

    uint32_t other_expansion = max_expansion / 2;
    factory.set_expansion(other_expansion);

    auto other_coder = factory.build();
    EXPECT_EQ(other_expansion, other_coder.expansion());
}

TEST(test_fulcrum_codes, fulcrum_encoder_api)
{
    using namespace kodocpp;
    test_fulcrum_api<encoder_factory>();
}

TEST(test_fulcrum_codes, fulcrum_decoder_api)
{
    using namespace kodocpp;
    test_fulcrum_api<decoder_factory>();
}

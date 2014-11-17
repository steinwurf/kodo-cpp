// Copyright Steinwurf ApS 2014.
// Distributed under the "STEINWURF RESEARCH LICENSE 1.0".
// See accompanying file LICENSE.rst or
// http://www.steinwurf.com/licensing

#include <cstdint>

#include <gtest/gtest.h>

#include <kodocpp/kodocpp.hpp>

void test_has_systematic_encoder(kodocpp::code_type code_type,
                                  kodocpp::finite_field finite_field)
{
    kodocpp::encoder_factory encoder_factory(
        code_type,
        finite_field,
        32,
        160,
        false);

    auto encoder = encoder_factory.build();

    EXPECT_TRUE(encoder.has_systematic_encoder());
}

TEST(TextHasSystematicEncoder, invoke_api)
{
    // Encoder test for full_rlnc
    test_has_systematic_encoder(kodocpp::code_type::full_rlnc,
                                 kodocpp::finite_field::binary);

    test_has_systematic_encoder(kodocpp::code_type::full_rlnc,
                                 kodocpp::finite_field::binary8);

    test_has_systematic_encoder(kodocpp::code_type::full_rlnc,
                                 kodocpp::finite_field::binary16);

    // Encoder test for on_the_fly
    test_has_systematic_encoder(kodocpp::code_type::on_the_fly,
                                 kodocpp::finite_field::binary);

    test_has_systematic_encoder(kodocpp::code_type::on_the_fly,
                                 kodocpp::finite_field::binary8);

    test_has_systematic_encoder(kodocpp::code_type::on_the_fly,
                                 kodocpp::finite_field::binary16);

    // Encoder test for on_the_fly
    test_has_systematic_encoder(kodocpp::code_type::sliding_window,
                                 kodocpp::finite_field::binary);

    test_has_systematic_encoder(kodocpp::code_type::sliding_window,
                                 kodocpp::finite_field::binary8);

    test_has_systematic_encoder(kodocpp::code_type::sliding_window,
                                 kodocpp::finite_field::binary16);
}

// Copyright Steinwurf ApS 2014.
// Distributed under the "STEINWURF RESEARCH LICENSE 1.0".
// See accompanying file LICENSE.rst or
// http://www.steinwurf.com/licensing

#include <cstdint>

#include <gtest/gtest.h>

#include <kodocpp/kodocpp.hpp>

void test_has_feedback_size_encoder(uint32_t symbols, uint32_t symbol_size,
                        kodocpp::code_type code_type,
                        kodocpp::finite_field finite_field,
                        bool trace_enabled)
{
    kodocpp::encoder_factory encoder_factory(
        code_type,
        finite_field,
        symbols,
        symbol_size,
        trace_enabled);

    kodocpp::encoder encoder = encoder_factory.build();

    if (code_type == kodocpp::code_type::full_rlnc ||
        code_type == kodocpp::code_type::on_the_fly)
    {
        EXPECT_FALSE(encoder.has_feedback_size());
    }
    else if (code_type == kodocpp::code_type::sliding_window)
    {
        EXPECT_TRUE(encoder.has_feedback_size());
    }
}

void test_has_feedback_size_decoder(uint32_t symbols, uint32_t symbol_size,
                        kodocpp::code_type code_type,
                        kodocpp::finite_field finite_field,
                        bool trace_enabled)
{
    kodocpp::decoder_factory decoder_factory(
        code_type,
        finite_field,
        symbols,
        symbol_size,
        trace_enabled);

    kodocpp::decoder decoder = decoder_factory.build();

    if (code_type == kodocpp::code_type::full_rlnc ||
        code_type == kodocpp::code_type::on_the_fly)
    {
        EXPECT_FALSE(decoder.has_feedback_size());
    }
    else if (code_type == kodocpp::code_type::sliding_window)
    {
        EXPECT_TRUE(decoder.has_feedback_size());
    }
}


TEST(TestHasFeedbackSize, invoke_api)
{
    //This is what is expectede for coder.symbol_size()
    uint32_t max_symbols = 32;
    uint32_t max_symbol_size = 160;

    // Testing ecoders
    // Full RLNC encoders
    test_has_feedback_size_encoder(max_symbols, max_symbol_size,
                                   kodocpp::code_type::full_rlnc,
                                   kodocpp::finite_field::binary,
                                   true);

    test_has_feedback_size_encoder(max_symbols, max_symbol_size,
                                   kodocpp::code_type::full_rlnc,
                                   kodocpp::finite_field::binary8,
                                   true);

    test_has_feedback_size_encoder(max_symbols, max_symbol_size,
                                   kodocpp::code_type::full_rlnc,
                                   kodocpp::finite_field::binary16,
                                   false);

    // On the fly encoders
    test_has_feedback_size_encoder(max_symbols, max_symbol_size,
                                   kodocpp::code_type::on_the_fly,
                                   kodocpp::finite_field::binary,
                                   false);

    test_has_feedback_size_encoder(max_symbols, max_symbol_size,
                                   kodocpp::code_type::on_the_fly,
                                   kodocpp::finite_field::binary8,
                                   false);

    test_has_feedback_size_encoder(max_symbols, max_symbol_size,
                                   kodocpp::code_type::on_the_fly,
                                   kodocpp::finite_field::binary8,
                                   false);

    // Sliding window encoders
    test_has_feedback_size_encoder(max_symbols, max_symbol_size,
                                   kodocpp::code_type::sliding_window,
                                   kodocpp::finite_field::binary,
                                   false);

    test_has_feedback_size_encoder(max_symbols, max_symbol_size,
                                   kodocpp::code_type::sliding_window,
                                   kodocpp::finite_field::binary8,
                                   false);

    test_has_feedback_size_encoder(max_symbols, max_symbol_size,
                                   kodocpp::code_type::sliding_window,
                                   kodocpp::finite_field::binary16,
                                   false);

    // Testing decoders
    // Full RLNC decoders
    test_has_feedback_size_decoder(max_symbols, max_symbol_size,
                                   kodocpp::code_type::full_rlnc,
                                   kodocpp::finite_field::binary,
                                   false);

    test_has_feedback_size_decoder(max_symbols, max_symbol_size,
                                   kodocpp::code_type::full_rlnc,
                                   kodocpp::finite_field::binary8,
                                   false);

    test_has_feedback_size_decoder(max_symbols, max_symbol_size,
                                   kodocpp::code_type::full_rlnc,
                                   kodocpp::finite_field::binary16,
                                   false);

    // On the fly decoders
    test_has_feedback_size_decoder(max_symbols, max_symbol_size,
                                   kodocpp::code_type::on_the_fly,
                                   kodocpp::finite_field::binary,
                                   false);

    test_has_feedback_size_decoder(max_symbols, max_symbol_size,
                                   kodocpp::code_type::on_the_fly,
                                   kodocpp::finite_field::binary8,
                                   false);

    test_has_feedback_size_decoder(max_symbols, max_symbol_size,
                                   kodocpp::code_type::on_the_fly,
                                   kodocpp::finite_field::binary16,
                                   false);
    // Sliding window decoders
    test_has_feedback_size_decoder(max_symbols, max_symbol_size,
                                   kodocpp::code_type::sliding_window,
                                   kodocpp::finite_field::binary,
                                   false);

    test_has_feedback_size_decoder(max_symbols, max_symbol_size,
                                   kodocpp::code_type::sliding_window,
                                   kodocpp::finite_field::binary8,
                                   false);

    test_has_feedback_size_decoder(max_symbols, max_symbol_size,
                                   kodocpp::code_type::sliding_window,
                                   kodocpp::finite_field::binary16,
                                   false);
}
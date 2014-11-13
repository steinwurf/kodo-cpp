// Copyright Steinwurf ApS 2014.
// Distributed under the "STEINWURF RESEARCH LICENSE 1.0".
// See accompanying file LICENSE.rst or
// http://www.steinwurf.com/licensing

#include <cstdint>

#include <gtest/gtest.h>

#include <kodocpp/kodocpp.hpp>

void test_max_symbol_size_encoder(uint32_t max_symbols, uint32_t max_symbol_size,
                        kodocpp::code_type code_type,
                        kodocpp::finite_field finite_field,
                        bool trace_enabled)
{
    kodocpp::encoder_factory encoder_factory(
        code_type,
        finite_field,
        max_symbols,
        max_symbol_size,
        trace_enabled);

    auto encoder = encoder_factory.build();

    uint32_t new_symbol_size = 100;
    encoder_factory.set_symbol_size(new_symbol_size);

    EXPECT_EQ(max_symbol_size, encoder_factory.max_symbol_size());
}

void test_max_symbol_size_decoder(uint32_t max_symbols, uint32_t max_symbol_size,
                        kodocpp::code_type code_type,
                        kodocpp::finite_field finite_field,
                        bool trace_enabled)
{
    kodocpp::decoder_factory decoder_factory(
        code_type,
        finite_field,
        max_symbols,
        max_symbol_size,
        trace_enabled);

    auto decoder = decoder_factory.build();

    uint32_t new_symbol_size = 100;
    decoder_factory.set_symbol_size(new_symbol_size);

    EXPECT_EQ(max_symbol_size, decoder_factory.max_symbol_size());

}


TEST(TestMaxSymbolSize, invoke_api)
{
    //This is what is expectede for coder.symbol_size()
    uint32_t max_symbols = 32;
    uint32_t max_symbol_size = 160;

    // Testing ecoders
    // Full RLNC encoders
    test_max_symbol_size_encoder(max_symbols, max_symbol_size,
                                   kodocpp::code_type::full_rlnc,
                                   kodocpp::finite_field::binary,
                                   true);

    test_max_symbol_size_encoder(max_symbols, max_symbol_size,
                                   kodocpp::code_type::full_rlnc,
                                   kodocpp::finite_field::binary8,
                                   true);

    test_max_symbol_size_encoder(max_symbols, max_symbol_size,
                                   kodocpp::code_type::full_rlnc,
                                   kodocpp::finite_field::binary16,
                                   false);

    // On the fly encoder
    test_max_symbol_size_encoder(max_symbols, max_symbol_size,
                                   kodocpp::code_type::on_the_fly,
                                   kodocpp::finite_field::binary,
                                   false);

    test_max_symbol_size_encoder(max_symbols, max_symbol_size,
                                   kodocpp::code_type::on_the_fly,
                                   kodocpp::finite_field::binary8,
                                   false);

    test_max_symbol_size_encoder(max_symbols, max_symbol_size,
                                   kodocpp::code_type::on_the_fly,
                                   kodocpp::finite_field::binary8,
                                   false);

    // Sliding window encoder
    test_max_symbol_size_encoder(max_symbols, max_symbol_size,
                                   kodocpp::code_type::sliding_window,
                                   kodocpp::finite_field::binary,
                                   false);

    test_max_symbol_size_encoder(max_symbols, max_symbol_size,
                                   kodocpp::code_type::sliding_window,
                                   kodocpp::finite_field::binary8,
                                   false);

    test_max_symbol_size_encoder(max_symbols, max_symbol_size,
                                   kodocpp::code_type::sliding_window,
                                   kodocpp::finite_field::binary16,
                                   false);

    // Testing decoders
    // Full RLNC decoders
    test_max_symbol_size_decoder(max_symbols, max_symbol_size,
                                   kodocpp::code_type::full_rlnc,
                                   kodocpp::finite_field::binary,
                                   false);

    test_max_symbol_size_decoder(max_symbols, max_symbol_size,
                                   kodocpp::code_type::full_rlnc,
                                   kodocpp::finite_field::binary8,
                                   false);

    test_max_symbol_size_decoder(max_symbols, max_symbol_size,
                                   kodocpp::code_type::full_rlnc,
                                   kodocpp::finite_field::binary16,
                                   false);

    // On the fly decoders
    test_max_symbol_size_decoder(max_symbols, max_symbol_size,
                                   kodocpp::code_type::on_the_fly,
                                   kodocpp::finite_field::binary,
                                   false);

    test_max_symbol_size_decoder(max_symbols, max_symbol_size,
                                   kodocpp::code_type::on_the_fly,
                                   kodocpp::finite_field::binary8,
                                   false);

    test_max_symbol_size_decoder(max_symbols, max_symbol_size,
                                   kodocpp::code_type::on_the_fly,
                                   kodocpp::finite_field::binary16,
                                   false);
    // Sliding window decoders
    test_max_symbol_size_decoder(max_symbols, max_symbol_size,
                                   kodocpp::code_type::sliding_window,
                                   kodocpp::finite_field::binary,
                                   false);

    test_max_symbol_size_decoder(max_symbols, max_symbol_size,
                                   kodocpp::code_type::sliding_window,
                                   kodocpp::finite_field::binary8,
                                   false);

    test_max_symbol_size_decoder(max_symbols, max_symbol_size,
                                   kodocpp::code_type::sliding_window,
                                   kodocpp::finite_field::binary16,
                                   false);
}

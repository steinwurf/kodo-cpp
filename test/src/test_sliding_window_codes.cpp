// Copyright Steinwurf ApS 2011-2013.
// Distributed under the "STEINWURF RESEARCH LICENSE 1.0".
// See accompanying file LICENSE.rst or
// http://www.steinwurf.com/licensing

#include <kodocpp/kodocpp.hpp>

#include <cstdlib>
#include <vector>
#include <algorithm>

#include <gtest/gtest.h>

#include "test_helper.hpp"

static uint32_t encoder_trace_called = 0;
static uint32_t decoder_trace_called = 0;

static void encoder_trace_callback(const char* zone, const char* data)
{
    EXPECT_TRUE(zone != 0);
    EXPECT_TRUE(data != 0);

    encoder_trace_called++;
}

static void decoder_trace_callback(const char* zone, const char* data)
{
    EXPECT_TRUE(zone != 0);
    EXPECT_TRUE(data != 0);

    decoder_trace_called++;
}

void test_sliding_window(uint32_t max_symbols, uint32_t max_symbol_size,
                         kodo_code_type code_type,
                         kodo_finite_field finite_field)
{
    bool trace_flag = true;

    //Initilization of encoder and decoder
    kodocpp::encoder_factory encoder_factory(
        code_type,
        finite_field,
        max_symbols,
        max_symbol_size,
        trace_flag);

    kodocpp::encoder encoder = encoder_factory.build();

    kodocpp::decoder_factory decoder_factory(
        code_type,
        finite_field,
        max_symbols,
        max_symbol_size,
        trace_flag);

    kodocpp::decoder decoder = decoder_factory.build();

    EXPECT_TRUE(max_symbols == encoder_factory.max_symbols());
    EXPECT_TRUE(max_symbol_size == encoder_factory.max_symbol_size());
    EXPECT_TRUE(max_symbols == encoder.symbols());
    EXPECT_TRUE(max_symbol_size == encoder.symbol_size());

    EXPECT_TRUE(max_symbols == decoder_factory.max_symbols());
    EXPECT_TRUE(max_symbol_size == decoder_factory.max_symbol_size());
    EXPECT_TRUE(max_symbols == decoder.symbols());
    EXPECT_TRUE(max_symbol_size == decoder.symbol_size());

    EXPECT_TRUE(encoder.block_size() == max_symbols * max_symbol_size);
    EXPECT_TRUE(decoder.block_size() == max_symbols * max_symbol_size);

    EXPECT_TRUE(encoder_factory.max_payload_size() >=
                encoder.payload_size());

    EXPECT_TRUE(decoder_factory.max_payload_size() >=
                decoder.payload_size());

    EXPECT_EQ(encoder_factory.max_payload_size(),
              decoder_factory.max_payload_size());

    uint32_t feedback_size = 0;

    EXPECT_EQ(encoder.feedback_size(),
              decoder.feedback_size());

    feedback_size = encoder.feedback_size();
    EXPECT_TRUE(feedback_size > 0);

    std::vector<uint8_t> feedback(feedback_size);

    // Allocate some storage for a "payload" the payload is what we would
    // eventually send over a network
    std::vector<uint8_t> payload(encoder.payload_size());

    // Allocate some data to encode. In this case we make a buffer
    // with the same size as the encoder's block size (the max.
    // amount a single encoder can encode)
    std::vector<uint8_t> data_in(encoder.block_size());

    // Just for fun - fill the data with random data
    std::generate(data_in.begin(), data_in.end(), rand);

    // Install a custom trace function for the encoder and decoder
    EXPECT_TRUE(encoder.has_set_trace_callback());
    encoder.set_trace_callback(encoder_trace_callback);

    EXPECT_TRUE(decoder.has_set_trace_callback());
    decoder.set_trace_callback(decoder_trace_callback);

    // Assign the data buffer to the encoder so that we may start
    // to produce encoded symbols from it
    encoder.set_symbols(data_in.data(), encoder.block_size());

    while (!decoder.is_complete())
    {
        // Encode the packet into the payload buffer
        uint32_t payload_used = encoder.write_payload(payload.data());
        EXPECT_TRUE(payload_used <= encoder.payload_size());

        // Pass that packet to the decoder
        decoder.read_payload(payload.data());
        EXPECT_TRUE(decoder.is_partial_complete());

        decoder.write_feedback(feedback.data());
        encoder.read_feedback(feedback.data());
    }
    EXPECT_TRUE(decoder.is_complete());

    // The decoder is complete, now copy the symbols from the decoder
    std::vector<uint8_t> data_out(decoder.block_size());
    decoder.copy_from_symbols(data_out.data(), decoder.block_size());

    // Check if we properly decoded the data
    EXPECT_TRUE(data_out == data_in);

    // Check that the trace functions were called at least once
    EXPECT_GT(encoder_trace_called, 0U);
    EXPECT_GT(decoder_trace_called, 0U);
}

TEST(TestSlidingWindowCodes, invoke_api)
{
    uint32_t max_symbols = rand_symbols();
    uint32_t max_symbol_size = rand_symbol_size();

    test_sliding_window(max_symbols, max_symbol_size,
                        kodo_sliding_window, kodo_binary);

    test_sliding_window(max_symbols, max_symbol_size,
                        kodo_sliding_window, kodo_binary4);

    test_sliding_window(max_symbols, max_symbol_size,
                        kodo_sliding_window, kodo_binary8);

    test_sliding_window(max_symbols, max_symbol_size,
                        kodo_sliding_window, kodo_binary16);
}

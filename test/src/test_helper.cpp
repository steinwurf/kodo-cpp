// Copyright Steinwurf ApS 2015.
// Distributed under the "STEINWURF RESEARCH LICENSE 1.0".
// See accompanying file LICENSE.rst or
// http://www.steinwurf.com/licensing

#include <kodocpp/kodocpp.hpp>

#include <cstdint>
#include <cstdlib>
#include <algorithm>
#include <vector>

#include <gtest/gtest.h>

#include "test_helper.hpp"

namespace kodocpp
{
    uint32_t rand_nonzero(uint32_t max_value)
    {
        assert(max_value > 0);
        return (rand() % max_value) + 1;
    }

    uint32_t rand_symbols(uint32_t max_symbols)
    {
        return rand_nonzero(max_symbols);
    }

    uint32_t rand_symbol_size(uint32_t max_symbol_size)
    {
        // Currently the biggest field we support is 2^32, so we always make
        // sure that the symbol size is a multiple of 4 bytes.
        uint32_t granularity = 4;
        uint32_t elements = max_symbol_size / granularity;

        return rand_nonzero(elements) * granularity;
    }

    void test_combinations(test_function_type coder_test,
                           uint32_t max_symbols, uint32_t max_symbol_size)
    {
        SCOPED_TRACE(testing::Message() << "symbols = " << max_symbols);
        SCOPED_TRACE(testing::Message() << "symbol_size = " << max_symbol_size);

        std::vector<kodoc_codec> codecs =
        {
            kodoc_full_vector,
            kodoc_on_the_fly,
            kodoc_sliding_window,
            kodoc_sparse_full_vector,
            kodoc_seed,
            kodoc_sparse_seed,
            kodoc_perpetual,
            kodoc_fulcrum,
            kodoc_reed_solomon
        };

        std::vector<std::string> codec_names =
        {
            "kodoc_full_vector",
            "kodoc_on_the_fly",
            "kodoc_sliding_window",
            "kodoc_sparse_full_vector",
            "kodoc_seed",
            "kodoc_sparse_seed",
            "kodoc_perpetual",
            "kodoc_fulcrum",
            "kodoc_reed_solomon"
        };

        for (uint32_t i = 0; i < codecs.size(); ++i)
        {
            SCOPED_TRACE(testing::Message() << "codec = " << codec_names[i]);

            kodoc_codec codec = codecs[i];

            if (has_codec(codec) == false)
                continue;

            if (codec != kodoc_reed_solomon)
            {
                SCOPED_TRACE(testing::Message() << "field = binary");
                coder_test(max_symbols, max_symbol_size, codec, kodoc_binary);
            }

            if (codec != kodoc_reed_solomon)
            {
                SCOPED_TRACE(testing::Message() << "field = binary4");
                coder_test(max_symbols, max_symbol_size, codec, kodoc_binary4);
            }

            {
                SCOPED_TRACE(testing::Message() << "field = binary8");
                coder_test(max_symbols, max_symbol_size, codec, kodoc_binary8);
            }
        }
    }

    void test_coder(coder& coder, uint32_t symbols, uint32_t symbol_size,
                    kodoc_codec codec)
    {
        EXPECT_EQ(symbols, coder.symbols());
        EXPECT_EQ(symbol_size, coder.symbol_size());
        EXPECT_EQ(symbols * symbol_size, coder.block_size());
        EXPECT_GT(coder.payload_size(), symbol_size);
        EXPECT_EQ(0U, coder.rank());

        if (codec == kodoc_sliding_window)
        {
            EXPECT_TRUE(coder.has_feedback_size());
            EXPECT_GT(coder.feedback_size(), 0U);
        }
        else
        {
            EXPECT_FALSE(coder.has_feedback_size());
        }

        EXPECT_TRUE(coder.has_trace_interface());
        coder.set_trace_stdout();
        coder.set_trace_off();
        coder.set_zone_prefix("prefix");
    }

    /// Create and configure encoder instance
    encoder create_encoder(uint32_t max_symbols, uint32_t max_symbol_size,
                           kodoc_codec codec,
                           kodoc_finite_field finite_field,
                           uint32_t& trace_counter)
    {
        // Initilization of encoder and decoder
        encoder_factory encoder_factory(
            codec, finite_field, max_symbols, max_symbol_size);

        encoder encoder = encoder_factory.build();

        EXPECT_EQ(max_symbols, encoder_factory.max_symbols());
        EXPECT_EQ(max_symbol_size, encoder_factory.max_symbol_size());
        EXPECT_EQ(max_symbols, encoder.symbols());
        EXPECT_EQ(max_symbol_size, encoder.symbol_size());

        EXPECT_EQ(max_symbols * max_symbol_size, encoder.block_size());

        EXPECT_GE(encoder_factory.max_payload_size(), encoder.payload_size());

        // Install a custom trace function for the encoder
        auto callback = [](uint32_t& count, const std::string& zone,
                           const std::string& data)
        {
            EXPECT_FALSE(zone.empty());
            EXPECT_FALSE(data.empty());
            count++;
        };

        using namespace std::placeholders;

        EXPECT_TRUE(encoder.has_trace_interface());
        encoder.set_trace_callback(
            std::bind<void>(callback, std::ref(trace_counter), _1, _2));

        if (codec == kodoc_sparse_full_vector ||
            codec == kodoc_sparse_seed)
        {
            // Set the coding vector density on the encoder
            encoder.set_density(0.2);
            EXPECT_EQ(0.2, encoder.density());
        }

        // Test perpetual specific functions
        if (codec == kodoc_perpetual)
        {
            EXPECT_FALSE(encoder.pseudo_systematic());
            bool pseudo_systematic = true;
            encoder.set_pseudo_systematic(pseudo_systematic);
            EXPECT_TRUE(encoder.pseudo_systematic());

            EXPECT_FALSE(encoder.pre_charging());
            bool pre_charging = true;
            encoder.set_pre_charging(pre_charging);
            EXPECT_TRUE(encoder.pre_charging());

            // width must be < symbols
            uint32_t width = max_symbols - 1;
            encoder.set_width(width);
            EXPECT_EQ(width, encoder.width());

            double width_ratio = 1.0;
            encoder.set_width_ratio(width_ratio);
            EXPECT_EQ(width_ratio, encoder.width_ratio());
        }

        return encoder;
    }

    /// Create and configure decoder instance
    decoder create_decoder(uint32_t max_symbols, uint32_t max_symbol_size,
                           kodoc_codec codec,
                           kodoc_finite_field finite_field,
                           uint32_t& trace_counter)
    {
        decoder_factory decoder_factory(
            codec, finite_field, max_symbols, max_symbol_size);

        decoder decoder = decoder_factory.build();

        EXPECT_EQ(max_symbols, decoder_factory.max_symbols());
        EXPECT_EQ(max_symbol_size, decoder_factory.max_symbol_size());
        EXPECT_EQ(max_symbols, decoder.symbols());
        EXPECT_EQ(max_symbol_size, decoder.symbol_size());

        EXPECT_GE(decoder_factory.max_payload_size(), decoder.payload_size());

        // Install a custom trace function for the decoder
        auto callback = [](uint32_t& count, const std::string& zone,
                           const std::string& data)
        {
            EXPECT_FALSE(zone.empty());
            EXPECT_FALSE(data.empty());
            count++;
        };

        using namespace std::placeholders;

        EXPECT_TRUE(decoder.has_trace_interface());
        decoder.set_trace_callback(
            std::bind<void>(callback, std::ref(trace_counter), _1, _2));

        return decoder;
    }

    void run_test_basic_api(
        kodoc_codec encoder_type, kodoc_codec decoder_type,
        kodoc_finite_field finite_field,
        uint32_t max_symbols, uint32_t max_symbol_size)
    {
        uint32_t encoder_trace_count = 0;
        uint32_t decoder_trace_count = 0;

        // Use the default constructor, so the compiler will be forced to copy
        // the coder instances created in the other functions.
        encoder encoder;
        decoder decoder;

        // We create and configure the encoder and decoder in different
        // functions to verify correct operation with copied instances.
        // The corresponding factories are also destroyed before the coder
        // instances are used.
        encoder = create_encoder(max_symbols, max_symbol_size,
                                 encoder_type, finite_field,
                                 encoder_trace_count);

        decoder = create_decoder(max_symbols, max_symbol_size,
                                 decoder_type, finite_field,
                                 decoder_trace_count);

        EXPECT_EQ(encoder.payload_size(), decoder.payload_size());

        // Allocate some storage for a "payload" the payload is what we would
        // eventually send over a network
        std::vector<uint8_t> payload(encoder.payload_size());

        // Allocate some data to encode. In this case we make a buffer
        // with the same size as the encoder's block size (the max.
        // amount a single encoder can encode)
        std::vector<uint8_t> data_in(encoder.block_size());
        std::vector<uint8_t> data_out(decoder.block_size());

        // Set the storage for the decoder
        decoder.set_mutable_symbols(data_out.data(), decoder.block_size());

        // Just for fun - fill the data with random data
        std::generate(data_in.begin(), data_in.end(), rand);

        // Assign the data buffer to the encoder so that we may start
        // to produce encoded symbols from it
        if (encoder_type != kodoc_on_the_fly)
        {
            encoder.set_const_symbols(data_in.data(), encoder.block_size());
        }

        // Test feedback if we are testing sliding window
        std::vector<uint8_t> feedback;
        if (encoder_type == kodoc_sliding_window)
        {
            uint32_t feedback_size = 0;

            EXPECT_EQ(encoder.feedback_size(), decoder.feedback_size());

            feedback_size = encoder.feedback_size();
            EXPECT_GT(feedback_size, 0U);

            feedback.resize(feedback_size);
        }

        while (!decoder.is_complete())
        {
            EXPECT_GE(encoder.rank(), decoder.rank());

            if (encoder_type == kodoc_on_the_fly)
            {
                // Randomly choose to add a new symbol (with 50% probability)
                // if the encoder rank is less than the maximum number of
                // symbols
                if ((rand() % 2) && encoder.rank() < encoder.symbols())
                {
                    // The rank of an encoder  indicates how many symbols have
                    // been added, i.e. how many symbols are available for
                    // encoding
                    uint32_t rank = encoder.rank();
                    uint32_t symbol_size = encoder.symbol_size();

                    // Calculate the offset to the next symbol to insert
                    uint8_t* symbol = data_in.data() + (rank * symbol_size);

                    encoder.set_const_symbol(rank, symbol, symbol_size);
                }
            }

            // Encode the packet into the payload buffer
            uint32_t payload_used = encoder.write_payload(payload.data());
            EXPECT_LE(payload_used, encoder.payload_size());

            // Pass that packet to the decoder
            decoder.read_payload(payload.data());

            if (encoder_type == kodoc_sliding_window)
            {
                decoder.write_feedback(feedback.data());
                encoder.read_feedback(feedback.data());
            }

            // Check the decoder rank and symbol counters
            EXPECT_GE(encoder.rank(), decoder.rank());
            EXPECT_GE(decoder.rank(), decoder.symbols_uncoded());
            EXPECT_GE(decoder.rank(), decoder.symbols_partially_decoded());
            EXPECT_EQ(decoder.symbols() - decoder.rank(),
                      decoder.symbols_missing());

            // Check if the decoder is partially complete
            // The decoder has to support partial decoding tracker for
            // on-the-fly decoding
            if (decoder.has_partial_decoding_interface() &&
                decoder.is_partially_complete())
            {
                for (uint32_t i = 0; i < decoder.symbols(); ++i)
                {
                    // Go through all symbols that are already decoded
                    if (decoder.is_symbol_uncoded(i))
                    {
                        // All uncoded symbols must have a pivot
                        EXPECT_TRUE(decoder.is_symbol_pivot(i));
                        // The uncoded symbols cannot be missing
                        EXPECT_FALSE(decoder.is_symbol_missing(i));
                        // The uncoded symbols cannot be partially decoded
                        EXPECT_FALSE(decoder.is_symbol_partially_decoded(i));

                        uint32_t offset = i * max_symbol_size;
                        uint8_t* original = data_in.data() + offset;

                        // Get the decoded symbol and compare it to the
                        // original symbol
                        uint8_t* decoded_symbol = data_out.data() + offset;
                        EXPECT_EQ(memcmp(
                            original, decoded_symbol, max_symbol_size), 0);
                    }
                }
            }
        }
        EXPECT_TRUE(decoder.is_complete());

        // Check if we properly decoded the data
        EXPECT_EQ(data_in, data_out);

        EXPECT_GT(encoder_trace_count, 0U);
        EXPECT_GT(decoder_trace_count, 0U);
    }

    void test_basic_api(kodoc_codec encoder_type,
                        kodoc_codec decoder_type,
                        uint32_t symbols, uint32_t symbol_size)
    {
        SCOPED_TRACE(testing::Message() << "symbols = " << symbols);
        SCOPED_TRACE(testing::Message() << "symbol_size = " << symbol_size);

        if (encoder_type != kodoc_reed_solomon)
        {
            SCOPED_TRACE(testing::Message() << "field = binary");
            run_test_basic_api(encoder_type, decoder_type, kodoc_binary,
                               symbols, symbol_size);
        }

        if (encoder_type != kodoc_reed_solomon)
        {
            SCOPED_TRACE(testing::Message() << "field = binary4");
            run_test_basic_api(encoder_type, decoder_type, kodoc_binary4,
                               symbols, symbol_size);
        }

        {
            SCOPED_TRACE(testing::Message() << "field = binary8");
            run_test_basic_api(encoder_type, decoder_type, kodoc_binary8,
                               symbols, symbol_size);
        }
    }

    void test_basic_api(kodoc_codec coder_type, uint32_t symbols,
                        uint32_t symbol_size)
    {
        test_basic_api(coder_type, coder_type, symbols, symbol_size);
    }
}

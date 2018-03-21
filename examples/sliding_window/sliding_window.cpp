// Copyright Steinwurf ApS 2014.
// Distributed under the "STEINWURF EVALUATION LICENSE 1.0".
// See accompanying file LICENSE.rst or
// http://www.steinwurf.com/licensing

/// @example sliding_window.cpp
///
/// This example shows how to use the sliding window encoder and decoder
/// stacks. The sliding window is special in that it does not require
/// that all symbols are available at the encoder before encoding can
/// start. In addition, it uses feedback between the decoder and encoder
/// such that symbols that have already been received at the decoder
/// are not included in the encoding again (saving computations).

#include <cstdint>
#include <cstdlib>
#include <ctime>
#include <iostream>
#include <vector>
#include <algorithm>
#include <set>

#include <kodocpp/kodocpp.hpp>

int main(void)
{
    // Seed random number generator to produce different results every time
    srand(static_cast<uint32_t>(time(0)));

    // Set the number of symbols (i.e. the generation size in RLNC
    // terminology) and the size of a symbol in bytes
    uint32_t max_symbols = 6;
    uint32_t max_symbol_size = 100;

    // Initilization of encoder and decoder
    kodocpp::encoder_factory encoder_factory(
        kodocpp::codec::sliding_window,
        kodocpp::field::binary8,
        max_symbols,
        max_symbol_size);

    kodocpp::encoder encoder = encoder_factory.build();

    kodocpp::decoder_factory decoder_factory(
        kodocpp::codec::sliding_window,
        kodocpp::field::binary8,
        max_symbols,
        max_symbol_size);

    kodocpp::decoder decoder = decoder_factory.build();

    // Allocate some storage for a "payload" the payload is what we would
    // eventually send over a network
    std::vector<uint8_t> payload(encoder.payload_size());

    // Allocate some data to encode. In this case we make a buffer
    // with the same size as the encoder's block size (the max.
    // amount a single encoder can encode)
    std::vector<uint8_t> data_in(encoder.block_size());

    // Just for fun - fill the data with random data
    std::generate(data_in.begin(), data_in.end(), rand);

    // Set the storage for the decoder
    std::vector<uint8_t> data_out(decoder.block_size());
    decoder.set_mutable_symbols(data_out.data(), decoder.block_size());

    std::vector<uint8_t> feedback(encoder.feedback_size());

    // Install a custom trace callback function
    auto callback = [](const std::string& zone, const std::string& data)
    {
        std::set<std::string> filters =
            {
                "decoder_state", "symbol_coefficients_before_read_symbol",
                "symbol_index_before_read_uncoded_symbol"
            };

        if (filters.count(zone))
        {
            std::cout << zone << ":" << std::endl;
            std::cout << data << std::endl;
        }
    };

    decoder.set_trace_callback(callback);

    while (!decoder.is_complete())
    {
        // Insert a new symbol until the encoder is full
        if ((rand() % 2) && encoder.rank() < encoder.symbols())
        {
            //The rank of an encoder indicates how many symbols have been
            // added, i.e how many symbols are available for encoding
            uint32_t rank = encoder.rank();

            //Calculate the offset to the next symbol to instert
            uint8_t* symbol = data_in.data() + (rank * encoder.symbol_size());

            encoder.set_const_symbol(rank, symbol, encoder.symbol_size());

            std::cout << "Symbol " << rank << " added to the encoder"
                      << std::endl;
        }

        // Only send packets if the encoder has more data than the decoder
        if (encoder.rank() == decoder.rank())
        {
            continue;
        }

        // Encode a packet into the payload buffer
        encoder.write_payload(payload.data());
        std::cout << "Encoded packet generated" << std::endl;

        // Simulate a lossy channel where we are losing 50% of the packets
        if (rand() % 2)
        {
            std::cout << "Packet dropped on channel" << std::endl << std::endl;
            continue;
        }

        std::cout << "Decoder received packet" << std::endl;

        // Packet got through - pass that packet to the decoder
        decoder.read_payload(payload.data());

        std::cout << "Encoder rank: " << encoder.rank()  << std::endl;
        std::cout << "Decoder rank: " << decoder.rank()  << std::endl;

        std::cout << "Decoder symbols uncoded: " << decoder.symbols_uncoded()
                  << std::endl;
        std::cout << "Decoder symbols seen: "
                  << decoder.symbols_partially_decoded() << std::endl;

        // Transmit the feedback
        decoder.write_feedback(feedback.data());

        // Note that the feedback packets can also be lost in a real network,
        // but here we deliver all of them for the sake of simplicity
        std::cout << "Received feedback from decoder" << std::endl << std::endl;
        encoder.read_feedback(feedback.data());
    }

    // Check if we properly decoded the data
    if (std::equal(data_out.begin(), data_out.end(), data_in.begin()))
    {
        std::cout << "Data decoded correctly" << std::endl;
    }
    else
    {
        std::cout << "Unexpected failure to decode, "
                  << "please file a bug report :)" << std::endl;
    }

    return 0;
}

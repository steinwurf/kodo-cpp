// Copyright Steinwurf ApS 2014.
// Distributed under the "STEINWURF RESEARCH LICENSE 1.0".
// See accompanying file LICENSE.rst or
// http://www.steinwurf.com/licensing

#include <cstdlib>
#include <ctime>
#include <iostream>
#include <vector>
#include <algorithm>
#include <set>

#include <kodocpp/kodocpp.hpp>

/// @example sliding_window.cpp
///
/// This example shows how to use the sliding window encoder and decoder
/// stacks. The sliding window is special in that it does not require
/// that all symbols are available at the encoder before encoding can
/// start. In addition, it uses feedback between the decoder and encoder
/// such that symbols that have already been received at the decoder
/// are not included in the encoding again (saving computations).

int main(void)
{
    // Seed random number generator to produce different results every time
    srand(static_cast<uint32_t>(time(0)));

    // Set the number of symbols (i.e. the generation size in RLNC
    // terminology) and the size of a symbol in bytes
    uint32_t max_symbols = 42;
    uint32_t max_symbol_size = 160;

    bool trace_enabled = false;

    // Initilization of encoder and decoder
    kodocpp::encoder_factory encoder_factory(
        kodocpp::code_type::sliding_window,
        kodocpp::finite_field::binary8,
        max_symbols,
        max_symbol_size,
        trace_enabled);

    kodocpp::encoder encoder = encoder_factory.build();

    trace_enabled = true;

    kodocpp::decoder_factory decoder_factory(
        kodocpp::code_type::sliding_window,
        kodocpp::finite_field::binary8,
        max_symbols,
        max_symbol_size,
        trace_enabled);

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

    std::vector<uint8_t> feedback(encoder.feedback_size());

    while (!decoder.is_complete())
    {
        // Randomly choose to insert a symbol or not
        if ((rand() % 2) && encoder.rank() < encoder.symbols())
        {
            //The rank of an encoder indicates how many symbols have been
            // added, i.e how many symbols are available for encoding
            uint32_t rank = encoder.rank();

            //Calculate the offset to the next symbol to instert
            uint8_t* symbol = data_in.data() + (rank * encoder.symbol_size());

            encoder.set_symbol(rank, symbol, encoder.symbol_size());

            std::cout << "Symbol " << rank << " added to the encoder"
                      << std::endl;
        }

        // Do not generate packets if the encoder is empty
        if (encoder.rank() == 0)
        {
            continue;
        }

        // Encode a packet into the payload buffer
        encoder.encode(payload.data());

        std::cout << "Packet encoded" << std::endl;

        // Send the data to the decoder, here we just for fun
        // simulate that we are losing 50% of the packets
        if (rand() % 2)
        {
            std::cout << "Packet dropped on channel" << std::endl;
            continue;
        }

        std::cout << "Decoder received packet" << std::endl;

        decoder.decode(payload.data());

        if (decoder.has_trace())
        {
            // Define trace filter function
            auto filter = [](const std::string& zone)
            {
                std::set<std::string> filters =
                    {"decoder_state", "input_symbol_coefficients"};
                return filters.count(zone) != 0;
            };

            std::cout << "Trace decoder:" << std::endl;
            decoder.trace(filter);
        }

        std::cout << "Encoder rank = " << encoder.rank()  << std::endl;
        std::cout << "Decoder rank = " << decoder.rank()  << std::endl;

        std::cout << "Decoder uncoded = " << decoder.symbols_uncoded()
                  << std::endl;
        std::cout << "Decoder seen = " << decoder.symbols_seen() << std::endl;

        decoder.write_feedback(feedback.data());

        if (rand() % 2)
        {
            std::cout << "Lost feedback from decoder" << std::endl;
        }
        else
        {
            std::cout << "Received feedback from decoder" << std::endl;
            encoder.read_feedback(feedback.data());
        }
    }

    std::vector<uint8_t> data_out(decoder.block_size());

    decoder.copy_symbols(data_out.data(), decoder.block_size());

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

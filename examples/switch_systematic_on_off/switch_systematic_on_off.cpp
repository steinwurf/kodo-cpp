// Copyright Steinwurf ApS 2014.
// Distributed under the "STEINWURF RESEARCH LICENSE 1.0".
// See accompanying file LICENSE.rst or
// http://www.steinwurf.com/licensing

#include <cstdlib>
#include <ctime>
#include <iostream>
#include <vector>
#include <algorithm>

#include <kodocpp/kodocpp.hpp>

/// @example switch_systematic_on_off.cpp
///
/// This example shows how to enable or disable systematic coding for
/// coding stacks that support it.
/// Systematic coding is used to reduce the amount of work done by an
/// encoder and a decoder. This is achieved by initially sending all
/// symbols which has not previously been sent uncoded. Kodo allows this
/// feature to be optionally turn of or off.

int main(void)
{
    // Seed random number generator to produce different results every time
    srand(static_cast<uint32_t>(time(0)));

    // Set the number of symbols (i.e. the generation size in RLNC
    // terminology) and the size of a symbol in bytes
    uint32_t max_symbols = 10;
    uint32_t max_symbol_size = 100;

    // Initilization of encoder and decoder
    kodocpp::encoder_factory encoder_factory(
        kodo_full_vector,
        kodo_binary8,
        max_symbols,
        max_symbol_size);

    kodocpp::encoder encoder = encoder_factory.build();

    kodocpp::decoder_factory decoder_factory(
        kodo_full_vector,
        kodo_binary8,
        max_symbols,
        max_symbol_size);

    kodocpp::decoder decoder = decoder_factory.build();

    // Set the storage for the decoder.
    std::vector<uint8_t> data_out(decoder.block_size());
    decoder.set_mutable_symbols(data_out.data(), decoder.block_size());

    // Allocate some storage for a "payload" the payload is what we would
    // eventually send over a network
    std::vector<uint8_t> payload(encoder.payload_size());

    // Allocate some data to encode. In this case we make a buffer
    // with the same size as the encoder's block size (the max.
    // amount a single encoder can encode)
    std::vector<uint8_t> data_in(encoder.block_size());

    // Just for fun - fill the data with random data
    std::generate(data_in.begin(), data_in.end(), rand);

    encoder.set_const_symbols(data_in.data(), encoder.block_size());

    std::cout << "Start encoding / decoding" << std::endl;
    while (!decoder.is_complete())
    {
        //If the chosen codec stack supports systematic coding
        if (encoder.has_set_systematic_off())
        {
            // with 50% probability toggle systematic
            if ((rand() % 2) == 0)
            {
                if (encoder.is_systematic_on())
                {
                    std::cout << "Turning systematic coding OFF" << std::endl;
                    encoder.set_systematic_off();
                }
                else
                {
                    std::cout << "Turning systematic coding ON" << std::endl;
                    encoder.set_systematic_on();
                }
            }
        }

        //Encode a packet into the payload buffer
        encoder.write_payload(payload.data());

        // Simulate a lossy channel where we are losing 50% of the packets
        if ((rand() % 2) == 0)
        {
            std::cout << "Packet dropped" << std::endl;
            continue;
        }

        //Pass the packet to the decoder
        decoder.read_payload(payload.data());

        std::cout << "Decoder rank: " << decoder.rank() << std::endl;

        // Symbols that were received in the systematic phase correspond
        // to the original source symbols and are therefore marked as
        // decoded
        std::cout << "Symbols decoded: " << decoder.symbols_uncoded()
                  << std::endl;
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

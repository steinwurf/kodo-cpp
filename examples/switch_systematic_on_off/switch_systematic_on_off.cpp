// Copyright Steinwurf ApS 2014.
// Distributed under the "STEINWURF RESEARCH LICENSE 1.0".
// See accompanying file LICENSE.rst or
// http://www.steinwurf.com/licensing

#include <cstdlib>
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
    uint32_t max_symbols = 16;
    uint32_t max_symbol_size = 160;

    bool trace_enabled = true;

    // Initilization of encoder and decoder
    kodocpp::encoder_factory encoder_factory(
        kodocpp::code_type::full_rlnc,
        kodocpp::finite_field::binary8,
        max_symbols,
        max_symbol_size,
        trace_enabled);

    kodocpp::encoder encoder = encoder_factory.build();

    kodocpp::decoder_factory decoder_factory(
        kodocpp::code_type::full_rlnc,
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

    encoder.set_symbols(data_in.data(), encoder.block_size());

    std::cout << "Start encoding / decoding" << std:endln;
    while (!decoder.is_complete())
    {
        //If the chosen codec stack supports systematic coding
        if (encoder.has_systematic_encoder())
        {
            // with 50% probability toggle systematic
            if ((rand() % 2) == 0)
            {
                if (encoder.is_systematic_on())
                {
                    std::cout << "Turning Systematic OFF" << std:endln;
                    encoder.set_systematic_off();
                }
                else
                {
                    std::cout << "Turning systematic ON" << std:endln;
                    encoder.set_systematic_on();
                }
            }
        }

        //Encode a packet into the payload buffer
        encoder.encode(payload.data());

        if ((rand() % 2) == 0)
        {
            std::cout << "Drop packet" << std:endln;
            continue;
        }

        //Pass the packet to the decoder
        decoder.decode(payload.data());

        std::cout << "Rank of decoder " << decoder.rank()  << std:endln;

        // Symbols that were received in the systematic phase correspond
        // to the original source symbols and are therefore marked as
        // decoded
        std::cout << "Symbols decoded " << decoder.symbols_uncoded() << std:endln;
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

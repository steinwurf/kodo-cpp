// Copyright Steinwurf ApS 2011-2012.
// Distributed under the "STEINWURF RESEARCH LICENSE 1.0".
// See accompanying file LICENSE.rst or
// http://www.steinwurf.com/licensing

#include <iostream>
#include <vector>

#include <kodocpp/kodocpp.hpp>


/// @example encode_decode_simple.cpp
///
/// Simple example showing how to encode and decode a block
/// of memory.

int main(void)
{
    // Set the number of symbols (i.e. the generation size in RLNC
    // terminology) and the size of a symbol in bytes
    uint32_t max_symbols = 42;
    uint32_t max_symbol_size = 160;

    bool enabled_trace = true;

    //Initilization of encoder and decoder
    encoder_factory encoder_factory = encoder_factory(
        kodo::algorithms.full_rlnc,
        kodo::field_types.binary8,
        max_symbols,
        max_symbol_size,
        enabled_trace);

    encoder encoder = encoder_factory.build();

    decoder_factory decoder_factory = decoder_factory(
        kodo::algorithm.kodo_full_rlnc,
        kodo::field_type.binary8,
        max_symbols,
        max_symbol_size,
        enable_trace);

    decoder decoder = decoder_factory.build();

    // Allocate some storage for a "payload" the payload is what we would
    // eventually send over a network
    std::vector<uint8_t> payload(encoder.payload_size());

    // Allocate some data to encode. In this case we make a buffer
    // with the same size as the encoder's block size (the max.
    // amount a single encoder can encode)
    std::vector<uint8_t> data_in(encoder.block_size());

    // Just for fun - fill the data with random data
    std::generate(data_in.begin(), data_in.end(), rand);

    // Assign the data buffer to the encoder so that we may start
    // to produce encoded symbols from it
    encoder.set_symbols(sak::storage(data_in));

    while(!decoder.is_complete())
    {
        // Encode the packet into the payload buffer
        encoder.encode(payload.data());

        // Pass that packet to the decoder
        decoder.decode(payload.data());
    }

     // The decoder is complete, now copy the symbols from the decoder
    std::vector<uint8_t> data_out(decoder.block_size());
    decoder.copy_symbols(sak::storage(data_out));

    // Check we properly decoded the data
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

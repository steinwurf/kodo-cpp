#include <cstdlib>
#include <iostream>
#include <vector>
#include <algorithm>

#include <kodocpp/kodocpp.hpp>


int main(void)
{
    // Set the number of symbols (i.e. the generation size in RLNC
    // terminology) and the size of a symbol in bytes
    uint32_t max_symbols = 42;
    uint32_t max_symbol_size = 160;

    bool trace_enabled = true;

    //Initilization of encoder and decoder
    kodocpp::encoder_factory encoder_factory(
        kodocpp::code_type::on_the_fly,
        kodocpp::finite_field::binary8,
        max_symbols,
        max_symbol_size,
        trace_enabled);

    kodocpp::encoder encoder = encoder_factory.build();

    kodocpp::decoder_factory decoder_factory(
        kodocpp::code_type::on_the_fly,
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


    // We are starting the encoding / decoding looop without having
    // added any data to the encoder - we will add symbols on-the-fly
    while(!decoder.is_complete())
    {
        std::vector<uint32_t> bytes_used;

        // Randomly choose to add a new symbol (with 50% porbability)
        // if the encoder rank is less than the maximum number of symbols
        if((rand % 2) && encoder.rank() < encoder.symbols())
        {
            // The rank of an encoder  indicates how many symbols have been added,
            // i.e. how many symbols are available for encoding
            uint32_t rank = encoder.rank();

            // Calculate the offset to the nex symbol to insert
            // N.B: CHANGE TO VECTOR
            //uint8_t* symbol  = data_in.data
        }
    }
}

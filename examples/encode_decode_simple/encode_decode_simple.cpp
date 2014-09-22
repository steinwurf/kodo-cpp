// Copyright Steinwurf ApS 2011-2012.
// Distributed under the "STEINWURF RESEARCH LICENSE 1.0".
// See accompanying file LICENSE.rst or
// http://www.steinwurf.com/licensing

#include <iostream>
//#include <kodocpp/>
namespace kodo
{
    int main(void)
    {
        //Remember to seed random

        uint32_t symbols = 42;
        uint32_t symbol_size = 160;

        typedef kodo::full_rlnc_encoder<fifi:binary8> rlnc_encoder;

        kodo::encoder_factory_wrapper* encoder_factory
            = new kodo::encoder_factory<rlnc_encoder>()

        // Allocate some data to encode. In this case we make a buffer
        // with the same size as the encoder's block size (the max.
        // amount a single encoder can encode)
        ////Change to the encoder :)
        std::vector<uint8_t> data_in(200);


        for(auto &e: data_in)
        {
            e = rand() % 256;
        }

        return 0;
    }
}

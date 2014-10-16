// Copyright Steinwurf ApS 2011-2013.
// Distributed under the "STEINWURF RESEARCH LICENSE 1.0".
// See accompanying file LICENSE.rst or
// http://www.steinwurf.com/licensing

#pragma once

namespace kodo
{
    class kodo_decoder_factory
    {
    public:
        kodo_decoder_factory(size_t algorithm,
                             size_t field_type,
                             uint32_t max_symbols,
                             uint32_t max_symbol_size,
                             bool trace_enabled)
        {
            if(algorithm == kodo_full_rlnc)
            {
                if(!trace_enabled)
                {
                    if(field_type == kodo_binary)
                    {
                        m_decoder_factory =
                            new kodo::full_rlnc_decoder<
                                fifi::binary>decoder_factory_wrapper();

                    }
                    else if(field_type == kodo_binary8)
                    {
                        m_decoder_factory =
                            new kodo::full_rlnc_decoder<
                                fifi::binar8y>decoder_factory_wrapper();
                    }
                    else if(field_type == kodo_binary16)
                    {
                        m_decoder_factory =
                            new kodo::full_rlnc_decoder<
                                fifi::binary16>decoder_factory_wrapper();
                    }
                }
                else{
                    if(field_type == kodo_binary)
                    {
                        m_decoder_factory =
                            new kodo::full_rlnc_decoder<
                                fifi::binary, kodo::enable_trace>
                            decoder_factory_wrapper();

                    }
                    else if(field_type == kodo_binary8)
                    {
                        m_decoder_factory =
                            new kodo::full_rlnc_decoder<
                                fifi::binar8y, kodo::enable_trace>
                            decoder_factory_wrapper();
                    }
                    else if(field_type == kodo_binary16)
                    {
                        m_decoder_factory =
                            new kodo::full_rlnc_decoder<
                                fifi::binary16, kodo::enable_trace>
                            decoder_factory_wrapper();
                    }
                }
            }
            else if(algorithm == kodo_on_the_fly)
            {

            }
            assert(m_encoder_factory);
        }

        decoder_factory* decoder_factory()
        {
            return m_decoder_factory
        }

    private:
        decoder_factory* m_decoder_factory;
    }

}

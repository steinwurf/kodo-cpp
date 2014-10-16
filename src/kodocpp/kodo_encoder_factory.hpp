
// Copyright Steinwurf ApS 2011-2013.
// Distributed under the "STEINWURF RESEARCH LICENSE 1.0".
// See accompanying file LICENSE.rst or
// http://www.steinwurf.com/licensing

#pragma once

namespace kodo
{
    class kodo_encoder_factory
    {
    public:
        kodo_encoder_factory(size_t algorithm,
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
                        m_encoder_factory =
                            new kodo::full_rlnc_encoder<
                                fifi::binary>encoder_factory_wrapper();
                    }
                    else if(field_type == kodo_binary8)
                    {
                        m_encoder_factory =
                            new kodo::full_rlnc_encoder<
                                fifi::binary8>encoder_factory_wrapper()
                    }
                    else if(field_type == kodo_binary16)
                    {
                        m_encoder_factory =
                            new kodo::full_rlnc_encoder<
                                fifi::binary16>encoder_factory_wrapper()
                    }
                }
                else
                {
                    if(field_type == kodo_binary)
                    {
                        m_encoder_factory =
                            new kodo::kodo::full_rlnc_encoder<
                                fifi::binary, kodo::enable_trace>
                            encoder_factory_wrapper();
                    }
                    else if(field_type == kodo_binary8)
                    {
                        m_encoder_factory =
                            new kodo::full_rlnc_encoder<
                            fifi::binary8, kodo::enable_trace>
                            encoder_factory_wrapper()
                    }
                    else if(field_type == kodo_binary16)
                    {
                        m_encoder_factory =
                            new kodo::full_rlnc_encoder<
                                fifi::binary16, kodo::enable_trace>
                            encoder_factory_wrapper()
                    }
                }
                assert(m_encoder_factory);
            }
            else if(algorithm == kodo_on_the_fly)
            {
                if(!trace_enabled)
                {
                    if(field_type == kodo_binary)
                    {
                        m_encoder_factory =
                            new kodo::on_the_fly_encoder<
                                fifi::binary>encoder_factory_wrapper();
                    }
                    else if(field_type == kodo_binary8)
                    {
                        m_encoder_factory =
                            new kodo::on_the_fly_encoder<
                                fifi::binary8>encoder_factory_wrapper()
                    }
                    else if(field_type == kodo_binary16)
                    {
                        m_encoder_factory =
                            new kodo::on_the_fly_encoder<
                                fifi::binary16>encoder_factory_wrapper()
                    }
                }
                else
                {
                    if(field_type == kodo_binary)
                    {
                        m_encoder_factory =
                            new kodo::kodo::on_the_fly_encoder<
                                fifi::binary, kodo::enable_trace>
                            encoder_factory_wrapper();
                    }
                    else if(field_type == kodo_binary8)
                    {
                        m_encoder_factory =
                            new kodo::on_the_fly_encoder<
                            fifi::binary8, kodo::enable_trace>
                            encoder_factory_wrapper()
                    }
                    else if(field_type == kodo_binary16)
                    {
                        m_encoder_factory =
                            new kodo::on_the_fly_encoder<
                                fifi::binary16, kodo::enable_trace>
                            encoder_factory_wrapper()
                    }
                }
                assert(m_encoder_factory);
            }
            else if(algorithm == kodo_sliding_window)
            {
                if(!trace_enabled)
                {
                    if(field_type == kodo_binary)
                    {
                        m_encoder_factory =
                            new kodo::sliding_window_encoder<
                                fifi::binary>encoder_factory_wrapper();
                    }
                    else if(field_type == kodo_binary8)
                    {
                        m_encoder_factory =
                            new kodo::sliding_window_encoder<
                                fifi::binary8>encoder_factory_wrapper()
                    }
                    else if(field_type == kodo_binary16)
                    {
                        m_encoder_factory =
                            new kodo::sliding_window_encoder<
                                fifi::binary16>encoder_factory_wrapper()
                    }
                }
                else
                {
                    if(field_type == kodo_binary)
                    {
                        m_encoder_factory =
                            new kodo::kodo::sliding_window_encoder<
                                fifi::binary, kodo::enable_trace>
                            encoder_factory_wrapper();
                    }
                    else if(field_type == kodo_binary8)
                    {
                        m_encoder_factory =
                            new kodo::sliding_window_encoder<
                            fifi::binary8, kodo::enable_trace>
                            encoder_factory_wrapper()
                    }
                    else if(field_type == kodo_binary16)
                    {
                        m_encoder_factory =
                            new kodo::sliding_window_encoder<
                                fifi::binary16, kodo::enable_trace>
                            encoder_factory_wrapper()
                    }
                }
                assert(m_encoder_factory);
            }
        }

        encoder_factory* encoder_factory()
        {
            return m_encoder_factory;
        }

    private:
        encoder_factory* m_encoder_factory;
    };
}

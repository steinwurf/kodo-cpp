// Copyright Steinwurf ApS 2011-2013.
// Distributed under the "STEINWURF RESEARCH LICENSE 1.0".
// See accompanying file LICENSE.rst or
// http://www.steinwurf.com/licensing

#pragma once

#include "factory_interface.hpp"

namespace kodo
{
    class encoder_factory : public factory_interface
    {
    public:
        encoder_factory(kodo::algorithm algorithm,
                             kodo::fieldtype field_type,
                             uint32_t max_symbols,
                             uint32_t max_symbol_size,
                             bool trace_enabled)
        {
            if(algorithm == kodo_full_rlnc)
            {
                if(!trace_enabled)
                {
                    if(field_type == kodo::field_type.binary)
                    {
                        m_encoder_factory =
                            new kodo::full_rlnc_encoder<
                                fifi::binary>encoder_factory_wrapper();
                    }
                    else if(field_type == kodo::field_type.binary8)
                    {
                        m_encoder_factory =
                            new kodo::full_rlnc_encoder<
                                fifi::binary8>encoder_factory_wrapper()
                    }
                    else if(field_type == kodo::field_type.binary16)
                    {
                        m_encoder_factory =
                            new kodo::full_rlnc_encoder<
                                fifi::binary16>encoder_factory_wrapper()
                    }
                }
                else
                {
                    if(field_type == kodo::field_type.binary)
                    {
                        m_encoder_factory =
                            new kodo::kodo::full_rlnc_encoder<
                                fifi::binary, kodo::enable_trace>
                            encoder_factory_wrapper();
                    }
                    else if(field_type == kodo::field_type.binary8)
                    {
                        m_encoder_factory =
                            new kodo::full_rlnc_encoder<
                            fifi::binary8, kodo::enable_trace>
                            encoder_factory_wrapper()
                    }
                    else if(field_type == kodo::field_type.binary16)
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
                    if(field_type == kodo::field_type.binary)
                    {
                        m_encoder_factory =
                            new kodo::on_the_fly_encoder<
                                fifi::binary>encoder_factory_wrapper();
                    }
                    else if(field_type == kodo::field_type.binary8)
                    {
                        m_encoder_factory =
                            new kodo::on_the_fly_encoder<
                                fifi::binary8>encoder_factory_wrapper()
                    }
                    else if(field_type == kodo::field_type.binary16)
                    {
                        m_encoder_factory =
                            new kodo::on_the_fly_encoder<
                                fifi::binary16>encoder_factory_wrapper()
                    }
                }
                else
                {
                    if(field_type == kodo::field_type.binary)
                    {
                        m_encoder_factory =
                            new kodo::kodo::on_the_fly_encoder<
                                fifi::binary, kodo::enable_trace>
                            encoder_factory_wrapper();
                    }
                    else if(field_type == kodo::field_type.binary8)
                    {
                        m_encoder_factory =
                            new kodo::on_the_fly_encoder<
                            fifi::binary8, kodo::enable_trace>
                            encoder_factory_wrapper()
                    }
                    else if(field_type == kodo::field_type.binary16)
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
                    if(field_type == kodo::field_type.binary)
                    {
                        m_encoder_factory =
                            new kodo::sliding_window_encoder<
                                fifi::binary>encoder_factory_wrapper();
                    }
                    else if(field_type == kodo::field_type.binary8)
                    {
                        m_encoder_factory =
                            new kodo::sliding_window_encoder<
                                fifi::binary8>encoder_factory_wrapper()
                    }
                    else if(field_type == kodo::field_type.binary16)
                    {
                        m_encoder_factory =
                            new kodo::sliding_window_encoder<
                                fifi::binary16>encoder_factory_wrapper()
                    }
                }
                else
                {
                    if(field_type == kodo::field_type.binary)
                    {
                        m_encoder_factory =
                            new kodo::kodo::sliding_window_encoder<
                                fifi::binary, kodo::enable_trace>
                            encoder_factory_wrapper();
                    }
                    else if(field_type == kodo::field_type.binary8)
                    {
                        m_encoder_factory =
                            new kodo::sliding_window_encoder<
                            fifi::binary8, kodo::enable_trace>
                            encoder_factory_wrapper()
                    }
                    else if(field_type == kodo::field_type.binary16)
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

        encoder build()
        {
            return encoder(new encoder_wrapper(m_encoder_factory).build())
        }

        void set_symbols(uint32_t symbols)
        {
            m_factory_wrapper.set_symbols(symbols)
        }

        void set_symbol_size(uint32_t symbol_size)
        {
            m_factory_wrapper.set_symbol_size(symbol_size)
        }

        uint32_t max_symbols() const
        {
            return m_factory_wrapper.max_symbols();
        }

        uint32_t max_symbol_size() const
        {
            return m_factory_wrapper.max_symbol_size();
        }

        uint32_t max_block_size() const
        {
            return m_factory_wrapper.max_block_size();
        }

        uint32_t max_payload_size() const
        {
            return m_factory_wrapper.max_payload_size();
        }

    private:
        encoder_factory* m_encoder_factory;
    };
}

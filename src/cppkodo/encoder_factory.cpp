// Copyright Steinwurf ApS 2011-2013.
// Distributed under the "STEINWURF RESEARCH LICENSE 1.0".
// See accompanying file LICENSE.rst or
// http://www.steinwurf.com/licensing


#include "encoder_factory.hpp"

namespace kodo
{
    encoder_factory::encoder_factory(kodo::algorithms algorithm,
                                     kodo::fieldtypes field_type,
                                     uint32_t max_symbols,
                                     uint32_t max_symbol_size,
                                     bool trace_enabled)
    {

        if(algorithm == algorithms.full_rlnc)
        {
            if(!trace_enabled)
            {
                if(field_type == kodo::field_type.binary)
                {
                    return new kodo::full_rlnc_encoder<
                        fifi::binary,
                        kodo::trace_enabled>encoder_factory_wrapper();
                }
                else if(field_type == kodo::field_type.binary4)
                {
                    return new kodo::full_rlnc_encoder<
                        fifi::binary4,
                        kodo::trace_enabled>encoder_factory_wrapper();
                }
                else if(field_type == kodo::field_type.binary8)
                {
                    return new kodo::full_rlnc_encoder<
                        fifi::binary8,
                        kodo::trace_enabled>encoder_factory_wrapper();
                }
                else if(field_type == kodo::field_type.binary16)
                {
                    return new kodo::full_rlnc_encoder<
                        fifi::binary16,
                        kodo::trace_enabled>encoder_factory_wrapper();
                }
            }
            else
            {
                if(field_type == kodo::field_type.binary)
                {
                    return new kodo::full_rlnc_encoder<
                        fifi::binary,
                        kodo::trace_enabled>encoder_factory_wrapper();
                }
                else if(field_type == kodo::field_type.binary4)
                {
                    return new kodo::full_rlnc_encoder<
                        fifi::binary4,
                        kodo::trace_enabled>encoder_factory_wrapper();
                }
                else if(field_type == kodo::field_type.binary8)
                {
                    return new kodo::full_rlnc_encoder<
                        fifi::binary8,
                        kodo::trace_enabled>encoder_factory_wrapper();
                }
                else if(field_type == kodo::field_type.binary16)
                {
                    return new kodo::full_rlnc_encoder<
                        fifi::binary16,
                        kodo::trace_enabled>encoder_factory_wrapper();
                }
            }
            assert(m_factory_wrapper);
        }
        else if(algorithm == kodo::algorithms.on_the_fly)
        {
            if(!trace_enabled)
            {
                if(field_type == kodo::field_type.binary)
                {
                    return new kodo::on_the_fly_encoder<
                        fifi::binary,
                        kodo::trace_enabled>encoder_factory_wrapper();
                }
                else if(field_type == kodo::field_type.binary4)
                {
                    return new kodo::on_the_fly_encoder<
                        fifi::binary4,
                        kodo::trace_enabled>encoder_factory_wrapper();
                }
                else if(field_type == kodo::field_type.binary8)
                {
                    return new kodo::on_the_fly_encoder<
                        fifi::binary8,
                        kodo::trace_enabled>encoder_factory_wrapper();
                }
                else if(field_type == kodo::field_type.binary16)
                {
                    return new kodo::on_the_fly_encoder<
                        fifi::binary16,
                        kodo::trace_enabled>encoder_factory_wrapper();
                }
            }
            else
            {
                if(field_type == kodo::field_type.binary)
                {
                    return new kodo::on_the_fly_encoder<
                        fifi::binary,
                        kodo::trace_enabled>encoder_factory_wrapper();
                }
                else if(field_type == kodo::field_type.binary4)
                {
                    return new kodo::on_the_fly_encoder<
                        fifi::binary4,
                        kodo::trace_enabled>encoder_factory_wrapper();
                }
                else if(field_type == kodo::field_type.binary8)
                {
                    return new kodo::on_the_fly_encoder<
                        fifi::binary8,
                        kodo::trace_enabled>encoder_factory_wrapper();
                }
                else if(field_type == kodo::field_type.binary16)
                {
                    return new kodo::on_the_fly_encoder<
                        fifi::binary16,
                        kodo::trace_enabled>encoder_factory_wrapper();
                }
            }
            assert(m_factory_wrapper);
        }
        else if(algorithm == kodo::algorithms.sliding_window)
        {
            if(!trace_enabled)
            {
                if(field_type == kodo::field_type.binary)
                {
                    return new kodo::sliding_window_encoder<
                        fifi::binary,
                        kodo::trace_enabled>encoder_factory_wrapper();
                }
                else if(field_type == kodo::field_type.binary4)
                {
                    return new kodo::sliding_window_encoder<
                        fifi::binary4,
                        kodo::trace_enabled>encoder_factory_wrapper();
                }
                else if(field_type == kodo::field_type.binary8)
                {
                    return new kodo::sliding_window_encoder<
                        fifi::binary8,
                        kodo::trace_enabled>encoder_factory_wrapper();
                }
                else if(field_type == kodo::field_type.binary16)
                {
                    return new kodo::sliding_window_encoder<
                        fifi::binary16,
                        kodo::trace_enabled>encoder_factory_wrapper();
                }
            }
            else
            {
                if(field_type == kodo::field_type.binary)
                {
                    return new kodo::sliding_window_encoder<
                        fifi::binary,
                        kodo::trace_enabled>encoder_factory_wrapper();
                }
                else if(field_type == kodo::field_type.binary4)
                {
                    return new kodo::sliding_window_encoder<
                        fifi::binary4,
                        kodo::trace_enabled>encoder_factory_wrapper();
                }
                else if(field_type == kodo::field_type.binary8)
                {
                    return new kodo::sliding_window_encoder<
                        fifi::binary8,
                        kodo::trace_enabled>encoder_factory_wrapper();
                }
                else if(field_type == kodo::field_type.binary16)
                {
                    return new kodo::sliding_window_encoder<
                        fifi::binary16,
                        kodo::trace_enabled>encoder_factory_wrapper();
                }
            }
            assert(m_factory_wrapper);
        }
        assert(m_factory_wrapper);
    }

    encoder encoder_factory::build()
    {
        return encoder(new encoder_wrapper(m_factory_wrapper).build());
    }

    void encoder_factory::set_symbols(uint32_t symbols)
    {
        m_factory_wrapper.set_symbols(symbols);
    }

    void encoder_factory::set_symbol_size(uint32_t symbol_size)
    {
        m_factory_wrapper.set_symbol_size(symbol_size);
    }

    uint32_t encoder_factory::max_symbols() const
    {
        return m_factory_wrapper.max_symbols();
    }

    uint32_t encoder_factory::max_symbol_size() const
    {
        return m_factory_wrapper.max_symbol_size();
    }

    uint32_t encoder_factory::max_block_size() const
    {
        return m_factory_wrapper.max_block_size();
    }

    uint32_t encoder_factory::max_payload_size() const
    {
        return m_factory_wrapper.max_payload_size();
    }
}

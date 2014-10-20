// Copyright Steinwurf ApS 2011-2013.
// Distributed under the "STEINWURF RESEARCH LICENSE 1.0".
// See accompanying file LICENSE.rst or
// http://www.steinwurf.com/licensing


#include "encoder_factory.hpp"

namespace kodo
{
    template<template <class, bool> KodoStack, class trace>
    KodoStack pick_field(kodo::fieldtype field_type)
    {
        if(field_type == kodo::field_type.binary)
        {
            return new KodoStack<
                fifi::binary,
                trace>encoder_factory_wrapper();
        }
        else if(field_type == kodo::field_type.binary8)
        {
            return new KodoStack<
                fifi::binary8,
                trace>encoder_factory_wrapper();
        }
        else if(field_type == kodo::field_type.binary16)
        {
            return new KodoStack<
                fifi::binary16,
                trace>encoder_factory_wrapper();
        }
    }

    encoder_factory::encoder_factory(kodo::algorithm algorithm,
                                     kodo::fieldtype field_type,
                                     uint32_t max_symbols,
                                     uint32_t max_symbol_size,
                                     bool trace_enabled);
    {
        if(algorithm == kodo_full_rlnc)
        {
            if(!trace_enabled)
            {
                m_factory_wrapper = pick_field<
                    full_rlnc_encoder, trace_disabled>(field_type);
            }
            else
            {
                m_factory_wrapper = pick_field<
                    full_rlnc_encoder, trace_enabled>(field_type);
            }
            assert(m_factory_wrapper);
        }
        else if(algorithm == kodo_on_the_fly)
        {
            if(!trace_enabled)
            {
                if(field_type == kodo::field_type.binary)
                {
                    m_factory_wrapper =
                        new kodo::on_the_fly_encoder<
                            fifi::binary>encoder_factory_wrapper();
                }
                else if(field_type == kodo::field_type.binary8)
                {
                    m_factory_wrapper =
                        new kodo::on_the_fly_encoder<
                            fifi::binary8>encoder_factory_wrapper();
                }
                else if(field_type == kodo::field_type.binary16)
                {
                    m_factory_wrapper =
                        new kodo::on_the_fly_encoder<
                            fifi::binary16>encoder_factory_wrapper();
                }
            }
            else
            {
                if(field_type == kodo::field_type.binary)
                {
                    m_factory_wrapper =
                        new kodo::kodo::on_the_fly_encoder<
                            fifi::binary, kodo::enable_trace>
                        encoder_factory_wrapper();
                }
                else if(field_type == kodo::field_type.binary8)
                {
                    m_factory_wrapper =
                        new kodo::on_the_fly_encoder<
                            fifi::binary8, kodo::enable_trace>
                        encoder_factory_wrapper();
                }
                else if(field_type == kodo::field_type.binary16)
                {
                    m_factory_wrapper =
                        new kodo::on_the_fly_encoder<
                            fifi::binary16, kodo::enable_trace>
                        encoder_factory_wrapper();
                }
            }
            assert(m_factory_wrapper);
        }
        else if(algorithm == kodo_sliding_window)
        {
            if(!trace_enabled)
            {
                if(field_type == kodo::field_type.binary)
                {
                    m_factory_wrapper =
                        new kodo::sliding_window_encoder<
                            fifi::binary>encoder_factory_wrapper();
                }
                else if(field_type == kodo::field_type.binary8)
                {
                    m_factory_wrapper =
                        new kodo::sliding_window_encoder<
                            fifi::binary8>encoder_factory_wrapper();
                }
                else if(field_type == kodo::field_type.binary16)
                {
                    m_factory_wrapper =
                        new kodo::sliding_window_encoder<
                            fifi::binary16>encoder_factory_wrapper();
                }
            }
            else
            {
                if(field_type == kodo::field_type.binary)
                {
                    m_factory_wrapper =
                        new kodo::kodo::sliding_window_encoder<
                            fifi::binary, kodo::enable_trace>
                        encoder_factory_wrapper();
                }
                else if(field_type == kodo::field_type.binary8)
                {
                    m_factory_wrapper =
                        new kodo::sliding_window_encoder<
                            fifi::binary8, kodo::enable_trace>
                        encoder_factory_wrapper();
                }
                else if(field_type == kodo::field_type.binary16)
                {
                    m_factory_wrapper =
                        new kodo::sliding_window_encoder<
                            fifi::binary16, kodo::enable_trace>
                        encoder_factory_wrapper();
                }
            }
            assert(m_factory_wrapper);
        }
    }

    encoder_factory::encoder build()
    {
        return encoder(new encoder_wrapper(m_factory_wrapper).build());
    }

    encoder_factory::void set_symbols(uint32_t symbols)
    {
        m_factory_wrapper.set_symbols(symbols);
    }

    encoder_factory::void set_symbol_size(uint32_t symbol_size)
    {
        m_factory_wrapper.set_symbol_size(symbol_size);
    }

    encoder_factory::uint32_t max_symbols() const
    {
        return m_factory_wrapper.max_symbols();
    }

    encoder_factory::uint32_t max_symbol_size() const
    {
        return m_factory_wrapper.max_symbol_size();
    }

    encoder_factory::uint32_t max_block_size() const
    {
        return m_factory_wrapper.max_block_size();
    }

    encoder_factory::uint32_t max_payload_size() const
    {
        return m_factory_wrapper.max_payload_size();
    }
}

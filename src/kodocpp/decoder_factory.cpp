// Copyright Steinwurf ApS 2011-2013.
// Distributed under the "STEINWURF RESEARCH LICENSE 1.0".
// See accompanying file LICENSE.rst or
// http://www.steinwurf.com/licensing

#include "decoder_factory.hpp"

namespace kodo{

    // Help fuction for creating factories
    template<template <class, bool> KodoStack, class trace>
    KodoStack pick_field(kodo::fieldtype field_type)
    {
        if(field_type == kodo::field_type.binary)
        {
            return new KodoStack<
                fifi::binary,
                trace>decoder_factory_wrapper();
        }
        else if(field_type == kodo::field_type.binary4)
        {
            return new KodoStack<
                fifi::binary4,
                trace>decoder_factory_wrapper();
        }
        else if(field_type == kodo::field_type.binary8)
        {
            return new KodoStack<
                fifi::binary8,
                trace>decoder_factory_wrapper();
        }
        else if(field_type == kodo::field_type.binary16)
        {
            return new KodoStack<
                fifi::binary16,
                trace>decoder_factory_wrapper();
        }
    }

    decoder_factory::decoder_factory(kodo::algorithm algorithm,
                     kodo::fieldtype field_type,
                     uint32_t max_symbols,
                     uint32_t max_symbol_size,
                     bool trace_enabled)
     {
        if(algorithm == kodo::algorithms.full_rlnc)
        {
            if(!trace_enabled)
            {
                m_factory_wrapper = pick_field<
                    full_rlnc_decoder, trace_disabled>(field_type);
            }
            else
            {
                m_factory_wrapper = pick_field<
                    full_rlnc_decoder, trace_enabled>(field_type);
            }
            assert(m_factory_wrapper);
        }
        else if(algorithm == kodo::algorithms.on_the_fly)
        {
            if(!trace_enabled)
            {
                m_factory_wrapper = pick_field<
                    on_the_fly_decoder, trace_disabled>(field_type);
            }
            else
            {
                m_factory_wrapper = pick_field<
                    on_the_fly_decoder, trace_enabled>(field_type);
            }
            assert(m_factory_wrapper);
        }
        else if(algorithm == kodo::algorithms.sliding_window)
        {
            if(!trace_enabled)
            {
                m_factory_wrapper = pick_field<
                    sliding_window_decoder, trace_disabled>(field_type);
            }
            else
            {
                m_factory_wrapper = pick_field<
                    sliding_window_decoder, trace_enabled>(field_type);
            }
            assert(m_factory_wrapper);
        }
        assert(m_factory_wrapper);
     }

     decoder_factory::decoder build()
     {
         return decoder(new decoder_wrapper(m_factory_wrapper).build());
     }

     decoder_factory::void set_symbols(uint32_t symbols)
     {
         m_factory_wrapper.set_symbols(symbols);
     }

     decoder_factory::void set_symbol_size(uint32_t symbol_size)
     {
         m_factory_wrapper.set_symbol_size(symbol_size);
     }

     decoder_factory::uint32_t max_symbols() const
     {
         return m_factory_wrapper.max_symbols();
     }

     decoder_factory::uint32_t max_symbol_size() const
     {
         return m_factory_wrapper.max_symbol_size();
     }

     decoder_factory::uint32_t max_block_size() const
     {
         return m_factory_wrapper.max_block_size();
     }

     decoder_factory::uint32_t max_payload_size() const
     {
         return m_factory_wrapper.max_payload_size();
     }
 }

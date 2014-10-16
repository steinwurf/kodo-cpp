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
        encoder_factory(size_t encoder_type, size_t field_type,
                        bool trace_enabled, uint32_t max_symbols,
                        uint32_t max_symbol_size)
        {
            if(encoder_type == kodo_full_rlnc)
            {
                if(trace_enabled)
                {
                    if(field_type == kodo_binary)
                    {
                        m_factory_interface = new encoder_factory_wrapper<
                            kodo::full_rlnc_encoder<
                                fifi:binary,
                                kodo::enable_trace>(
                                    max_symbols,
                                    max_symbol_size);
                    }
                    else if(field_type == kodo_binary8)
                    {
                        m_factory_interface = new encoder_factory_wrapper<
                            kodo::full_rlnc_encoder<
                                fifi:binary8,
                                kodo::enable_trace>(
                                    max_symbols,
                                    max_symbol_size);
                    }
                    else if(field_type == kodo_binary16)
                    {
                        m_factory_interface = new encoder_factory_wrapper<
                            kodo::full_rlnc_encoder<
                                fifi:binary16,
                                kodo::enable_trace>(
                                    max_symbols,
                                    max_symbol_size);
                    }
                }
                else
                {
                    if(field_type == kodo_binary)
                    {
                        m_factory_interface new encoder_factory_wrapper<
                            kodo::full_rlnc_encoder<fifi:binary>(
                                max_symbols,
                                max_symbol_size);
                    }
                    else if(field_type == kodo_binary8)
                    {
                        m_factory_interface new encoder_factory_wrapper<
                            kodo::full_rlnc_encoder<fifi:binary8>(
                                max_symbols,
                                max_symbol_size);
                    }
                    else if(field_type == kodo_binary16)
                    {
                        m_factory_interface new encoder_factory_wrapper<
                            kodo::full_rlnc_encoder<fifi:binary16>(
                                max_symbols,
                                max_symbol_size);
                    }
                }
            }
            else if(encoder_type == kodo_sliding_window)
            {
                if(trace_enabled)
                {
                    if(field_type == kodo_binary)
                    {
                        m_factory_interface = new encoder_factory_wrapper<
                            kodo::sliding_window<
                                fifi:binary,
                                kodo::enable_trace>(
                                    max_symbols,
                                    max_symbol_size);
                    }
                    else if(field_type == kodo_binary8)
                    {
                        m_factory_interface = new encoder_factory_wrapper<
                            kodo::sliding_window<
                                fifi:binary8,
                                kodo::enable_trace>(
                                    max_symbols,
                                    max_symbol_size);
                    }
                    if(field_type == kodo_binary16)
                    {
                        m_factory_interface = new encoder_factory_wrapper<
                            kodo::sliding_window<
                                fifi:binary16,
                                kodo::enable_trace>(
                                    max_symbols,
                                    max_symbol_size);
                    }
                }
                else
                {
                    if(field_type == kodo_binary)
                    {
                        m_factory_interface = new encoder_factory_wrapper<
                            kodo::sliding_window<
                                fifi:binary>(
                                    max_symbols,
                                    max_symbol_size);
                    }
                    else if(field_type == kodo_binary8)
                    {
                        m_factory_interface = new encoder_factory_wrapper<
                            kodo::sliding_window<
                                fifi:binary8>(
                                    max_symbols,
                                    max_symbol_size);
                    }
                    if(field_type == kodo_binary16)
                    {
                        m_factory_interface = new encoder_factory_wrapper<
                            kodo::sliding_window<
                                fifi:binary16>(
                                    max_symbols,
                                    max_symbol_size);
                    }

                }
            }

        }
    private:
        factory_interface* m_factory_interface
    }

}

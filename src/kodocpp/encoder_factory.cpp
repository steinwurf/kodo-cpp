// Copyright Steinwurf ApS 2011-2013.
// Distributed under the "STEINWURF RESEARCH LICENSE 1.0".
// See accompanying file LICENSE.rst or
// http://www.steinwurf.com/licensing

#include <kodo/rlnc/full_rlnc_codes.hpp>
#include <kodo/rlnc/on_the_fly_codes.hpp>

#include <kodo/rlnc/sliding_window_encoder.hpp>
#include <kodo/rlnc/sliding_window_decoder.hpp>

#include "internal/factory_interface.hpp"
#include "internal/encoder_factory_wrapper.hpp"

#include "encoder_factory.hpp"

namespace kodocpp
{
    encoder_factory::encoder_factory(code_type code,
                                     finite_field field,
                                     uint32_t max_symbols,
                                     uint32_t max_symbol_size,
                                     bool trace_enabled)
    {
        using namespace kodo;

        if (code == code_type::full_rlnc)
        {
            if (!trace_enabled)
            {
                if (field == finite_field::binary)
                {
                    m_factory_wrapper = new encoder_factory_wrapper<
                        full_rlnc_encoder<fifi::binary,
                            disable_trace>>(max_symbols, max_symbol_size);
                }
                else if (field == finite_field::binary4)
                {
                    m_factory_wrapper = new encoder_factory_wrapper<
                        full_rlnc_encoder<fifi::binary4,
                            disable_trace>>(max_symbols, max_symbol_size);
                }
                else if (field == finite_field::binary8)
                {
                    m_factory_wrapper = new encoder_factory_wrapper<
                        full_rlnc_encoder<fifi::binary8,
                            disable_trace>>(max_symbols, max_symbol_size);
                }
                else if (field == finite_field::binary16)
                {
                    m_factory_wrapper = new encoder_factory_wrapper<
                        full_rlnc_encoder<fifi::binary16,
                            disable_trace>>(max_symbols, max_symbol_size);
                }
            }
            else
            {
                if (field == finite_field::binary)
                {
                    m_factory_wrapper = new encoder_factory_wrapper<
                        full_rlnc_encoder<fifi::binary,
                            enable_trace>>(max_symbols, max_symbol_size);
                }
                else if (field == finite_field::binary4)
                {
                    m_factory_wrapper = new encoder_factory_wrapper<
                        full_rlnc_encoder<fifi::binary4,
                            enable_trace>>(max_symbols, max_symbol_size);
                }
                else if (field == finite_field::binary8)
                {
                    m_factory_wrapper = new encoder_factory_wrapper<
                        full_rlnc_encoder<fifi::binary8,
                            enable_trace>>(max_symbols, max_symbol_size);
                }
                else if (field == finite_field::binary16)
                {
                    m_factory_wrapper = new encoder_factory_wrapper<
                        full_rlnc_encoder<fifi::binary16,
                            enable_trace>>(max_symbols, max_symbol_size);
                }
            }
        }
        else if (code == code_type::on_the_fly)
        {
            if (!trace_enabled)
            {
                if (field == finite_field::binary)
                {
                    m_factory_wrapper = new encoder_factory_wrapper<
                        on_the_fly_encoder<fifi::binary,
                            disable_trace>>(max_symbols, max_symbol_size);
                }
                else if (field == finite_field::binary4)
                {
                    m_factory_wrapper = new encoder_factory_wrapper<
                        on_the_fly_encoder<fifi::binary4,
                            disable_trace>>(max_symbols, max_symbol_size);
                }
                else if (field == finite_field::binary8)
                {
                    m_factory_wrapper = new encoder_factory_wrapper<
                        on_the_fly_encoder<fifi::binary8,
                            disable_trace>>(max_symbols, max_symbol_size);
                }
                else if (field == finite_field::binary16)
                {
                    m_factory_wrapper = new encoder_factory_wrapper<
                        on_the_fly_encoder<fifi::binary16,
                            disable_trace>>(max_symbols, max_symbol_size);
                }
            }
            else
            {
                if (field == finite_field::binary)
                {
                    m_factory_wrapper = new encoder_factory_wrapper<
                        on_the_fly_encoder<fifi::binary,
                            enable_trace>>(max_symbols, max_symbol_size);
                }
                else if (field == finite_field::binary4)
                {
                    m_factory_wrapper = new encoder_factory_wrapper<
                        on_the_fly_encoder<fifi::binary4,
                            enable_trace>>(max_symbols, max_symbol_size);
                }
                else if (field == finite_field::binary8)
                {
                    m_factory_wrapper = new encoder_factory_wrapper<
                        on_the_fly_encoder<fifi::binary8,
                            enable_trace>>(max_symbols, max_symbol_size);
                }
                else if (field == finite_field::binary16)
                {
                    m_factory_wrapper = new encoder_factory_wrapper<
                        on_the_fly_encoder<fifi::binary16,
                            enable_trace>>(max_symbols, max_symbol_size);
                }
            }
        }
        else if (code == code_type::sliding_window)
        {
            if (!trace_enabled)
            {
                if (field == finite_field::binary)
                {
                    m_factory_wrapper = new encoder_factory_wrapper<
                        sliding_window_encoder<fifi::binary,
                            disable_trace>>(max_symbols, max_symbol_size);
                }
                else if (field == finite_field::binary4)
                {
                    m_factory_wrapper = new encoder_factory_wrapper<
                        sliding_window_encoder<fifi::binary4,
                            disable_trace>>(max_symbols, max_symbol_size);
                }
                else if (field == finite_field::binary8)
                {
                    m_factory_wrapper = new encoder_factory_wrapper<
                        sliding_window_encoder<fifi::binary8,
                            disable_trace>>(max_symbols, max_symbol_size);
                }
                else if (field == finite_field::binary16)
                {
                    m_factory_wrapper = new encoder_factory_wrapper<
                        sliding_window_encoder<fifi::binary16,
                            disable_trace>>(max_symbols, max_symbol_size);
                }
            }
            else
            {
                if (field == finite_field::binary)
                {
                    m_factory_wrapper = new encoder_factory_wrapper<
                        sliding_window_encoder<fifi::binary,
                            enable_trace>>(max_symbols, max_symbol_size);
                }
                else if (field == finite_field::binary4)
                {
                    m_factory_wrapper = new encoder_factory_wrapper<
                        sliding_window_encoder<fifi::binary4,
                            enable_trace>>(max_symbols, max_symbol_size);
                }
                else if (field == finite_field::binary8)
                {
                    m_factory_wrapper = new encoder_factory_wrapper<
                        sliding_window_encoder<fifi::binary8,
                            enable_trace>>(max_symbols, max_symbol_size);
                }
                else if (field == finite_field::binary16)
                {
                    m_factory_wrapper = new encoder_factory_wrapper<
                        sliding_window_encoder<fifi::binary16,
                            enable_trace>>(max_symbols, max_symbol_size);
                }
            }
        }
        assert(m_factory_wrapper);
    }

    encoder_factory::~encoder_factory()
    {
        delete m_factory_wrapper;
    }

    encoder encoder_factory::build()
    {
        auto wrapper = m_factory_wrapper->build();
        return encoder(wrapper);
    }

    void encoder_factory::set_symbols(uint32_t symbols)
    {
        m_factory_wrapper->set_symbols(symbols);
    }

    void encoder_factory::set_symbol_size(uint32_t symbol_size)
    {
        m_factory_wrapper->set_symbol_size(symbol_size);
    }

    uint32_t encoder_factory::max_symbols() const
    {
        return m_factory_wrapper->max_symbols();
    }

    uint32_t encoder_factory::max_symbol_size() const
    {
        return m_factory_wrapper->max_symbol_size();
    }

    uint32_t encoder_factory::max_block_size() const
    {
        return m_factory_wrapper->max_block_size();
    }

    uint32_t encoder_factory::max_payload_size() const
    {
        return m_factory_wrapper->max_payload_size();
    }
}

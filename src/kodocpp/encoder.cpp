// Copyright Steinwurf ApS 2011-2013.
// Distributed under the "STEINWURF RESEARCH LICENSE 1.0".
// See accompanying file LICENSE.rst or
// http://www.steinwurf.com/licensing

#include <cassert>

#include "internal/encoder_interface.hpp"

#include "encoder.hpp"

namespace kodocpp
{
    encoder::encoder(encoder_interface* wrapper) :
        m_wrapper(wrapper)
    {
        assert(m_wrapper);
    }

    encoder::~encoder()
    {
        delete m_wrapper;
    }

    uint32_t encoder::block_size() const
    {
        return m_wrapper->block_size();
    }

    uint32_t encoder::payload_size() const
    {
        return m_wrapper->payload_size();
    }

    uint32_t encoder::rank() const
    {
        return m_wrapper->rank();
    }

    uint32_t encoder::symbol_size() const
    {
        return m_wrapper->symbol_size();
    }

    uint32_t encoder::symbols() const
    {
        return m_wrapper->symbols();
    }

    bool encoder::symbol_pivot(uint32_t index) const
    {
        return m_wrapper->symbol_pivot(index);
    }

    bool encoder::has_trace() const
    {
        return m_wrapper->has_trace();
    }

    void encoder::trace(std::function<bool(std::string)> filter)
    {
        m_wrapper->trace(filter);
    }

    bool encoder::has_feedback_size() const
    {
        return m_wrapper->has_feedback_size();
    }

    uint32_t encoder::feedback_size() const
    {
        return m_wrapper->feedback_size();
    }

    uint32_t encoder::encode(uint8_t* payload)
    {
        return m_wrapper->encode(payload);
    }

    void encoder::set_symbols(const uint8_t* data, uint32_t size)
    {
        m_wrapper->set_symbols(data, size);
    }

    void encoder::set_symbol(
        uint32_t index, const uint8_t* data, uint32_t size)
    {
        m_wrapper->set_symbol(index, data, size);
    }

    bool encoder::has_systematic_encoder() const
    {
        return m_wrapper->has_systematic_encoder();
    }

    bool encoder::is_systematic_on() const
    {
        return m_wrapper->is_systematic_on();
    }

    void encoder::set_systematic_on()
    {
        m_wrapper->set_systematic_on();
    }

    void encoder::set_systematic_off()
    {
        m_wrapper->set_systematic_off();
    }

    void encoder::read_feedback(uint8_t* feedback)
    {
        m_wrapper->read_feedback(feedback);
    }
}

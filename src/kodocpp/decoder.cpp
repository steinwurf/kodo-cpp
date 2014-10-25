// Copyright Steinwurf ApS 2011-2013.
// Distributed under the "STEINWURF RESEARCH LICENSE 1.0".
// See accompanying file LICENSE.rst or
// http://www.steinwurf.com/licensing

#include "internal/decoder_interface.hpp"

#include "decoder.hpp"

namespace kodocpp
{
    decoder::decoder(decoder_interface* wrapper) :
        m_wrapper(wrapper)
    { }

    uint32_t decoder::block_size() const
    {
        return m_wrapper->block_size();
    }

    uint32_t decoder::payload_size() const
    {
        return m_wrapper->payload_size();
    }

    uint32_t decoder::rank() const
    {
        return m_wrapper->rank();
    }

    uint32_t decoder::symbol_size() const
    {
        return m_wrapper->symbol_size();
    }

    uint32_t decoder::symbols() const
    {
        return m_wrapper->symbols();
    }

    bool decoder::symbol_pivot(uint32_t index) const
    {
        return m_wrapper->symbol_pivot(index);
    }

    bool decoder::has_trace() const
    {
        return m_wrapper->has_trace();
    }

    void decoder::trace(std::function<bool(std::string)> filter)
    {
        m_wrapper->trace(filter);
    }

    bool decoder::has_feedback_size() const
    {
        return m_wrapper->has_feedback_size();
    }

    uint32_t decoder::feedback_size() const
    {
        return m_wrapper->feedback_size();
    }

    uint32_t decoder::recode(uint8_t* data)
    {
        return m_wrapper->recode(data);
    }

    void decoder::decode(uint8_t* data)
    {
        m_wrapper->decode(data);
    }

    bool decoder::is_complete() const
    {
        return m_wrapper->is_complete();
    }

    void decoder::copy_symbols(uint8_t* data, uint32_t size) const
    {
        m_wrapper->copy_symbols(data, size);
    }

    void decoder::copy_symbol(uint32_t index, uint8_t* data, uint32_t size) const
    {
        m_wrapper->copy_symbol(index, data, size);
    }

    bool decoder::has_partial_decoding_tracker() const
    {
        return m_wrapper->has_partial_decoding_tracker();
    }

    bool decoder::is_partial_complete() const
    {
        return m_wrapper->is_partial_complete();
    }

    bool decoder::is_symbol_uncoded(uint32_t index) const
    {
        return m_wrapper->is_symbol_uncoded(index);
    }

    uint32_t decoder::symbols_uncoded() const
    {
        return m_wrapper->symbols_uncoded();
    }

    uint32_t decoder::symbols_seen() const
    {
        return m_wrapper->symbols_seen();
    }

    void decoder::write_feedback(uint8_t* feedback)
    {
        m_wrapper->write_feedback(feedback);
    }
}

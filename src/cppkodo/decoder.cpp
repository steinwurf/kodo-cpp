// Copyright Steinwurf ApS 2011-2013.
// Distributed under the "STEINWURF RESEARCH LICENSE 1.0".
// See accompanying file LICENSE.rst or
// http://www.steinwurf.com/licensing

#include "decoder.hpp"

namespace kodo
{
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

// Copyright Steinwurf ApS 2011-2013.
// Distributed under the "STEINWURF RESEARCH LICENSE 1.0".
// See accompanying file LICENSE.rst or
// http://www.steinwurf.com/licensing

#include "coder.hpp"

namespace kodo
{
    uint32_t coder::block_size() const
    {
        return m_wrapper->block_size();
    }

    uint32_t coder::payload_size() const
    {
        return m_wrapper->payload_size();
    }

    uint32_t coder::rank() const
    {
        return m_wrapper->rank();
    }

    uint32_t coder::symbol_size() const
    {
        return m_wrapper->symbol_size();
    }

    uint32_t coder::symbols() const
    {
        return m_wrapper->symbols();
    }

    bool coder::symbol_pivot(uint32_t index) const
    {
        return m_wrapper->symbol_pivot(index);
    }

    bool coder::has_trace() const
    {
        return m_wrapper->has_trace();
    }

    void coder::trace(std::function<bool(std::string)> filter)
    {
        m_wrapper->trace(filter);
    }

    bool coder::has_feedback_size() const
    {
        return m_wrapper->has_feedback_size();
    }

    uint32_t coder::feedback_size() const
    {
        return m_wrapper->feedback_size();
    }
}

// Copyright Steinwurf ApS 2011-2013.
// Distributed under the "STEINWURF RESEARCH LICENSE 1.0".
// See accompanying file LICENSE.rst or
// http://www.steinwurf.com/licensing

#include "coder.hpp"
namespace kodo
{
    uint32_t block_size() const
    {
        return m_wrapper.block_size();
    }

    uint32_t payload_size() const
    {
        return m_wrapper.payload_size();
    }

    uint32_t rank() const
    {
        return m_wrapper.rank();
    }

    uint32_t symbol_size() const
    {
        return m_wrapper.symbol_size();
    }

    uint32_t symbols() const
    {
        return m_wrapper.symbols();
    }

    bool symbol_pivot(uint32_t index) const
    {
        return m_wrapper.symbol_pivot(index);
    }

    bool has_trace() const
    {
        return m_wrapper.has_trace();
    }

    void trace(std::function<bool(std::string)> filter)
    {
        m_wrapper.trace(filter);
    }

    bool has_feedback_size() const
    {
        return m_wrapper.has_feedback_size();
    }

    uint32_t feedback_size() const
    {
        return m_wrapper.feedback_size();
    }
}

// Copyright Steinwurf ApS 2011-2013.
// Distributed under the "STEINWURF RESEARCH LICENSE 1.0".
// See accompanying file LICENSE.rst or
// http://www.steinwurf.com/licensing

#pragma once

#include "internal/coder_interface.hpp"

namespace kodo
{
    class coder
    {
    public:
        coder(coder_interface* wrapper) : m_wrapper(wrapper)
        {

        }

        uint32_t block_size() const;
        uint32_t payload_size() const;
        uint32_t rank() const;
        uint32_t symbol_size() const;
        uint32_t symbols() const;
        bool symbol_pivot(uint32_t) const;

        bool has_trace() const;
        void trace(std::function<bool(std::string)>);

        bool has_feedback_size() const;
        uint32_t feedback_size() const;

    private:
        coder_interface* m_wrapper;
    };
}

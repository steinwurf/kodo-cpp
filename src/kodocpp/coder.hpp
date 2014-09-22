// Copyright Steinwurf ApS 2011-2013.
// Distributed under the "STEINWURF RESEARCH LICENSE 1.0".
// See accompanying file LICENSE.rst or
// http://www.steinwurf.com/licensing

#pragma once

#include "ckodo.h"

namespace kodo
{
    /// Base class for both encoder and decoder implementations.
    class coder
    {
    public:

        virtual ~coder() {}

        virtual uint32_t block_size() const = 0;
        virtual uint32_t payload_size() const = 0;
        virtual uint32_t rank() const = 0;
        virtual uint32_t symbol_size() const = 0;
        virtual uint32_t symbols() const = 0;
        virtual bool symbol_pivot(uint32_t) const = 0;

        virtual bool has_trace() const = 0;
        virtual void trace(kodo_filter_function_t) = 0;

        virtual bool has_feedback_size() const = 0;
        virtual uint32_t feedback_size() const = 0;
    };
}

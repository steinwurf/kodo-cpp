// Copyright Steinwurf ApS 2011-2013.
// Distributed under the "STEINWURF RESEARCH LICENSE 1.0".
// See accompanying file LICENSE.rst or
// http://www.steinwurf.com/licensing

#pragma once

#include <cassert>

#include <sak/storage.hpp>
#include <kodo/is_partial_complete.hpp>
#include <kodo/has_partial_decoding_tracker.hpp>

#include <kodo/trace_decode_symbol.hpp>
#include <kodo/symbol_decoding_status_tracker.hpp>
#include <kodo/trace.hpp>

namespace kodo
{
    template<class KodoStack, class Base>
    class coder_wrapper : public Base
    {
    public:

        coder_wrapper(const typename KodoStack::pointer& coder) :
            m_coder(coder)
        {
            assert(m_coder);
        }

        virtual uint32_t block_size() const
        {
            return m_coder->block_size();
        }

        virtual uint32_t payload_size() const
        {
            return m_coder->payload_size();
        }

        virtual uint32_t rank() const
        {
            return m_coder->rank();
        }

        virtual uint32_t symbol_size() const
        {
            return m_coder->symbol_size();
        }

        virtual uint32_t symbols() const
        {
            return m_coder->symbols();
        }

        virtual bool symbol_pivot(uint32_t index) const
        {
            return m_coder->is_symbol_pivot(index);
        }

        virtual bool has_trace() const
        {
            return kodo::has_trace<KodoStack>::value;
        }

        virtual void trace(kodo_filter_function_t filter_function)
        {
            if (filter_function)
            {
                auto filter = [&filter_function](const std::string& zone)
                {
                    return (filter_function(zone.c_str()) != 0);
                };
                kodo::trace<KodoStack>(m_coder, std::cout, filter);
            }
            else
            {
                kodo::trace<KodoStack>(m_coder, std::cout);
            }
        }

        virtual bool has_feedback_size() const
        {
            return kodo::has_feedback_size<KodoStack>::value;
        }

        virtual uint32_t feedback_size() const
        {
            return kodo::feedback_size(m_coder);
        }

    private:
        typename KodoStack::pointer m_coder;
    };
}

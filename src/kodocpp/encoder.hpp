// Copyright Steinwurf ApS 2011-2013.
// Distributed under the "STEINWURF RESEARCH LICENSE 1.0".
// See accompanying file LICENSE.rst or
// http://www.steinwurf.com/licensing

#pragma once

#include <cstdint>
#include <cassert>

#include <kodoc/kodoc.h>

#include "coder.hpp"
#include <iostream>

namespace kodocpp
{
    class encoder: public coder
    {
    public:

        encoder(kodo_coder_t coder_instance = 0) :
            coder(coder_instance,
                [](kodo_coder_t coder)
                {
                    if (coder != 0) kodo_delete_encoder(coder);
                })
        { }

        void set_symbols(uint8_t* data, uint32_t size)
        {
            kodo_set_symbols(m_coder.get(), data, size);
        }

        void set_symbol(uint32_t index, uint8_t* data, uint32_t size)
        {
            kodo_set_symbol(m_coder.get(), index, data, size);
        }

        bool has_set_systematic_off() const
        {
            return kodo_has_set_systematic_off(m_coder.get()) != 0;
        }

        bool is_systematic_on() const
        {
            return kodo_is_systematic_on(m_coder.get()) != 0;
        }

        void set_systematic_on()
        {
            kodo_set_systematic_on(m_coder.get());
        }

        void set_systematic_off()
        {
            kodo_set_systematic_off(m_coder.get());
        }

        void read_feedback(uint8_t* feedback)
        {
            kodo_read_feedback(m_coder.get(), feedback);
        }

        bool pseudo_systematic() const
        {
            return kodo_pseudo_systematic(m_coder.get()) != 0;
        }

        void set_pseudo_systematic(bool pseudo_systematic)
        {
            kodo_set_pseudo_systematic(m_coder.get(), pseudo_systematic);
        }

        bool pre_charging() const
        {
            return kodo_pre_charging(m_coder.get()) != 0;
        }

        void set_pre_charging(bool pre_charging)
        {
            kodo_set_pre_charging(m_coder.get(), pre_charging);
        }

        uint32_t width() const
        {
            return kodo_width(m_coder.get());
        }

        void set_width(uint32_t width)
        {
            kodo_set_width(m_coder.get(), width);
        }

        double width_ratio() const
        {
            return kodo_width_ratio(m_coder.get());
        }

        void set_width_ratio(double width_ratio)
        {
            kodo_set_width_ratio(m_coder.get(), width_ratio);
        }
    };
}

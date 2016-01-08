// Copyright Steinwurf ApS 2011-2013.
// Distributed under the "STEINWURF RESEARCH LICENSE 1.0".
// See accompanying file LICENSE.rst or
// http://www.steinwurf.com/licensing

#pragma once

#include <cstdint>
#include <cassert>

#include <kodoc/kodoc.h>

#include "coder.hpp"

namespace kodocpp
{
    class encoder: public coder
    {
    public:

        encoder(kodoc_coder_t coder_instance = 0) :
            coder(coder_instance, [](kodoc_coder_t coder)
                {
                    if (coder != 0) kodoc_delete_coder(coder);
                })
        { }

        void set_const_symbols(uint8_t* data, uint32_t size)
        {
            kodoc_set_const_symbols(m_coder.get(), data, size);
        }

        void set_const_symbol(uint32_t index, uint8_t* data, uint32_t size)
        {
            kodoc_set_const_symbol(m_coder.get(), index, data, size);
        }

        bool has_set_systematic_interface() const
        {
            return kodoc_has_systematic_interface(m_coder.get()) != 0;
        }

        bool is_systematic_on() const
        {
            return kodoc_is_systematic_on(m_coder.get()) != 0;
        }

        void set_systematic_on()
        {
            kodoc_set_systematic_on(m_coder.get());
        }

        void set_systematic_off()
        {
            kodoc_set_systematic_off(m_coder.get());
        }

        void read_feedback(uint8_t* feedback)
        {
            kodoc_read_feedback(m_coder.get(), feedback);
        }

        double density() const
        {
            return kodoc_density(m_coder.get());
        }

        void set_density(double density)
        {
            kodoc_set_density(m_coder.get(), density);
        }

        bool pseudo_systematic() const
        {
            return kodoc_pseudo_systematic(m_coder.get()) != 0;
        }

        void set_pseudo_systematic(bool pseudo_systematic)
        {
            kodoc_set_pseudo_systematic(m_coder.get(), pseudo_systematic);
        }

        bool pre_charging() const
        {
            return kodoc_pre_charging(m_coder.get()) != 0;
        }

        void set_pre_charging(bool pre_charging)
        {
            kodoc_set_pre_charging(m_coder.get(), pre_charging);
        }

        uint32_t width() const
        {
            return kodoc_width(m_coder.get());
        }

        void set_width(uint32_t width)
        {
            kodoc_set_width(m_coder.get(), width);
        }

        double width_ratio() const
        {
            return kodoc_width_ratio(m_coder.get());
        }

        void set_width_ratio(double width_ratio)
        {
            kodoc_set_width_ratio(m_coder.get(), width_ratio);
        }
    };
}

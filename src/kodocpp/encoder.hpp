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
        coder(coder_instance,
              [](kodoc_coder_t coder) { if (coder) kodoc_delete_coder(coder); })
    { }

    //------------------------------------------------------------------
    // SYMBOL STORAGE API
    //------------------------------------------------------------------

    /// Specifies the source data for all symbols. This will specify all
    /// symbols also in the case of partial data. If this is not desired,
    /// then the symbols should be specified individually. This also
    /// means that it is the responsibility of the user to communicate
    /// how many of the bytes transmitted are application data.
    /// @param data The buffer containing the data to be encoded
    /// @param size The size of the buffer to be encoded
    void set_const_symbols(uint8_t* data, uint32_t size)
    {
        kodoc_set_const_symbols(m_coder.get(), data, size);
    }

    /// Specifies the source data for a given symbol.
    /// @param index The index of the symbol in the coding block
    /// @param data The buffer containing the data to be encoded
    /// @param size The size of the symbol buffer
    void set_const_symbol(uint32_t index, uint8_t* data, uint32_t size)
    {
        kodoc_set_const_symbol(m_coder.get(), index, data, size);
    }

    //------------------------------------------------------------------
    // CODEC API
    //------------------------------------------------------------------

    /// Reads the feedback information from the provided buffer.
    /// @param feedback The buffer which contains the feedback information
    void read_feedback(uint8_t* feedback)
    {
        kodoc_read_feedback(m_coder.get(), feedback);
    }

    /// Writes an encoded symbol according to the provided symbol
    /// coefficients.
    /// @param symbol_data The destination buffer for the encoded symbol
    /// @param coefficients The desired coding coefficients that should
    ///        be used to calculate the encoded symbol.
    /// @return The number of bytes used.
    uint32_t write_symbol(uint8_t* symbol_data, uint8_t* coefficients)
    {
        return kodoc_write_symbol(m_coder.get(), symbol_data, coefficients);
    }

    /// Writes a systematic/uncoded symbol that corresponds to the provided
    /// symbol index.
    /// @param symbol_data The destination of the uncoded source symbol.
    /// @param index The index of this uncoded symbol in the data block.
    /// @return The number of bytes used.
    uint32_t write_uncoded_symbol(uint8_t* symbol_data, uint32_t index)
    {
        return kodoc_write_uncoded_symbol(
            m_coder.get(), symbol_data, index);
    }

    //------------------------------------------------------------------
    // SYSTEMATIC API
    //------------------------------------------------------------------

    /// Returns whether an encoder has systematic capabilities
    /// @param encoder The encoder
    /// @return true if the encoder supports the systematic mode
    bool has_systematic_interface() const
    {
        return kodoc_has_systematic_interface(m_coder.get()) != 0;
    }

    /// Returns whether the encoder is in the systematic mode, i.e. if it
    /// will initially send the original source symbols
    /// @return true if the encoder is in the systematic mode
    bool is_systematic_on() const
    {
        return kodoc_is_systematic_on(m_coder.get()) != 0;
    }

    /// Switches the systematic encoding on
    void set_systematic_on()
    {
        kodoc_set_systematic_on(m_coder.get());
    }

    /// Switches the systematic encoding off
    void set_systematic_off()
    {
        kodoc_set_systematic_off(m_coder.get());
    }

    //------------------------------------------------------------------
    // SPARSE ENCODER API
    //------------------------------------------------------------------

    /// Returns the current coding vector density of a sparse encoder.
    /// @return The coding vector density (0.0 < density <= 1.0)
    double density() const
    {
        return kodoc_density(m_coder.get());
    }

    /// Sets the coding vector density of a sparse encoder.
    /// @param density The density value (0.0 < density <= 1.0)
    void set_density(double density)
    {
        kodoc_set_density(m_coder.get(), density);
    }

    //------------------------------------------------------------------
    // PERPETUAL ENCODER API
    //------------------------------------------------------------------

    /// Get the pseudo-systematic property of the perpetual generator
    /// @return the current setting for pseudo-systematic
    bool pseudo_systematic() const
    {
        return kodoc_pseudo_systematic(m_coder.get()) != 0;
    }

    /// Set the pseudo-systematic property of the perpetual generator
    /// @param pseudo_systematic the new setting for pseudo-systematic
    void set_pseudo_systematic(bool pseudo_systematic)
    {
        kodoc_set_pseudo_systematic(m_coder.get(), pseudo_systematic);
    }

    /// Get the pre-charging property of the perpetual generator
    /// @return the current setting for pre-charging
    bool pre_charging() const
    {
        return kodoc_pre_charging(m_coder.get()) != 0;
    }

    /// Set the pre-charging property of the perpetual generator
    /// @param pre_charging the new setting for pre-charging
    void set_pre_charging(bool pre_charging)
    {
        kodoc_set_pre_charging(m_coder.get(), pre_charging);
    }

    /// Get the width (the number of non-zero coefficients after the pivot)
    /// @return the width used by the perpetual generator
    uint32_t width() const
    {
        return kodoc_width(m_coder.get());
    }

    /// Set the perpetual width, i.e. the number of non-zero coefficients
    /// after the pivot. The width_ratio is calculated from this value.
    /// @param width the perpetual width (0 <= width < symbols)
    void set_width(uint32_t width)
    {
        kodoc_set_width(m_coder.get(), width);
    }

    /// Get the ratio that is used to calculate the width
    /// @return the width ratio of the perpetual generator
    double width_ratio() const
    {
        return kodoc_width_ratio(m_coder.get());
    }

    /// Set the ratio that is used to calculate the number of non-zero
    /// coefficients after the pivot (i.e. the width)
    /// @param width_ratio the width ratio (0.0 < width_ratio <= 1.0)
    void set_width_ratio(double width_ratio)
    {
        kodoc_set_width_ratio(m_coder.get(), width_ratio);
    }

    //------------------------------------------------------------------
    // FULCRUM ENCODER API
    //------------------------------------------------------------------

    /// Get the number of nested symbols on a fulcrum encoder
    uint32_t nested_symbols()
    {
        return kodoc_nested_symbols(m_coder.get());
    }

    /// Get the number of nested symbol_size on a fulcrum encoder
    uint32_t nested_symbol_size()
    {
        return kodoc_nested_symbol_size(m_coder.get());
    }
};
}

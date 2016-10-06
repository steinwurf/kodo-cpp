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
class decoder: public coder
{
public:

    decoder(kodoc_coder_t coder_instance = 0) :
        coder(coder_instance,
              [](kodoc_coder_t coder) { if (coder) kodoc_delete_coder(coder); })
    { }

    //------------------------------------------------------------------
    // PAYLOAD API
    //------------------------------------------------------------------

    /// Reads the coded symbol in the payload buffer. The decoder state is
    /// updated during this operation.
    /// @param payload The buffer storing the payload of an encoded symbol.
    ///        The payload buffer may be changed by this operation,
    ///        so it cannot be reused. If the payload is needed at several
    ///        places, make sure to keep a copy of the original payload.
    void read_payload(uint8_t* payload)
    {
        kodoc_read_payload(m_coder.get(), payload);
    }

    //------------------------------------------------------------------
    // SYMBOL STORAGE API
    //------------------------------------------------------------------

    /// Specifies the data buffer where the decoder should store the
    /// decoded symbols. This will specify the storage for all symbols.
    /// If this is not desired, then the symbols can be specified
    /// individually
    /// @param data The buffer containing the data to be decoded
    /// @param size The size of the buffer to be decoded
    void set_mutable_symbols(uint8_t* data, uint32_t size)
    {
        kodoc_set_mutable_symbols(m_coder.get(), data, size);
    }

    /// Specifies the data buffer where the decoder should store a given
    /// symbol.
    /// @param index The index of the symbol in the coding block
    /// @param data The buffer that should contain the decoded symbol
    /// @param size The size of the symbol buffer
    void set_mutable_symbol(uint32_t index, uint8_t* data, uint32_t size)
    {
        kodoc_set_mutable_symbol(m_coder.get(), index, data, size);
    }

    //------------------------------------------------------------------
    // CODEC API
    //------------------------------------------------------------------

    /// Checks whether decoding is complete.
    /// @param decoder The decoder to query
    /// @return true if the decoding is complete
    bool is_complete() const
    {
        return kodoc_is_complete(m_coder.get()) != 0;
    }

    /// Check whether the decoder supports partial decoding. This means
    /// means that the decoder will be able to decode symbols on-the-fly.
    /// If the decoder supports the partial decoding tracker, then the
    /// is_partially_complete() function can be used to determine if
    /// some of the symbols are fully decoded.
    /// @return true if the decoder supports partial decoding
    bool has_partial_decoding_interface() const
    {
        return kodoc_has_partial_decoding_interface(m_coder.get()) != 0;
    }

    /// Check whether decoding is partially complete. This means that some
    /// symbols in the decoder are fully decoded. You can use the
    /// is_symbol_uncoded() function to determine which symbols.
    /// @return true if the decoding is partially complete
    bool is_partially_complete() const
    {
        return kodoc_is_partially_complete(m_coder.get()) != 0;
    }

    /// Writes the feedback information into the provided buffer.
    /// @param feedback The buffer which should contain the feedback
    ///        information.
    /// @return The total bytes used from the feeback buffer
    void write_feedback(uint8_t* feedback)
    {
        kodoc_write_feedback(m_coder.get(), feedback);
    }

    /// Indicates if a symbol is partially or fully decoded. A symbol with
    /// a pivot element is defined in the coding matrix of a decoder.
    /// @param index Index of the symbol whose state should be checked
    /// @return true if the symbol is defined
    bool is_symbol_pivot(uint32_t index) const
    {
        return kodoc_is_symbol_pivot(m_coder.get(), index) != 0;
    }

    /// Indicates whether a symbol is missing at a decoder.
    /// @param index Index of the symbol whose state should be checked
    /// @return true if the symbol is missing
    bool is_symbol_missing(uint32_t index)
    {
        return kodoc_is_symbol_missing(m_coder.get(), index) != 0;
    }

    /// Indicates whether a symbol has been partially decoded at a decoder.
    /// @param index Index of the symbol whose state should be checked
    /// @return true if the symbol has been partially decoded
    bool is_symbol_partially_decoded(uint32_t index)
    {
        return kodoc_is_symbol_partially_decoded(m_coder.get(), index) != 0;
    }

    /// Indicates whether a symbol is available in an uncoded (i.e. fully
    /// decoded) form at the decoder. To guarantee that the returned value is
    /// correct, the status updater had to be on (set_status_updater_on()) when
    /// a symbol was read, or the method update_symbol_status() had to be
    /// previously called.
    /// @param index Index of the symbol whose state should be checked
    /// @return true if the symbol is uncoded
    bool is_symbol_uncoded(uint32_t index) const
    {
        return kodoc_is_symbol_uncoded(m_coder.get(), index) != 0;
    }

    /// Returns the number of missing symbols.
    /// @return The number of missing symbols at the decoder
    uint32_t symbols_missing()
    {
        return kodoc_symbols_missing(m_coder.get());
    }

    /// Returns the number of partially decoded symbols.
    /// @return The number of partially decoded symbols at the decoder
    uint32_t symbols_partially_decoded() const
    {
        return kodoc_symbols_partially_decoded(m_coder.get());
    }

    /// Returns the number of uncoded (i.e. fully decoded) symbols. To guarantee
    /// that the returned value is correct, the status updater had to be on
    /// (set_status_updater_on()) when a symbol was read, or the method
    /// update_symbol_status() had to be previously called.
    /// @return The number of uncoded symbols at the decoder
    uint32_t symbols_uncoded() const
    {
        return kodoc_symbols_uncoded(m_coder.get());
    }

    /// Returns whether an decoder implements the
    /// symbol_decoding_status_updater_interface.
    /// @return True if the decoder implements the
    ///         symbol_decoding_status_updater_interface, otherwise false
    bool has_symbol_decoding_status_updater_interface() const
    {
        auto coder = m_coder.get();
        return kodoc_has_symbol_decoding_status_updater_interface(coder) != 0;
    }

    /// Sets the status updater on.
    void set_status_updater_on()
    {
        kodoc_set_status_updater_on(m_coder.get());
    }

    /// Sets the status updater off.
    void set_status_updater_off()
    {
        kodoc_set_status_updater_off(m_coder.get());
    }

    /// Updates the symbol status so that all uncoded symbols, label partially.
    void update_symbol_status()
    {
        kodoc_update_symbol_status(m_coder.get());
    }

    /// Returns whether the symbol status updater is enabled or not.
    /// @return True if the symbol status updater is enabled, otherwise false
    bool is_status_updater_enabled()
    {
        return kodoc_is_status_updater_enabled(m_coder.get()) != 0;
    }

    /// Reads and decodes an encoded symbol according to the provided
    /// coding coefficients.
    /// @param symbol_data The encoded symbol
    /// @param coefficients The coding coefficients that were used to
    ///        calculate the encoded symbol
    void read_symbol(uint8_t* symbol_data, uint8_t* coefficients)
    {
        kodoc_read_symbol(m_coder.get(), symbol_data, coefficients);
    }

    /// Reads and decodes a systematic/uncoded symbol with the
    /// corresponding symbol index.
    /// @param symbol_data The uncoded source symbol.
    /// @param index The index of this uncoded symbol in the data block.
    void read_uncoded_symbol(uint8_t* symbol_data, uint32_t index)
    {
        kodoc_read_uncoded_symbol(m_coder.get(), symbol_data, index);
    }
};
}

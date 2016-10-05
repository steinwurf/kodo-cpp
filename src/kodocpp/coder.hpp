// Copyright Steinwurf ApS 2011-2013.
// Distributed under the "STEINWURF RESEARCH LICENSE 1.0".
// See accompanying file LICENSE.rst or
// http://www.steinwurf.com/licensing

#pragma once

#include <cstdint>
#include <cassert>
#include <string>
#include <functional>

#include <kodoc/kodoc.h>
#include <memory>

namespace kodocpp
{
class coder
{
public:

    using callback_type =
        std::function<void(const std::string&, const std::string&)>;

protected:

    // Make sure that this base class cannot be instantiated
    coder(kodoc_coder_t coder, std::function<void(kodoc_coder_t)> deleter) :
        m_coder(coder, deleter)
    { }

public:

    //------------------------------------------------------------------
    // PAYLOAD API
    //------------------------------------------------------------------

    /// Returns the payload size of an encoder/decoder, which is the
    /// maximum size of a generated payload.
    /// @return The required payload buffer size in bytes
    uint32_t payload_size() const
    {
        return kodoc_payload_size(m_coder.get());
    }

    /// Writes a systematic/coded symbol into the provided payload buffer.
    /// @param payload The buffer which should contain the (re/en)coded
    ///        symbol.
    /// @return The total bytes used from the payload buffer
    uint32_t write_payload(uint8_t* payload)
    {
        return kodoc_write_payload(m_coder.get(), payload);
    }

    /// Checks whether the coder supports the write_payload() function.
    /// @return true if write_payload is supported
    bool has_write_payload()
    {
        return kodoc_has_write_payload(m_coder.get()) != 0;
    }

    //------------------------------------------------------------------
    // SYMBOL STORAGE API
    //------------------------------------------------------------------

    /// Returns the block size of an encoder/decoder.
    /// @return The block size, i.e. the total size in bytes
    ///         that this coder operates on.
    uint32_t block_size() const
    {
        return kodoc_block_size(m_coder.get());
    }

    /// Returns the symbol size of an encoder/decoder.
    /// @return The size of a symbol in bytes
    uint32_t symbol_size() const
    {
        return kodoc_symbol_size(m_coder.get());
    }

    /// Returns the number of symbols in a block (i.e. the generation size).
    /// @return The number of symbols
    uint32_t symbols() const
    {
        return kodoc_symbols(m_coder.get());
    }

    /// Returns the size of coefficient vector.
    /// @return The size of coefficient vector
    uint32_t coefficient_vector_size() const
    {
        return kodoc_coefficient_vector_size(m_coder.get());
    }

    //------------------------------------------------------------------
    // CODEC API
    //------------------------------------------------------------------

    /// The rank of a decoder indicates how many symbols have been decoded
    /// or partially decoded. The rank of an encoder indicates how many
    /// symbols are available for encoding.
    /// @return The rank of the decoder or encoder
    uint32_t rank() const
    {
        return kodoc_rank(m_coder.get());
    }

    /// Checks whether the encoder or decoder can use/provide feedback
    /// information. The encoder can disregard some symbols if the
    /// feedback from decoder indicates that those symbols were already
    /// decoded.
    /// @return true if feedback is supported
    bool has_feedback_size() const
    {
        return kodoc_has_feedback_size(m_coder.get()) != 0;
    }

    /// Returns the feedback size of an encoder/decoder.
    /// @return The size of the required feedback buffer in bytes
    uint32_t feedback_size() const
    {
        return kodoc_feedback_size(m_coder.get());
    }

    //------------------------------------------------------------------
    // TRACE API
    //------------------------------------------------------------------

    /// Returns whether an encoder or decoder supports the trace interface
    /// @return true if tracing is supported
    bool has_trace_interface() const
    {
        return kodoc_has_trace_interface(m_coder.get()) != 0;
    }

    /// Enables the trace function of the encoder/decoder, which prints
    /// to the standard output.
    void set_trace_stdout()
    {
        kodoc_set_trace_stdout(m_coder.get());
    }

    /// Registers a custom callback that will get the trace output of an
    /// encoder or decoder.
    /// @param callback The callback function that should process
    ///        the trace output
    void set_trace_callback(callback_type callback)
    {
        // This function object will be allocated on the heap, and its
        // address will remain valid until the shared pointer is destroyed.
        // Therefore it is safe to use this callback even after the coder
        // object is copied and destroyed (i.e. its this pointer becomes
        // invalid).
        m_callback.reset(new callback_type(callback));

        auto c_callback = [](const char* zone, const char* data,
                             void* context)
        {
            callback_type heap_callback = *((callback_type*)context);
            heap_callback(zone, data);
        };

        kodoc_set_trace_callback(
            m_coder.get(), c_callback, m_callback.get());
    }

    /// Disables the trace function of the encoder/decoder.
    void set_trace_off()
    {
        kodoc_set_trace_off(m_coder.get());
    }

    /// Sets the zone prefix that should be used for the trace output of
    /// a particular encoder/decoder instance. The zone prefix can help to
    /// differentiate the output that is coming from various coder
    /// instances.
    /// @param prefix The zone prefix for the trace output
    void set_zone_prefix(const std::string& prefix)
    {
        kodoc_set_zone_prefix(m_coder.get(), prefix.c_str());
    }

    //------------------------------------------------------------------
    // FULCRUM CODER API
    //------------------------------------------------------------------

    /// Get the number of expansion symbols on a fulcrum coder
    uint32_t expansion() const
    {
        return kodoc_expansion(m_coder.get());
    }

    /// Get the number of inner symbols on a fulcrum coder
    uint32_t inner_symbols() const
    {
        return kodoc_inner_symbols(m_coder.get());
    }

protected:

    std::shared_ptr<kodoc_coder> m_coder;

private:

    std::shared_ptr<callback_type> m_callback;
};
}

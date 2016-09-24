// Copyright Steinwurf ApS 2011-2013.
// Distributed under the "STEINWURF RESEARCH LICENSE 1.0".
// See accompanying file LICENSE.rst or
// http://www.steinwurf.com/licensing

#pragma once

#include <cstdint>
#include <cassert>
#include <memory>
#include <functional>

#include <kodoc/kodoc.h>

namespace kodocpp
{
class factory
{
protected:

    // Make sure that this base class cannot be instantiated
    factory(kodoc_factory_t factory,
            std::function<void(kodoc_factory_t)> deleter) :
        m_factory(factory, deleter)
    { }

public:

    /// Sets the number of symbols which should be used for the subsequent
    /// encoders / decoders built with this factory. The value must
    /// be below the max symbols used when the factory was constructed.
    /// @param symbols The number of symbols used for the next coder
    ///        built with the factory.
    void set_symbols(uint32_t symbols)
    {
        kodoc_factory_set_symbols(m_factory.get(), symbols);
    }

    /// Sets the symbol size which should be used for the subsequent
    /// encoders / decoders built with this factory. The value must
    /// be below the max symbol size used when the factory was constructed.
    /// @param symbol_size The symbol size used for the next coder
    ///        built with the factory.
    void set_symbol_size(uint32_t symbol_size)
    {
        kodoc_factory_set_symbol_size(m_factory.get(), symbol_size);
    }

    /// Returns the maximum number of symbols supported by the factory.
    /// @return the maximum number of symbols
    uint32_t max_symbols() const
    {
        return kodoc_factory_max_symbols(m_factory.get());
    }

    /// Returns the maximum symbol size supported by the factory.
    /// @return the maximum symbol size in bytes
    uint32_t max_symbol_size() const
    {
        return kodoc_factory_max_symbol_size(m_factory.get());
    }

    /// Returns the maximum block size supported by the factory.
    /// @return The maximum amount of data encoded / decoded in bytes.
    ///         This is calculated by multiplying the maximum number of
    ///         symbols by the maximum size of a symbol.
    uint32_t max_block_size() const
    {
        return kodoc_factory_max_block_size(m_factory.get());
    }

    /// Returns the maximum payload size supported by the factory.
    /// @return the maximum required payload buffer size in bytes
    uint32_t max_payload_size() const
    {
        return kodoc_factory_max_payload_size(m_factory.get());
    }

    //------------------------------------------------------------------
    // FULCRUM FACTORY API
    //------------------------------------------------------------------

    /// Get the maximum number of expansion symbols for a fulcrum factory
    uint32_t max_expansion() const
    {
        return kodoc_factory_max_expansion(m_factory.get());
    }

    /// Get the maximum number of inner symbols for a fulcrum factory
    uint32_t max_inner_symbols() const
    {
        return kodoc_factory_max_inner_symbols(m_factory.get());
    }

    /// Set the number of expansion symbols for a fulcrum factory
    /// @param expansion The number of expansion symbols to use
    void set_expansion(uint32_t expansion)
    {
        kodoc_factory_set_expansion(m_factory.get(), expansion);
    }

protected:

    std::shared_ptr<kodoc_factory> m_factory;
};
}

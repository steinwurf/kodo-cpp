// Copyright Steinwurf ApS 2011-2013.
// Distributed under the "STEINWURF RESEARCH LICENSE 1.0".
// See accompanying file LICENSE.rst or
// http://www.steinwurf.com/licensing

#include "decoder.hpp"

namespace kodo
{
    uint32_t decoder::recode(uint8_t* data)
    {
        return m_wrapper.recode(data);
    }

    void decoder::decode(uint8_t data)
    {
        return m_wrapper.decode(data);
    }

    bool decoder::is_complete()
    {
        return m_wrapper.is_complete();
    }

    void decoder::copy_symbols(uint8_t data, uint32_t size)
    {
        return m_wrappercopy_symbols(index, data, size);
    }

}

// Copyright Steinwurf ApS 2011-2013.
// Distributed under the "STEINWURF RESEARCH LICENSE 1.0".
// See accompanying file LICENSE.rst or
// http://www.steinwurf.com/licensing

namespace kodo
{
    uint32_t recode(uint8_t* data)
    {
        return m_wrapper.recode(data);
    }

    void decode(uint8_t data)
    {
        return m_wrapper.decode(data);
    }

    bool is_complete()
    {
        return m_wrapper.is_complete();
    }

    void copy_symbols(uint8_t data, uint32_t size)
    {
        return m_wrappercopy_symbols(index, data, size);
    }

}

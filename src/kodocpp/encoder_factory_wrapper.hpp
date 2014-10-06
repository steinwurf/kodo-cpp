// Copyright Steinwurf ApS 2011-2013.
// Distributed under the "STEINWURF RESEARCH LICENSE 1.0".
// See accompanying file LICENSE.rst or
// http://www.steinwurf.com/licensing

#pragma once

namespace kodo
{
    template<class KodoStack>
    class encoder_factory_wrapper : public factory_interface
    {
    public:
        encoder_factory_wrapper(uint32_t max_symbols, uint32_t max_symbol_size)
        {
            m_encoder_factory = new KodoStack::factory(
                max_symbols,
                max_symbol_size);
        }

        void set_symbols(uint32_t symbols)
        {
            m_encoder_factory->set_symbols(symbols);
        }

        void set_symbol_size(uint32_t symbol_size)
        {
            m_encoder_factory->set_symbol_size(symbol_size);
        }

        uint32_t max_symbols() const
        {
            return m_encoder_factory->max_symbols();
        }

        uint32_t max_symbol_size() const
        {
            return m_encoder_factory->max_symbol_size();
        }
        uint32_t max_block_size() const
        {
            return m_encoder_factory->max_block_size();
        }
        uint32_t max_payload_size() const
        {
            return m_encoder_factory->max_payload_size();
        }

        encoder_wrapper* build()
        {
            return new encoder_wrapper(m_encoder_factory.build());
        }

    private:
        KodoStack::factory* m_encoder_factory;
    }
}

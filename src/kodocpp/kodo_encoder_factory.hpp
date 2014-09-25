
// Copyright Steinwurf ApS 2011-2013.
// Distributed under the "STEINWURF RESEARCH LICENSE 1.0".
// See accompanying file LICENSE.rst or
// http://www.steinwurf.com/licensing

#pragma once

namespace kodo
{
    class kodo_encoder_factory
    {
        public kodo_encoder_factory(size_t algorithm,
                                    size_t field_type,
                                    uint32_t max_symbols,
                                    uint32_t max_symbol_size,
                                    bool trace_enabled)
        {
            if(algorithm == kodo_full_rlnc)
            {
                if(!trace_enabled)
                {
                    if(field_type == kodo_binary)
                    {
                        m_encoder_factory =
                            new kodo::<kodo::full_rlnc_encoder<
                                fiffi:binary>>encoder_factory_wrapper();
                    }
                }
            }
        }


        private encoder_factory* m_encoder_factory;
    }
}

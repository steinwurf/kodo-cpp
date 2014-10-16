// Copyright Steinwurf ApS 2011-2013.
// Distributed under the "STEINWURF RESEARCH LICENSE 1.0".
// See accompanying file LICENSE.rst or
// http://www.steinwurf.com/licensing

#prgama once
namespace kodo
{
    class encoder_factory : public factory
    {
    public:
        encoder_factory(size_t encoder_type) : factory(encoder_type)
        {

    }

        encoder build()
        {
            return encoder(new encoder_wrapper(m_wrapper.build()));
        }
    };
}

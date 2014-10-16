// Copyright Steinwurf ApS 2011-2013.
// Distributed under the "STEINWURF RESEARCH LICENSE 1.0".
// See accompanying file LICENSE.rst or
// http://www.steinwurf.com/licensing

class decoder
{
public:
    encoder(decoder_interface* wrapper) : m_wrapper(wrapper)
    {

    }

private:
    decoder_interface* m_wrapper;
}

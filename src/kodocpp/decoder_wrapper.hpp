// Copyright Steinwurf ApS 2011-2013.
// Distributed under the "STEINWURF RESEARCH LICENSE 1.0".
// See accompanying file LICENSE.rst or
// http://www.steinwurf.com/licensing

#pragma once

#include <cassert>

#include <sak/storage.hpp>

#include <kodo/write_feedback.hpp>

#include <kodo/is_partial_complete.hpp>
#include <kodo/has_partial_decoding_tracker.hpp>

#include <kodo/trace_decode_symbol.hpp>
#include <kodo/trace_linear_block_decoder.hpp>
#include <kodo/symbol_decoding_status_tracker.hpp>
#include <kodo/trace.hpp>

#include "coder_wrapper.hpp"
#include "decoder.hpp"

namespace kodo
{
    template<class KodoStack>
    class decoder_wrapper : public coder_wrapper<KodoStack, decoder>
    {
    public:

        decoder_wrapper(const typename KodoStack::pointer& coder) :
            coder_wrapper<KodoStack, decoder>(coder),
            m_decoder(coder)
        {
            assert(m_decoder);
        }

        virtual uint32_t recode(uint8_t *payload)
        {
            assert(payload);
            assert(m_decoder);

            return m_decoder->recode(payload);
        }

        virtual void decode(uint8_t *payload)
        {
            assert(payload);
            assert(m_decoder);

            m_decoder->decode(payload);
        }

        virtual bool is_complete() const
        {
            assert(m_decoder);
            return m_decoder->is_complete();
        }

        virtual void copy_symbols(uint8_t* data, uint32_t size) const
        {
            auto storage = sak::mutable_storage(data, size);
            m_decoder->copy_symbols(storage);
        }

        virtual void copy_symbol(uint32_t index, uint8_t* data,
                                 uint32_t size) const
        {
            auto storage = sak::mutable_storage(data, size);
            m_decoder->copy_symbol(index, storage);
        }

        virtual bool has_partial_decoding_tracker() const
        {
            return kodo::has_partial_decoding_tracker<KodoStack>::value;
        }

        virtual bool is_partial_complete() const
        {
            return kodo::is_partial_complete(m_decoder);
        }

        virtual bool is_symbol_uncoded(uint32_t index) const
        {
            return m_decoder->is_symbol_uncoded(index);
        }

        virtual uint32_t symbols_uncoded() const
        {
            return m_decoder->symbols_uncoded();
        }

        virtual uint32_t symbols_seen() const
        {
            return m_decoder->symbols_seen();
        }

        virtual void write_feedback(uint8_t* feedback)
        {
            kodo::write_feedback(m_decoder, feedback);
        }


    private:

        typename KodoStack::pointer m_decoder;
    };
}

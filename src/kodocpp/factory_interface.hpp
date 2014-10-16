// Copyright Steinwurf ApS 2011-2013.
// Distributed under the "STEINWURF RESEARCH LICENSE 1.0".
// See accompanying file LICENSE.rst or
// http://www.steinwurf.com/licensing

#pragma once

#include <kodo/rlnc/full_rlnc_codes.hpp>
#include <kodo/rlnc/on_the_fly_codes.hpp>

#include <kodo/rlnc/sliding_window_encoder.hpp>
#include <kodo/rlnc/sliding_window_decoder.hpp>

// Initialize the type constants
// Typdefs for the encoder/decoder type we wish to use
// also if it has trace enabled or not
typedef kodo::full_rlnc_encoder<fifi::binary> full_rlnc_encoder;
typedef kodo::full_rlnc_decoder<fifi::binary> full_rlnc_decoder;

typedef kodo::full_rlnc_encoder<fifi::binary, kodo::enable_trace>
    full_rlnc_encoder_trace;
typedef kodo::full_rlnc_decoder<fifi::binary, kodo::enable_trace>
    full_rlnc_decoder_trace;


typedef kodo::full_rlnc_encoder<fifi::binary8> full_rlnc_encoder8;
typedef kodo::full_rlnc_decoder<fifi::binary8> full_rlnc_decoder8;

typedef kodo::full_rlnc_encoder<fifi::binary8, kodo::enable_trace>
    full_rlnc_encoder_trace8;
typedef kodo::full_rlnc_decoder<fifi::binary8, kodo::enable_trace>
    full_rlnc_decoder_trace8;

typedef kodo::full_rlnc_encoder<fifi::binary16> full_rlnc_encoder16;
typedef kodo::full_rlnc_decoder<fifi::binary16> full_rlnc_decoder16;

typedef kodo::full_rlnc_encoder<fifi::binary16, kodo::enable_trace>
    full_rlnc_encoder_trace16;
typedef kodo::full_rlnc_decoder<fifi::binary16, kodo::enable_trace>
    full_rlnc_decoder_trace16;

// Typedefs for the on-the-fly coders

typedef kodo::on_the_fly_encoder<fifi::binary> on_the_fly_encoder;
typedef kodo::on_the_fly_decoder<fifi::binary> on_the_fly_decoder;

typedef kodo::on_the_fly_encoder<fifi::binary, kodo::enable_trace>
    on_the_fly_encoder_trace;
typedef kodo::on_the_fly_decoder<fifi::binary, kodo::enable_trace>
    on_the_fly_decoder_trace;


typedef kodo::on_the_fly_encoder<fifi::binary8> on_the_fly_encoder8;
typedef kodo::on_the_fly_decoder<fifi::binary8> on_the_fly_decoder8;

typedef kodo::on_the_fly_encoder<fifi::binary8, kodo::enable_trace>
    on_the_fly_encoder_trace8;
typedef kodo::on_the_fly_decoder<fifi::binary8, kodo::enable_trace>
    on_the_fly_decoder_trace8;


typedef kodo::on_the_fly_encoder<fifi::binary16> on_the_fly_encoder16;
typedef kodo::on_the_fly_decoder<fifi::binary16> on_the_fly_decoder16;

typedef kodo::on_the_fly_encoder<fifi::binary16, kodo::enable_trace>
    on_the_fly_encoder_trace16;
typedef kodo::on_the_fly_decoder<fifi::binary16, kodo::enable_trace>
    on_the_fly_decoder_trace16;


typedef kodo::sliding_window_encoder<fifi::binary> sliding_window_encoder;
typedef kodo::sliding_window_decoder<fifi::binary> sliding_window_decoder;

typedef kodo::sliding_window_encoder<fifi::binary, kodo::enable_trace>
    sliding_window_encoder_trace;
typedef kodo::sliding_window_decoder<fifi::binary, kodo::enable_trace>
    sliding_window_decoder_trace;


typedef kodo::sliding_window_encoder<fifi::binary8> sliding_window_encoder8;
typedef kodo::sliding_window_decoder<fifi::binary8> sliding_window_decoder8;

typedef kodo::sliding_window_encoder<fifi::binary8, kodo::enable_trace>
    sliding_window_encoder_trace8;
typedef kodo::sliding_window_decoder<fifi::binary8, kodo::enable_trace>
    sliding_window_decoder_trace8;

typedef kodo::sliding_window_encoder<fifi::binary16> sliding_window_encoder16;
typedef kodo::sliding_window_decoder<fifi::binary16> sliding_window_decoder16;

typedef kodo::sliding_window_encoder<fifi::binary, kodo::enable_trace>
    sliding_window_encoder_trace16;
typedef kodo::sliding_window_decoder<fifi::binary, kodo::enable_trace>
    sliding_window_decoder_trace16;

const size_t kodo_binary = typeid(fifi::binary).hash_code();
const size_t kodo_binary8 = typeid(fifi::binary8).hash_code();
const size_t kodo_binary16 = typeid(fifi::binary16).hash_code();

const size_t kodo_full_rlnc =
    typeid(full_rlnc_encoder).hash_code();

const size_t kodo_on_the_fly =
    typeid(on_the_fly_encoder).hash_code();

const size_t kodo_sliding_window =
    typeid(sliding_window_encoder).hash_code();

namespace kodo
{
    class factory_interface
    {
    public:
        virtual void* build() = 0;

        virtual void set_symbols(uint32_t symbols) = 0;
        virtual void set_symbol_size(uint32_t symbol_size) = 0;

        virtual uint32_t max_symbols() const = 0;
        virtual uint32_t max_symbol_size() const = 0;
        virtual uint32_t max_block_size() const = 0;
        virtual uint32_t max_payload_size() const = 0;

        virtual ~factory(){}
    };
}

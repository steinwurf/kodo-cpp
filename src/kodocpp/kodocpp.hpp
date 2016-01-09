// Copyright Steinwurf ApS 2011-2013.
// Distributed under the "STEINWURF RESEARCH LICENSE 1.0".
// See accompanying file LICENSE.rst or
// http://www.steinwurf.com/licensing

#pragma once

#include <kodoc/kodoc.h>

#include "encoder_factory.hpp"
#include "decoder_factory.hpp"
#include "encoder.hpp"
#include "decoder.hpp"

namespace kodocpp
{
    /// Checks whether a given codec is available in the current configuration.
    /// It is possible to enable or disable specific codecs when configuring
    /// kodo-cpp.
    /// To see the relevant options, execute "python waf --help"
    /// @param codec The codec type that should be checked
    /// @return true if the codec is available
    inline bool has_codec(int32_t codec)
    {
        return kodoc_has_codec(codec) != 0;
    }
}

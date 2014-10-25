// Copyright Steinwurf ApS 2011-2013.
// Distributed under the "STEINWURF RESEARCH LICENSE 1.0".
// See accompanying file LICENSE.rst or
// http://www.steinwurf.com/licensing

#pragma once

#if defined(_MSC_VER)
    #if defined(BUILD_KODOCPP_DLL)
        #define KODOCPP_API __declspec(dllexport)
    #else
        #define KODOCPP_API __declspec(dllimport)
    #endif
#else
    #define KODOCPP_API
#endif

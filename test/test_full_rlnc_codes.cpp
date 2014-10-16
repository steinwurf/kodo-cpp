// Copyright Steinwurf ApS 2011-2013.
// Distributed under the "STEINWURF RESEARCH LICENSE 1.0".
// See accompanying file LICENSE.rst or
// http://www.steinwurf.com/licensing

/// @file test_bindings.cpp Unit tests for the Kodo C++ bindings

void test_basic_api(uint32_t max_symbols, uint32_t max_symbol_size,
                    size_t algorithm, size_t finite_field)
{

    bool trace_enabled = false;

    //Initialize the cass and variables


    //ASSERT_TRUE to check if decoder is komplete

}

TEST(TestFullRlncCodes, invoke_api)
{
    test_basic_api(42, 160, kodo_full_rlnc, kodo_binary);
    test_basic_api(42, 160, kodo_full_rlnc, kodo_binary8);
    test_basic_api(42, 160, kodo_full_rlnc, kodo_binary16);
}

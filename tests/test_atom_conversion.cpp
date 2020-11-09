#define KXVER 3
#include "kx/k.h"
#include "markrooney/kdb.hpp"

// Need to undefine R as it causes issues with the doctest templates
#undef R

using namespace kdb;

#include "doctest/doctest.h"

TEST_CASE("roundtrip conversion should result in the equivalent object") {
    khp((S) "", -1);

    SUBCASE("integer atoms are converted between types correctly") {
        type::atom_int value = 42;
        type::atom_int result;
        convert::to_native(convert::from_native(value), result);
        CHECK_EQ(value, result);
    }

    SUBCASE("char atoms are converted between types correctly") {
        type::atom_char value = 'a';
        type::atom_char result;
        convert::to_native(convert::from_native(value), result);
        CHECK_EQ(value, result);
    }

    SUBCASE("byte atoms are converted between types correctly") {
        type::atom_byte value = 0xde;
        type::atom_byte result;
        convert::to_native(convert::from_native(value), result);
        CHECK_EQ(value, result);
    }

    SUBCASE("symbol atoms are converted between types correctly") {
        type::atom_symbol value = "example";
        type::atom_symbol result;
        convert::to_native(convert::from_native(value), result);
        CHECK_EQ(value, result);
    }

    SUBCASE("short atoms are converted between types correctly") {
        type::atom_short value = 15;
        type::atom_short result;
        convert::to_native(convert::from_native(value), result);
        CHECK_EQ(value, result);
    }

    SUBCASE("long atoms are converted between types correctly") {
        type::atom_long value = 8457374627641;
        type::atom_long result;
        convert::to_native(convert::from_native(value), result);
        CHECK_EQ(value, result);
    }

    SUBCASE("real atoms are converted between types correctly") {
        type::atom_real value = 15.2837465;
        type::atom_real result;
        convert::to_native(convert::from_native(value), result);
        CHECK_EQ(value, result);
    }

    SUBCASE("float atoms are converted between types correctly") {
        type::atom_float value = 151672245.2837465;
        type::atom_float result;
        convert::to_native(convert::from_native(value), result);
        CHECK_EQ(value, result);
    }

    SUBCASE("bool atoms are converted between types correctly") {
        type::atom_bool value = true;
        type::atom_bool result;
        convert::to_native(convert::from_native(value), result);
        CHECK_EQ(value, result);
    }
}
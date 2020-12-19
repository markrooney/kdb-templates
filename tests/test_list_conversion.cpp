#define KXVER 3
#include "k.h"
#include <markrooney/kdb.hpp>

using namespace kdb;

#include "doctest/doctest.h"

TEST_CASE("roundtrip conversion with lists should result in equivalent objects") {
    khp((S) "", -1);

    SUBCASE("list of integer atoms are converted between types correctly") {
        type::list_int value = {1, 2, 3, 4, 5};
        type::list_int result;
        convert::to_native(convert::from_native(value), result);
        CHECK_EQ(value, result);
        CHECK_EQ(value.size(), result.size());
    }

    SUBCASE("list of char atoms are converted between types correctly") {
        type::list_char value = {'a','b','c','d','e'};
        type::list_char result;
        convert::to_native(convert::from_native(value), result);
        CHECK_EQ(value, result);
        CHECK_EQ(value.size(), result.size());
    }

    SUBCASE("list of byte atoms are converted between types correctly") {
        type::list_byte value = {0xDE,0xAD,0xBE,0xEF};
        type::list_byte result;
        convert::to_native(convert::from_native(value), result);
        CHECK_EQ(value, result);
        CHECK_EQ(value.size(), result.size());
    }

    SUBCASE("list of symbol atoms are converted between types correctly") {
        type::list_symbol value = {"one","two","three"};
        type::list_symbol result;
        convert::to_native(convert::from_native(value), result);
        CHECK_EQ(value, result);
        CHECK_EQ(value.size(), result.size());
    }

    SUBCASE("list of short atoms are converted between types correctly") {
        type::list_short value = {1, 2, 3, 4, 5};
        type::list_short result;
        convert::to_native(convert::from_native(value), result);
        CHECK_EQ(value, result);
        CHECK_EQ(value.size(), result.size());
    }

    SUBCASE("list of long atoms are converted between types correctly") {
        type::list_long value = {1, 2, 3, 4, 5};
        type::list_long result;
        convert::to_native(convert::from_native(value), result);
        CHECK_EQ(value, result);
        CHECK_EQ(value.size(), result.size());
    }

    SUBCASE("list of real atoms are converted between types correctly") {
        type::list_real value = {1.1, 2.2, 3.3, 4.4, 5.5};
        type::list_real result;
        convert::to_native(convert::from_native(value), result);
        CHECK_EQ(value, result);
        CHECK_EQ(value.size(), result.size());
    }

    SUBCASE("list of float atoms are converted between types correctly") {
        type::list_float value = {1.1, 2.2, 3.3, 4.4, 5.5};
        type::list_float result;
        convert::to_native(convert::from_native(value), result);
        CHECK_EQ(value, result);
        CHECK_EQ(value.size(), result.size());
    }
}
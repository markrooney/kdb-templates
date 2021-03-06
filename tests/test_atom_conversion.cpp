/**
 *  Copyright 2020 Mark Rooney
 *
 *  Licensed under the Apache License, Version 2.0 (the "License");
 *  you may not use this file except in compliance with the License.
 *  You may obtain a copy of the License at
 *
 *      http://www.apache.org/licenses/LICENSE-2.0
 *
 *  Unless required by applicable law or agreed to in writing, software
 *  distributed under the License is distributed on an "AS IS" BASIS,
 *  WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
 *  See the License for the specific language governing permissions and
 *  limitations under the License.
 */

#define KXVER 3
#include "k.h"
#include "kdb.hpp"

using namespace kdb::convert;
using namespace kdb::type;

#include "doctest/doctest.h"

TEST_CASE("roundtrip conversion should result in the equivalent object") {
    khp((S) "", -1);

    SUBCASE("integer atoms are converted between types correctly") {
        atom_int value = 42;
        atom_int result;
        to_native(from_native(value), result);
        CHECK_EQ(value, result);
    }

    SUBCASE("char atoms are converted between types correctly") {
        atom_char value = 'a';
        atom_char result;
        to_native(from_native(value), result);
        CHECK_EQ(value, result);
    }

    SUBCASE("byte atoms are converted between types correctly") {
        atom_byte value = 0xde;
        atom_byte result;
        to_native(from_native(value), result);
        CHECK_EQ(value, result);
    }

    SUBCASE("symbol atoms are converted between types correctly") {
        atom_symbol value = "example";
        atom_symbol result;
        to_native(from_native(value), result);
        CHECK_EQ(value, result);
    }

    SUBCASE("short atoms are converted between types correctly") {
        atom_short value = 15;
        atom_short result;
        to_native(from_native(value), result);
        CHECK_EQ(value, result);
    }

    SUBCASE("long atoms are converted between types correctly") {
        atom_long value = 8457374627641;
        atom_long result;
        to_native(from_native(value), result);
        CHECK_EQ(value, result);
    }

    SUBCASE("real atoms are converted between types correctly") {
        atom_real value = 15.2837465;
        atom_real result;
        to_native(from_native(value), result);
        CHECK_EQ(value, result);
    }

    SUBCASE("float atoms are converted between types correctly") {
        atom_float value = 151672245.2837465;
        atom_float result;
        to_native(from_native(value), result);
        CHECK_EQ(value, result);
    }

    SUBCASE("bool atoms are converted between types correctly") {
        atom_bool value = true;
        atom_bool result;
        to_native(from_native(value), result);
        CHECK_EQ(value, result);
    }
}
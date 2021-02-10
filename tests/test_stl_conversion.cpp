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

#include "doctest/doctest.h"

#include <vector>
#include <deque>
#include <list>
#include <forward_list>
#include <array>
#include <set>
#include <unordered_set>
#include <map>

TEST_CASE("support std::vector round-trip conversions") {
    khp((S) "", -1);

    std::vector<int> data = {1, 2, 3, 4, 5};
    auto result = to_native<std::vector<int>>(from_native(data));

    CHECK_EQ(data, result);
}

TEST_CASE("support std::array round-trip conversions") {
    khp((S) "", -1);

    std::array<int, 5> data = {1, 2, 3, 4, 5};
    auto result = to_native<std::array<int,5>>(from_native(data));

    CHECK_EQ(data, result);
}

TEST_CASE("support std::deque round-trip conversions") {
    khp((S) "", -1);

    std::deque<int> data = {1, 2, 3, 4, 5};
    auto result = to_native<std::deque<int>>(from_native(data));

    CHECK_EQ(data, result);
}

TEST_CASE("support std::unordered_map round-trip conversions") {
    khp((S) "", -1);

    std::unordered_map<std::string, double> data { {"one", 1.2}, {"two", 2.3}, {"three", 3.4} };
    auto result = to_native<std::unordered_map<std::string, double>>(from_native(data));
    CHECK_EQ(data, result);
}

/**
 * Commented out for now as std::map requires an encoding/decoding implementation 'kdb::custom_type_impl<std::map<std::__cxx11::basic_string<char>, int, std::less<std::__cxx11::basic_string<char>>, std::allocator<std::pair<const std::__cxx11::basic_string<char>, int>>>>'
 *
TEST_CASE("support std::map round-trip conversions") {
    khp((S) "", -1);

    std::map<std::string, int> data { {"one", 1}, {"two", 2}, {"three", 3} };
    auto result = to_native<std::map<std::string, int>>(from_native(data));

    CHECK_EQ(data, result);
}
*/

/**
 * Commented out for now as std::multiset requires an encoding/decoding implementation 'kdb::custom_type_impl<std::multiset<int, std::less<int>, std::allocator<int>>>'
 *
TEST_CASE("support std::multiset round-trip conversions") {
    khp((S) "", -1);

    std::multiset<int> data = {1, 2, 3, 4, 5};
    auto result = to_native<std::multiset<int>>(from_native(data));

    CHECK_EQ(data, result);
}
*/

/**
 * Commented out for now as std::unordered_multiset requires an encoding/decoding implementation 'kdb::custom_type_impl<std::unordered_multiset<int, std::hash<int>, std::equal_to<int>, std::allocator<int>>>'
 *
TEST_CASE("support std::unordered_multiset round-trip conversions") {
    khp((S) "", -1);

    std::unordered_multiset<int> data = {1, 2, 3, 4, 5};
    auto result = to_native<std::unordered_multiset<int>>(from_native(data));

    CHECK_EQ(data, result);
}
*/

/**
 * Commented out for now as std::unordered_set requires an encoding/decoding implementation 'kdb::custom_type_impl<std::unordered_set<int, std::hash<int>, std::equal_to<int>, std::allocator<int>>>'
 *
TEST_CASE("support std::unordered_set round-trip conversions") {
    khp((S) "", -1);

    std::unordered_set<int> data = {1, 2, 3, 4, 5};
    auto result = to_native<std::unordered_set<int>>(from_native(data));

    CHECK_EQ(data, result);
}
*/

/**
 * Commented out for now as std::set requires an encoding/decoding implementation kdb::custom_type_impl<std::set<int, std::less<int>, std::allocator<int>>>
 *
TEST_CASE("support std::set round-trip conversions") {
    khp((S) "", -1);

    std::set<int> data = {1, 2, 3, 4, 5};
    auto result = to_native<std::set<int>>(from_native(data));

    CHECK_EQ(data, result);
}
*/

/**
 * Commented out for now as std::list requires an encoding/decoding implementation that doesn't use the subscript operator.
 *
TEST_CASE("support std::list round-trip conversions") {
    khp((S) "", -1);

    std::list<int> data = {1, 2, 3, 4, 5};
    auto result = to_native<std::list<int>>(from_native(data));
}
*/

/**
 * Commented out for now as std::forward_list requires an encoding/decoding implementation that doesn't use the subscript operator.
 *
TEST_CASE("support std::forward_list round-trip conversions") {
    khp((S) "", -1);

    std::forward_list<int> data = {1, 2, 3, 4, 5};
    auto result = to_native<std::forward_list<int>>(from_native(data));
}
*/
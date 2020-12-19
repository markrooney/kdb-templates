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

#ifndef _MARKROONEY_DETAIL_TYPES_H
#define _MARKROONEY_DETAIL_TYPES_H

#include <variant>       // for std::variant used by kdb::type::any
#include <vector>        // for std::vector used by kdb::type::list
#include <string>        // for std::string used by kdb::type::symbol
#include <unordered_map> // for std::unordered map used by kdb::type::dict
#include <memory>        // for std::unique_ptr in recursive variant types

/*!
@brief namespace for the KDB type conversion library
@since version 1.0.0
*/
namespace kdb::type {

    /*!
     * @brief alias to the native datatype used to represent a single KDB boolean
     * @since version 1.0.0
     */
    using atom_bool = bool;

    /*!
     * @brief alias to the native datatype used to represent a single KDB byte
     * @since version 1.0.0
     */
    using atom_byte = G;

    /*!
     * @brief alias to the native datatype used to represent a single KDB short
     * @since version 1.0.0
     */
    using atom_short = H;

    /*!
     * @brief alias to the native datatype used to represent a single KDB int
     * @since version 1.0.0
     */
    using atom_int = I;

    /*!
     * @brief alias to the native datatype used to represent a single KDB long
     * @since version 1.0.0
     */
    using atom_long = J;

    /*!
     * @brief alias to the native datatype used to represent a single KDB real
     * @since version 1.0.0
     */
    using atom_real = E;

    /*!
     * @brief alias to the native datatype used to represent a single KDB float
     * @since version 1.0.0
     */
    using atom_float = F;

    /*!
     * @brief alias to the native datatype used to represent a single KDB char
     * @since version 1.0.0
     */
    using atom_char = C;

    /*!
     * @brief alias to the native datatype used to represent a single KDB symbol
     * @since version 1.0.0
     */
    using atom_symbol = std::string;

    /*!
     * @brief a variant type representing any single KDB atom. You should use std::
     * @since version 1.0.0
     */
    using atom_any = std::variant<atom_bool, atom_byte, atom_short, atom_int, atom_long , atom_real, atom_float, atom_char, atom_symbol>;

    constexpr inline atom_bool is_bool(const atom_any& any) {
        return std::holds_alternative<atom_bool>(any);
    }

    inline atom_bool as_bool(const atom_any& any) {
        return std::get<atom_bool>(any);
    }

    constexpr inline atom_byte is_byte(const atom_any& any) {
        return std::holds_alternative<atom_byte>(any);
    }

    inline atom_byte as_byte(const atom_any& any) {
        return std::get<atom_byte>(any);
    }

    constexpr inline bool is_short(const atom_any& any) {
        return std::holds_alternative<atom_short>(any);
    }

    inline atom_short as_short(const atom_any& any) {
        return std::get<atom_short>(any);
    }

    constexpr inline bool is_int(const atom_any& any) {
        return std::holds_alternative<atom_int>(any);
    }

    inline atom_int as_int(const atom_any& any) {
        return std::get<atom_int>(any);
    }

    constexpr inline bool is_long(const atom_any& any) {
        return std::holds_alternative<atom_long>(any);
    }

    inline atom_long as_long(const atom_any& any) {
        return std::get<atom_long>(any);
    }

    constexpr inline bool is_real(const atom_any& any) {
        return std::holds_alternative<atom_real>(any);
    }

    inline atom_real as_real(const atom_any& any) {
        return std::get<atom_real>(any);
    }

    constexpr inline bool is_float(const atom_any& any) {
        return std::holds_alternative<atom_float>(any);
    }

    inline atom_float as_float(const atom_any& any) {
        return std::get<atom_float>(any);
    }

    constexpr inline bool is_char(const atom_any& any) {
        return std::holds_alternative<atom_char>(any);
    }

    inline atom_char as_char(const atom_any& any) {
        return std::get<atom_char>(any);
    }

    constexpr inline bool is_symbol(const atom_any& any) {
        return std::holds_alternative<atom_symbol>(any);
    }

    inline atom_symbol as_symbol(const atom_any& any) {
        return std::get<atom_symbol>(any);
    }

    constexpr inline bool is_integral(const atom_any& any) {
        return is_int(any) or is_long(any) or is_short(any) or is_bool(any);
    }

    constexpr inline bool is_floating(const atom_any& any) {
        return is_float(any) or is_real(any);
    }

    constexpr inline bool is_numerical(const atom_any& any) {
        return is_integral(any) or is_floating(any);
    }

    /*!
     * @since version 1.0.0
     */
    template<typename T>
    using list = std::vector<T>;

    /*!
     * @since version 1.0.0
     */
    using list_bool = list<atom_bool>;

    /*!
     * @since version 1.0.0
     */
    using list_byte = list<atom_byte>;

    /*!
     * @since version 1.0.0
     */
    using list_short = list<atom_short>;

    /*!
     * @since version 1.0.0
     */
    using list_int = list<atom_int>;

    /*!
     * @since version 1.0.0
     */
    using list_long = list<atom_long>;

    /*!
     * @since version 1.0.0
     */
    using list_real = list<atom_real>;

    /*!
     * @brief a list of floats stored efficiently as a contiguous vector
     * @since version 1.0.0
     */
    using list_float = list<atom_float>;

    /*!
     * @since version 1.0.0
     */
    using list_char = list<atom_char>;

    /*!
     * A type representing a list of KDB symbols
     *
     * @example represented in kdb as: `abc`def`hij`kdb
     * @since version 1.0.0
     */
    using list_symbol = list<atom_symbol>;

    /*!
     * @since version 1.0.0
     */
    using list_mixed = list<atom_any>;

    struct list_wrapper;

    using nested_list = std::vector<list_wrapper>;
    using any_list = std::variant<list_bool, list_real, list_float, list_byte, list_char, list_int, list_short, list_long, list_symbol, list_mixed, nested_list>;

    struct list_wrapper
    {
        template <typename... Ts>
        list_wrapper(Ts&&... items) : value{std::forward<Ts>(items)...} {}
        any_list value{};
    };

    template<typename T1, typename T2>
    using dict = std::unordered_map<T1,T2>;

    using table = dict<atom_symbol, any_list>;

    using keyed_table = dict<table, table>;
}

#endif
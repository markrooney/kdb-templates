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

#ifndef _MARKROONEY_KDB_H
#define _MARKROONEY_KDB_H

#if ((__cplusplus < 201703L))
#error "this header file requires C++17 features. please use a compatible compiler and flags"
#endif

#ifndef KXVER
#error "please include 'k.h' and set KXVER before including this header file"
#endif

#include <array>  // for std::array
#include <cstddef>// for std::size_t
#include <cstring>// for std::memcpy
#include <variant>// for std::variant
#include <vector> // for std::vector

#include "detail/exceptions.hpp"
#include "detail/macro_expansion.hpp"
#include "detail/types.hpp"

/*!
@brief namespace for the KDB type conversion library
@since version 1.0.0
*/
namespace kdb {

    template<typename T>
    struct custom_type_impl;

#define CREATE_ATOM_TYPE(_mac_nat, _mac_tag, _mac_lst, _mac_nul, _mac_cons, _mac_acc)       \
    template<>                                                                              \
    struct custom_type_impl<_mac_nat> {                                                     \
        constexpr static const int tag = (_mac_tag);                                        \
        static inline void set_list(K obj, int idx, _mac_nat x) { _mac_lst(obj)[idx] = x; } \
        static inline _mac_nat get_list(K obj, int idx) { return _mac_lst(obj)[idx]; }      \
        static inline K encode(_mac_nat x) noexcept { return _mac_cons(x); }                \
        constexpr static inline _mac_nat access(K obj) noexcept { return obj->_mac_acc; }   \
        constexpr static inline bool decode(K obj, _mac_nat &result) noexcept {             \
            if (obj->t != -(_mac_tag)) { return false; }                                    \
            result = access(obj);                                                           \
            return true;                                                                    \
        }                                                                                   \
    };

    CREATE_ATOM_TYPE(type::atom_byte, KG, kG, ng, kg, g)
    CREATE_ATOM_TYPE(type::atom_char, KC, kC, ' ', kc, g)
    CREATE_ATOM_TYPE(type::atom_bool, KB, kC, false, kb, g)
    CREATE_ATOM_TYPE(type::atom_short, KH, kH, nh, kh, h)
    CREATE_ATOM_TYPE(type::atom_int, KI, kI, ni, ki, i)
    CREATE_ATOM_TYPE(type::atom_long, KJ, kJ, nj, kj, j)
    CREATE_ATOM_TYPE(type::atom_real, KE, kE, ne, ke, e)
    CREATE_ATOM_TYPE(type::atom_float, KF, kF, nf, kf, f)

    template<>
    struct custom_type_impl<type::atom_symbol> {
        static const int tag = KS;
        static inline K encode(const type::atom_symbol &x) noexcept { return ks(ss((S) x.c_str())); }
        static inline void set_list(K obj, int idx, const type::atom_symbol &x) { kS(obj)[idx] = ss((S) x.c_str()); }
        static inline type::atom_symbol get_list(K obj, int idx) { return type::atom_symbol{kS(obj)[idx]}; }
        static inline type::atom_symbol access(K obj) noexcept { return type::atom_symbol{obj->s}; }
        static inline bool decode(K obj, type::atom_symbol &result) noexcept {
            if (obj->t != -tag) {
                return false;
            }
            result = access(obj);
            return true;
        }
    };

    template<template<typename, typename> class C, typename T, typename A>
    struct custom_type_impl<C<T, A>> {
        static const int tag = 0;
        static inline void set_list(K obj, int idx, const C<T, A> &x) {
            kK(obj)[idx] = custom_type_impl<C<T, A>>::encode(x);
        }

        static inline C<T, A> get_list(K obj, int idx) {
            C<T, A> res;
            custom_type_impl<C<T, A>>::decode(kK(obj)[idx], res);
            return res;
        }

        constexpr static auto encode(const C<T, A> &x) noexcept {
            auto res = ktn(custom_type_impl<T>::tag, x.size());
            // Changing the variable here from size_t -> int makes a performance difference!. The int version is inlined with SSE instructions.
            for (auto i = 0; i < x.size(); i++)
                custom_type_impl<T>::set_list(res, i, x[i]);
            return res;
        }

        constexpr static bool decode(K obj, C<T, A> &result) noexcept {
            if (obj->t != custom_type_impl<T>::tag) {
                return false;
            }

            J size = obj->n;
            C<T, A> temp(size);
            for (J i = 0; i < size; i++) {
                temp[i] = custom_type_impl<T>::get_list(obj, i);
            }

            result = std::move(temp);
            return true;
        }
    };

    template<template<typename, size_t> class C, typename T, size_t N>
    struct custom_type_impl<C<T, N>> {
        static inline K encode(const C<T, N> &x) noexcept {
            size_t size = N;
            K res = ktn(custom_type_impl<T>::tag, size);
            for (int i = 0; i < size; i++)
                custom_type_impl<T>::set_list(res, i, x[i]);
            return res;
        }

        static inline bool decode(K x, C<T, N> &result) noexcept {
            if (x->t != custom_type_impl<T>::tag) {
                return false;
            }

            J size = x->n;
            C<T, N> temp;
            for (J i = 0; i < size; i++) {
                temp[i] = custom_type_impl<T>::get_list(x, i);
            }

            result = std::move(temp);

            return true;
        }
    };

    // --------------------------------------------------------------------------------
    // ------------------------- Variant K Object Support -----------------------------
    // --------------------------------------------------------------------------------
    template<>
    struct custom_type_impl<kdb::type::atom_any> {
        static const int tag = 0;

        static inline K encode(const kdb::type::atom_any &x) noexcept {
            return std::visit([](auto arg) { return custom_type_impl<decltype(arg)>::encode(arg); }, x);
        }

        static inline void set_list(K obj, int idx, const type::atom_any &x) {
            kK(obj)[idx] = encode(x);
        }

        static inline type::atom_any get_list(K obj, int idx) {
            type::atom_any res;
            decode(kK(obj)[idx], res);
            return res;
        }

        static inline bool decode(K x, type::atom_any &result) noexcept {
            if (xt >= 0) {
                return false;
            }

            switch (xt) {
                CS(-custom_type_impl<type::atom_byte>::tag, result = custom_type_impl<type::atom_byte>::access(x))
                CS(-custom_type_impl<type::atom_bool>::tag, result = custom_type_impl<type::atom_bool>::access(x))
                CS(-custom_type_impl<type::atom_short>::tag, result = custom_type_impl<type::atom_short>::access(x))
                CS(-custom_type_impl<type::atom_int>::tag, result = custom_type_impl<type::atom_int>::access(x))
                CS(-custom_type_impl<type::atom_long>::tag, result = custom_type_impl<type::atom_long>::access(x))
                CS(-custom_type_impl<type::atom_real>::tag, result = custom_type_impl<type::atom_real>::access(x))
                CS(-custom_type_impl<type::atom_float>::tag, result = custom_type_impl<type::atom_float>::access(x))
                CS(-custom_type_impl<type::atom_char>::tag, result = custom_type_impl<type::atom_char>::access(x))
                CS(-custom_type_impl<type::atom_symbol>::tag, result = custom_type_impl<type::atom_symbol>::access(x))
                default:
                    return false;
            }

            return true;
        }
    };

    static bool contains_lists(K x) {
        if (xt != 0)
            return false;

        for (int i = 0; i < x->n; i++)
            if ((kK(x)[i]->t) >= 0)
                return true;

        return false;
    }

    static K any_list_encoder(const kdb::type::any_list &x);
    static kdb::type::any_list any_list_decoder(K x);

    template<>
    struct custom_type_impl<type::nested_list> {
        static const int tag = 0;

        static inline K encode(const kdb::type::nested_list &x) noexcept {
            K list = ktn(0, 0);
            for (const auto &sub_list : x) {
                jk(&list, any_list_encoder(sub_list.value));
            }
            return list;
        }

        static inline bool decode(K x, type::nested_list &result) noexcept {
            for (int i = 0; i < xn; i++) {
                result.push_back(any_list_decoder(kK(x)[i]));
            }
            return true;
        }
    };

    static K any_list_encoder(const kdb::type::any_list &x) {
        return std::visit([](auto arg) { return custom_type_impl<decltype(arg)>::encode(arg); }, x);
    }

    static kdb::type::any_list any_list_decoder(K x) {
        type::list_mixed a;
        type::list_byte b;
        type::list_bool c;
        type::list_short d;
        type::list_int e;
        type::list_long f;
        type::list_real g;
        type::list_float h;
        type::list_char i;
        type::list_symbol j;
        type::nested_list n;

        switch (xt) {
            CS(
                    0,
                    if (contains_lists(x)) {
                        custom_type_impl<type::nested_list>::decode(x, n);
                        return n;
                    } else {
                        custom_type_impl<type::list_mixed>::decode(x, a);
                        return a;
                    })
            CS(custom_type_impl<type::atom_byte>::tag, custom_type_impl<type::list_byte>::decode(x, b); return b;)
            CS(custom_type_impl<type::atom_bool>::tag, custom_type_impl<type::list_bool>::decode(x, c); return c;)
            CS(custom_type_impl<type::atom_short>::tag, custom_type_impl<type::list_short>::decode(x, d); return d;)
            CS(custom_type_impl<type::atom_int>::tag, custom_type_impl<type::list_int>::decode(x, e); return e;)
            CS(custom_type_impl<type::atom_long>::tag, custom_type_impl<type::list_long>::decode(x, f); return f;)
            CS(custom_type_impl<type::atom_real>::tag, custom_type_impl<type::list_real>::decode(x, g); return g;)
            CS(custom_type_impl<type::atom_float>::tag, custom_type_impl<type::list_float>::decode(x, h); return h;)
            CS(custom_type_impl<type::atom_char>::tag, custom_type_impl<type::list_char>::decode(x, i); return i;)
            CS(custom_type_impl<type::atom_symbol>::tag, custom_type_impl<type::list_symbol>::decode(x, j); return j;)
            default:
                return kdb::type::list_mixed{};
        }
    }

    // TODO :: implement custom_type_impl<list_any> so that this example will compile
    template<>
    struct custom_type_impl<kdb::type::any_list> {
        static const int tag = 0;

        static inline K encode(const kdb::type::any_list &x) noexcept {
            return any_list_encoder(x);
        }

        static inline void set_list(K obj, int idx, const type::any_list &x) {
            kK(obj)[idx] = encode(x);
        }

        static inline type::any_list get_list(K obj, int idx) {
            type::any_list res;
            decode(kK(obj)[idx], res);
            return res;
        }

        static inline bool decode(K x, type::any_list &result) noexcept {
            if ((xt < 0) or (xt > 20))
                return false;
            result = any_list_decoder(x);
            return true;
        }
    };

    // Handles the c++ standard map data types
    template<
            template<typename, typename, typename, typename, typename> class C, typename KeyType, typename ValType, typename Hash, typename Equal, typename Alloc>
    struct custom_type_impl<C<KeyType, ValType, Hash, Equal, Alloc>> {
        static const int tag = XD;

        static inline void set_list(K obj, int idx, const C<KeyType, ValType, Hash, Equal, Alloc> &x) {
            kK(obj)[idx] = custom_type_impl<C<KeyType, ValType, Hash, Equal, Alloc>>::encode(x);
        }

        static inline C<KeyType, ValType, Hash, Equal, Alloc> get_list(K obj, int idx) {
            C<KeyType, ValType, Hash, Equal, Alloc> res;
            custom_type_impl<C<KeyType, ValType, Hash, Equal, Alloc>>::decode(kK(obj)[idx], res);
            return res;
        }

        static inline K encode(const C<KeyType, ValType, Hash, Equal, Alloc> &x) noexcept {
            size_t size = x.size();
            K keys = ktn(custom_type_impl<KeyType>::tag, size);
            K values = ktn(custom_type_impl<ValType>::tag, size);

            int i = 0;
            for (const auto &pair : x) {
                custom_type_impl<KeyType>::set_list(keys, i, pair.first);
                custom_type_impl<ValType>::set_list(values, i, pair.second);
                i++;
            }

            return xD(keys, values);
        }

        static inline bool decode(K x, C<KeyType, ValType, Hash, Equal, Alloc> &result) noexcept {
            if (xt != tag) {
                return false;
            }

            K keys = xx;
            K values = xy;

            if ((keys->t != custom_type_impl<KeyType>::tag) or (values->t != custom_type_impl<ValType>::tag)) {
                return false;
            }

            std::vector<KeyType> native_keys;
            custom_type_impl<std::vector<KeyType>>::decode(keys, native_keys);

            std::vector<ValType> native_values;
            custom_type_impl<std::vector<ValType>>::decode(values, native_values);

            C<KeyType, ValType, Hash, Equal, Alloc> temp{};

            for (std::size_t i = 0; i < native_keys.size(); ++i)
                temp[native_keys[i]] = native_values[i];

            result = std::move(temp);
            return true;
        }
    };

    namespace convert {
        template<size_t N>
        void to_byte_buffer(K obj, const std::array<char, N> &target) {
            K buffer = b9(3, obj);

            if ((sizeof(buffer->n) + buffer->n) > N) {
                throw std::runtime_error("buffer to small to write to");
            }

            std::memcpy((void *) target.data(), &buffer->n, sizeof(buffer->n));
            std::memcpy((void *) (target.data() + sizeof(buffer->n)), kG(buffer), buffer->n);
        }

        template<typename T, size_t N>
        void to_byte_buffer(const T &data, const std::array<char, N> &target) {
            K obj = custom_type_impl<T>::encode(data);
            to_byte_buffer(obj, target);
        }

        template<size_t N>
        void from_byte_buffer(const std::array<char, N> &target, K &obj) {
            J size = *((J *) target.data());
            K bytes = ktn(KG, size);
            std::memmove(kG(bytes), target.data() + sizeof(J), size);

            if (!okx(bytes)) {
                throw std::runtime_error("invalid bytes for deserializing");
            }

            K temp = d9(bytes);
            r0(bytes);
            obj = temp;
        }

        template<typename T, size_t N>
        void from_byte_buffer(const std::array<char, N> &target, T &data) {
            K temp;
            from_byte_buffer(target, temp);
            if (!custom_type_impl<T>::decode(temp, data)) {
                throw kdb::exception::invalid_conversion("couldn't convert to native type");
            }
        }

        template<typename T>
        void to_native(K obj, T &result) {
            if (!custom_type_impl<T>::decode(obj, result))
                throw kdb::exception::invalid_conversion("invalid conversion");
        }

        template<typename T>
        void to_native_or_die(K obj, T &result) {
            if (!custom_type_impl<T>::decode(obj, result))
                std::abort();
        }

        template<typename T>
        inline bool to_native_unsafe(K obj, T &result) noexcept {
            return custom_type_impl<T>::decode(obj, result);
        }

        template<typename T>
        inline T to_native(K obj) {
            T result;
            if (!custom_type_impl<T>::decode(obj, result))
                throw kdb::exception::invalid_conversion("invalid conversion");
            return result;
        }

        template<typename T>
        inline T to_native_unsafe(K obj) noexcept {
            T result;
            custom_type_impl<T>::decode(obj, result);
            return result;
        }

        template<typename T>
        inline K from_native(const T &data) noexcept {
            return custom_type_impl<T>::encode(data);
        }
    }// namespace convert

    namespace impl {// anonymous namespace - no outside access

        template<typename T, typename M,
                 typename std::enable_if<std::is_member_object_pointer<M>::value, M>::type * = nullptr>
        constexpr inline void pack(K &x, const T &t, int index, M m) { kK(x)[index] = kdb::convert::from_native(t.*m); }

        template<typename T, typename M, typename... Ms,
                 typename std::enable_if<std::is_member_object_pointer<M>::value, M>::type * = nullptr>
        constexpr inline void pack(K &x, const T &t, int index, M m, Ms... ms) {
            kK(x)[index] = kdb::convert::from_native(t.*m);
            pack(x, t, index + 1, ms...);
        }

        template<typename T, typename... Ms>
        constexpr inline K pack(const T &t, Ms... ms) {
            K list = ktn(0, sizeof...(ms));
            pack(list, t, 0, ms...);
            return list;
        }

        template<typename T, typename M, typename... Ms,
                 typename std::enable_if<std::is_member_object_pointer<M>::value, M>::type * = nullptr>
        constexpr inline void pack_dict(K &x, const T &t, int index, const char *n, M m) {
            n = "test";
            kK(x)[index] = kdb::convert::from_native(t.*m);
        }

        template<typename T, typename M, typename... Ms,
                 typename std::enable_if<std::is_member_object_pointer<M>::value, M>::type * = nullptr>
        constexpr inline void pack_dict(K &x, const T &t, int index, const char *n, M m, Ms... ms) {
            n = "test";
            kK(x)[index] = kdb::convert::from_native(t.*m);
            pack_dict(x, t, index + 1, ms...);
        }

        template<typename T, typename... Ms>
        constexpr inline K pack_dict(const T &t, Ms... ms) {
            K list = ktn(0, sizeof...(ms));
            pack_dict(list, t, 0, ms...);
            return list;
        }

        template<typename T, typename M,
                 typename std::enable_if<std::is_member_object_pointer<M>::value, M>::type * = nullptr>
        constexpr void unpack(K &x, T &t, int i, M m) {
            kdb::convert::to_native(kK(x)[i], t.*m);
        }

        template<typename T, typename M, typename... Ms,
                 typename std::enable_if<std::is_member_object_pointer<M>::value, M>::type * = nullptr>
        constexpr void unpack(K &obj, T &t, int i, M m, Ms... ms) {
            kdb::convert::to_native(kK(obj)[i], t.*m);
            unpack(obj, t, i + 1, ms...);
        }

        /**
 * Requirements for being able to unpack a data structure:
 * - The type to be unpacked has to be default constructable (have a public constructor with no args)
 * - The type (and all dependant types) need to be supported via kdb::convert::to_native.
 */
        template<typename T, typename... Ms>
        constexpr T unpack(K &x, Ms... ms) {
            T res{};
            unpack(x, res, 0, ms...);
            return res;
        }
    }// namespace impl
}// namespace kdb

#define KDB_REGISTER_FIELDS(TypeName, ...)                                                                            \
    namespace kdb {                                                                                                   \
        template<>                                                                                                    \
        struct custom_type_impl<TypeName> {                                                                           \
            static const int tag = 0;                                                                                 \
            static inline K encode(const TypeName &x) noexcept { return std::move(kdb::impl::pack(x, __VA_ARGS__)); } \
            static inline bool decode(K x, TypeName &result) noexcept {                                               \
                if (x->t != tag) return false;                                                                        \
                result = kdb::impl::unpack<TypeName>(x, __VA_ARGS__);                                                 \
                return true;                                                                                          \
            }                                                                                                         \
        };                                                                                                            \
    }

#define TYPE_MEMBER_FN(Type, Member) &Type::Member

#define KDB_REGISTER(TypeName, ...)                                                                                                                                        \
    namespace kdb {                                                                                                                                                        \
        template<>                                                                                                                                                         \
        struct custom_type_impl<TypeName> {                                                                                                                                \
            static const int tag = 0;                                                                                                                                      \
            static inline K encode(const TypeName &x) noexcept { return std::move(kdb::impl::pack(x, PASTE_EXPAND(PASTE_MACRO(TYPE_MEMBER_FN, TypeName, __VA_ARGS__)))); } \
            static inline bool decode(K x, TypeName &result) noexcept {                                                                                                    \
                if (x->t != tag) return false;                                                                                                                             \
                result = kdb::impl::unpack<TypeName>(x, PASTE_EXPAND(PASTE_MACRO(TYPE_MEMBER_FN, TypeName, __VA_ARGS__)));                                                 \
                return true;                                                                                                                                               \
            }                                                                                                                                                              \
        };                                                                                                                                                                 \
    }

#define KDB_REGISTER_DICT_TYPE(TypeName, ...)                                                                              \
    namespace kdb {                                                                                                        \
        template<>                                                                                                         \
        struct custom_type_impl<TypeName> {                                                                                \
            static const int tag = 0;                                                                                      \
            static inline K encode(const TypeName &x) noexcept { return std::move(kdb::impl::pack_dict(x, __VA_ARGS__)); } \
            static inline bool decode(K x, TypeName &result) noexcept {                                                    \
                return true;                                                                                               \
            }                                                                                                              \
        };                                                                                                                 \
    }

// remove any Kx macros that will cause problems for people using C++ templates. These macros can be enabled by defining
// USE_KX_MACROS before loading this header file.
#include "detail/remove_macros.hpp"

#endif
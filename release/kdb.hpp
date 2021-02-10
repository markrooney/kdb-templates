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

// #include "detail/exceptions.hpp"
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

#ifndef _MARKROONEY_DETAIL_EXCEPTIONS_H
#define _MARKROONEY_DETAIL_EXCEPTIONS_H

#include <exception>
#include <stdexcept>
#include <string>

namespace kdb::exception {

    class invalid_conversion : public std::runtime_error {
    public:
        explicit invalid_conversion(const std::string& msg) : std::runtime_error(msg) { }
    };
}

#endif
// #include "detail/macro_expansion.hpp"
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

#ifndef EXAMPLE_MACRO_EXPANSION_HPP
#define EXAMPLE_MACRO_EXPANSION_HPP

// This macro expansion has been taken from https://github.com/nlohmann/json/blob/develop/single_include/nlohmann/json.hpp and expanded to support two arg macros.
// Allows us to apply a macro/function to each variadic macro argument and is useful for constructing custom types.
#define PASTE_EXPAND( x ) x
#define PASTE_GET_MACRO(_1, _2, _3, _4, _5, _6, _7, _8, _9, _10, _11, _12, _13, _14, _15, _16, _17, _18, _19, _20, _21, _22, _23, _24, _25, _26, _27, _28, _29, _30, _31, _32, _33, _34, _35, _36, _37, _38, _39, _40, _41, _42, _43, _44, _45, _46, _47, _48, _49, _50, _51, _52, _53, _54, _55, _56, _57, _58, _59, _60, _61, _62, _63, _64, NAME,...) NAME
#define PASTE_MACRO(...) PASTE_EXPAND(PASTE_GET_MACRO(__VA_ARGS__, \
        PASTE_MACRO64, \
        PASTE_MACRO63, \
        PASTE_MACRO62, \
        PASTE_MACRO61, \
        PASTE_MACRO60, \
        PASTE_MACRO59, \
        PASTE_MACRO58, \
        PASTE_MACRO57, \
        PASTE_MACRO56, \
        PASTE_MACRO55, \
        PASTE_MACRO54, \
        PASTE_MACRO53, \
        PASTE_MACRO52, \
        PASTE_MACRO51, \
        PASTE_MACRO50, \
        PASTE_MACRO49, \
        PASTE_MACRO48, \
        PASTE_MACRO47, \
        PASTE_MACRO46, \
        PASTE_MACRO45, \
        PASTE_MACRO44, \
        PASTE_MACRO43, \
        PASTE_MACRO42, \
        PASTE_MACRO41, \
        PASTE_MACRO40, \
        PASTE_MACRO39, \
        PASTE_MACRO38, \
        PASTE_MACRO37, \
        PASTE_MACRO36, \
        PASTE_MACRO35, \
        PASTE_MACRO34, \
        PASTE_MACRO33, \
        PASTE_MACRO32, \
        PASTE_MACRO31, \
        PASTE_MACRO30, \
        PASTE_MACRO29, \
        PASTE_MACRO28, \
        PASTE_MACRO27, \
        PASTE_MACRO26, \
        PASTE_MACRO25, \
        PASTE_MACRO24, \
        PASTE_MACRO23, \
        PASTE_MACRO22, \
        PASTE_MACRO21, \
        PASTE_MACRO20, \
        PASTE_MACRO19, \
        PASTE_MACRO18, \
        PASTE_MACRO17, \
        PASTE_MACRO16, \
        PASTE_MACRO15, \
        PASTE_MACRO14, \
        PASTE_MACRO13, \
        PASTE_MACRO12, \
        PASTE_MACRO11, \
        PASTE_MACRO10, \
        PASTE_MACRO9, \
        PASTE_MACRO8, \
        PASTE_MACRO7, \
        PASTE_MACRO6, \
        PASTE_MACRO5, \
        PASTE_MACRO4, \
        PASTE_MACRO3)(__VA_ARGS__))

#define PASTE_MACRO3(func, v1, v2) func(v1, v2)
#define PASTE_MACRO4(func, v1, v2, v3) PASTE_MACRO3(func, v1, v2), PASTE_MACRO3(func, v1, v3)
#define PASTE_MACRO5(func, v1, v2, v3, v4) PASTE_MACRO3(func, v1, v2), PASTE_MACRO4(func, v1, v3, v4)
#define PASTE_MACRO6(func, v1, v2, v3, v4, v5) PASTE_MACRO3(func, v1, v2), PASTE_MACRO5(func, v1, v3, v4, v5)
#define PASTE_MACRO7(func, v1, v2, v3, v4, v5, v6) PASTE_MACRO3(func, v1, v2), PASTE_MACRO6(func, v1, v3, v4, v5, v6)
#define PASTE_MACRO8(func, v1, v2, v3, v4, v5, v6, v7) PASTE_MACRO3(func, v1, v2), PASTE_MACRO7(func, v1, v3, v4, v5, v6, v7)
#define PASTE_MACRO9(func, v1, v2, v3, v4, v5, v6, v7, v8) PASTE_MACRO3(func, v1, v2), PASTE_MACRO8(func, v1, v3, v4, v5, v6, v7, v8)
#define PASTE_MACRO10(func, v1, v2, v3, v4, v5, v6, v7, v8, v9) PASTE_MACRO3(func, v1, v2), PASTE_MACRO9(func, v1, v3, v4, v5, v6, v7, v8, v9)
#define PASTE_MACRO11(func, v1, v2, v3, v4, v5, v6, v7, v8, v9, v10) PASTE_MACRO3(func, v1, v2), PASTE_MACRO10(func, v1, v3, v4, v5, v6, v7, v8, v9, v10)
#define PASTE_MACRO12(func, v1, v2, v3, v4, v5, v6, v7, v8, v9, v10, v11) PASTE_MACRO3(func, v1, v2), PASTE_MACRO11(func, v1, v3, v4, v5, v6, v7, v8, v9, v10, v11)
#define PASTE_MACRO13(func, v1, v2, v3, v4, v5, v6, v7, v8, v9, v10, v11, v12) PASTE_MACRO3(func, v1, v2), PASTE_MACRO12(func, v1, v3, v4, v5, v6, v7, v8, v9, v10, v11, v12)
#define PASTE_MACRO14(func, v1, v2, v3, v4, v5, v6, v7, v8, v9, v10, v11, v12, v13) PASTE_MACRO3(func, v1, v2), PASTE_MACRO13(func, v1, v3, v4, v5, v6, v7, v8, v9, v10, v11, v12, v13)
#define PASTE_MACRO15(func, v1, v2, v3, v4, v5, v6, v7, v8, v9, v10, v11, v12, v13, v14) PASTE_MACRO3(func, v1, v2), PASTE_MACRO14(func, v1, v3, v4, v5, v6, v7, v8, v9, v10, v11, v12, v13, v14)
#define PASTE_MACRO16(func, v1, v2, v3, v4, v5, v6, v7, v8, v9, v10, v11, v12, v13, v14, v15) PASTE_MACRO3(func, v1, v2), PASTE_MACRO15(func, v1, v3, v4, v5, v6, v7, v8, v9, v10, v11, v12, v13, v14, v15)
#define PASTE_MACRO17(func, v1, v2, v3, v4, v5, v6, v7, v8, v9, v10, v11, v12, v13, v14, v15, v16) PASTE_MACRO3(func, v1, v2), PASTE_MACRO16(func, v1, v3, v4, v5, v6, v7, v8, v9, v10, v11, v12, v13, v14, v15, v16)
#define PASTE_MACRO18(func, v1, v2, v3, v4, v5, v6, v7, v8, v9, v10, v11, v12, v13, v14, v15, v16, v17) PASTE_MACRO3(func, v1, v2), PASTE_MACRO17(func, v1, v3, v4, v5, v6, v7, v8, v9, v10, v11, v12, v13, v14, v15, v16, v17)
#define PASTE_MACRO19(func, v1, v2, v3, v4, v5, v6, v7, v8, v9, v10, v11, v12, v13, v14, v15, v16, v17, v18) PASTE_MACRO3(func, v1, v2), PASTE_MACRO18(func, v1, v3, v4, v5, v6, v7, v8, v9, v10, v11, v12, v13, v14, v15, v16, v17, v18)
#define PASTE_MACRO20(func, v1, v2, v3, v4, v5, v6, v7, v8, v9, v10, v11, v12, v13, v14, v15, v16, v17, v18, v19) PASTE_MACRO3(func, v1, v2), PASTE_MACRO19(func, v1, v3, v4, v5, v6, v7, v8, v9, v10, v11, v12, v13, v14, v15, v16, v17, v18, v19)
#define PASTE_MACRO21(func, v1, v2, v3, v4, v5, v6, v7, v8, v9, v10, v11, v12, v13, v14, v15, v16, v17, v18, v19, v20) PASTE_MACRO3(func, v1, v2), PASTE_MACRO20(func, v1, v3, v4, v5, v6, v7, v8, v9, v10, v11, v12, v13, v14, v15, v16, v17, v18, v19, v20)
#define PASTE_MACRO22(func, v1, v2, v3, v4, v5, v6, v7, v8, v9, v10, v11, v12, v13, v14, v15, v16, v17, v18, v19, v20, v21) PASTE_MACRO3(func, v1, v2), PASTE_MACRO21(func, v1, v3, v4, v5, v6, v7, v8, v9, v10, v11, v12, v13, v14, v15, v16, v17, v18, v19, v20, v21)
#define PASTE_MACRO23(func, v1, v2, v3, v4, v5, v6, v7, v8, v9, v10, v11, v12, v13, v14, v15, v16, v17, v18, v19, v20, v21, v22) PASTE_MACRO3(func, v1, v2), PASTE_MACRO22(func, v1, v3, v4, v5, v6, v7, v8, v9, v10, v11, v12, v13, v14, v15, v16, v17, v18, v19, v20, v21, v22)
#define PASTE_MACRO24(func, v1, v2, v3, v4, v5, v6, v7, v8, v9, v10, v11, v12, v13, v14, v15, v16, v17, v18, v19, v20, v21, v22, v23) PASTE_MACRO3(func, v1, v2), PASTE_MACRO23(func, v1, v3, v4, v5, v6, v7, v8, v9, v10, v11, v12, v13, v14, v15, v16, v17, v18, v19, v20, v21, v22, v23)
#define PASTE_MACRO25(func, v1, v2, v3, v4, v5, v6, v7, v8, v9, v10, v11, v12, v13, v14, v15, v16, v17, v18, v19, v20, v21, v22, v23, v24) PASTE_MACRO3(func, v1, v2), PASTE_MACRO24(func, v1, v3, v4, v5, v6, v7, v8, v9, v10, v11, v12, v13, v14, v15, v16, v17, v18, v19, v20, v21, v22, v23, v24)
#define PASTE_MACRO26(func, v1, v2, v3, v4, v5, v6, v7, v8, v9, v10, v11, v12, v13, v14, v15, v16, v17, v18, v19, v20, v21, v22, v23, v24, v25) PASTE_MACRO3(func, v1, v2), PASTE_MACRO25(func, v1, v3, v4, v5, v6, v7, v8, v9, v10, v11, v12, v13, v14, v15, v16, v17, v18, v19, v20, v21, v22, v23, v24, v25)
#define PASTE_MACRO27(func, v1, v2, v3, v4, v5, v6, v7, v8, v9, v10, v11, v12, v13, v14, v15, v16, v17, v18, v19, v20, v21, v22, v23, v24, v25, v26) PASTE_MACRO3(func, v1, v2), PASTE_MACRO26(func, v1, v3, v4, v5, v6, v7, v8, v9, v10, v11, v12, v13, v14, v15, v16, v17, v18, v19, v20, v21, v22, v23, v24, v25, v26)
#define PASTE_MACRO28(func, v1, v2, v3, v4, v5, v6, v7, v8, v9, v10, v11, v12, v13, v14, v15, v16, v17, v18, v19, v20, v21, v22, v23, v24, v25, v26, v27) PASTE_MACRO3(func, v1, v2), PASTE_MACRO27(func, v1, v3, v4, v5, v6, v7, v8, v9, v10, v11, v12, v13, v14, v15, v16, v17, v18, v19, v20, v21, v22, v23, v24, v25, v26, v27)
#define PASTE_MACRO29(func, v1, v2, v3, v4, v5, v6, v7, v8, v9, v10, v11, v12, v13, v14, v15, v16, v17, v18, v19, v20, v21, v22, v23, v24, v25, v26, v27, v28) PASTE_MACRO3(func, v1, v2), PASTE_MACRO28(func, v1, v3, v4, v5, v6, v7, v8, v9, v10, v11, v12, v13, v14, v15, v16, v17, v18, v19, v20, v21, v22, v23, v24, v25, v26, v27, v28)
#define PASTE_MACRO30(func, v1, v2, v3, v4, v5, v6, v7, v8, v9, v10, v11, v12, v13, v14, v15, v16, v17, v18, v19, v20, v21, v22, v23, v24, v25, v26, v27, v28, v29) PASTE_MACRO3(func, v1, v2), PASTE_MACRO29(func, v1, v3, v4, v5, v6, v7, v8, v9, v10, v11, v12, v13, v14, v15, v16, v17, v18, v19, v20, v21, v22, v23, v24, v25, v26, v27, v28, v29)
#define PASTE_MACRO31(func, v1, v2, v3, v4, v5, v6, v7, v8, v9, v10, v11, v12, v13, v14, v15, v16, v17, v18, v19, v20, v21, v22, v23, v24, v25, v26, v27, v28, v29, v30) PASTE_MACRO3(func, v1, v2), PASTE_MACRO30(func, v1, v3, v4, v5, v6, v7, v8, v9, v10, v11, v12, v13, v14, v15, v16, v17, v18, v19, v20, v21, v22, v23, v24, v25, v26, v27, v28, v29, v30)
#define PASTE_MACRO32(func, v1, v2, v3, v4, v5, v6, v7, v8, v9, v10, v11, v12, v13, v14, v15, v16, v17, v18, v19, v20, v21, v22, v23, v24, v25, v26, v27, v28, v29, v30, v31) PASTE_MACRO3(func, v1, v2), PASTE_MACRO31(func, v1, v3, v4, v5, v6, v7, v8, v9, v10, v11, v12, v13, v14, v15, v16, v17, v18, v19, v20, v21, v22, v23, v24, v25, v26, v27, v28, v29, v30, v31)
#define PASTE_MACRO33(func, v1, v2, v3, v4, v5, v6, v7, v8, v9, v10, v11, v12, v13, v14, v15, v16, v17, v18, v19, v20, v21, v22, v23, v24, v25, v26, v27, v28, v29, v30, v31, v32) PASTE_MACRO3(func, v1, v2), PASTE_MACRO32(func, v1, v3, v4, v5, v6, v7, v8, v9, v10, v11, v12, v13, v14, v15, v16, v17, v18, v19, v20, v21, v22, v23, v24, v25, v26, v27, v28, v29, v30, v31, v32)
#define PASTE_MACRO34(func, v1, v2, v3, v4, v5, v6, v7, v8, v9, v10, v11, v12, v13, v14, v15, v16, v17, v18, v19, v20, v21, v22, v23, v24, v25, v26, v27, v28, v29, v30, v31, v32, v33) PASTE_MACRO3(func, v1, v2), PASTE_MACRO33(func, v1, v3, v4, v5, v6, v7, v8, v9, v10, v11, v12, v13, v14, v15, v16, v17, v18, v19, v20, v21, v22, v23, v24, v25, v26, v27, v28, v29, v30, v31, v32, v33)
#define PASTE_MACRO35(func, v1, v2, v3, v4, v5, v6, v7, v8, v9, v10, v11, v12, v13, v14, v15, v16, v17, v18, v19, v20, v21, v22, v23, v24, v25, v26, v27, v28, v29, v30, v31, v32, v33, v34) PASTE_MACRO3(func, v1, v2), PASTE_MACRO34(func, v1, v3, v4, v5, v6, v7, v8, v9, v10, v11, v12, v13, v14, v15, v16, v17, v18, v19, v20, v21, v22, v23, v24, v25, v26, v27, v28, v29, v30, v31, v32, v33, v34)
#define PASTE_MACRO36(func, v1, v2, v3, v4, v5, v6, v7, v8, v9, v10, v11, v12, v13, v14, v15, v16, v17, v18, v19, v20, v21, v22, v23, v24, v25, v26, v27, v28, v29, v30, v31, v32, v33, v34, v35) PASTE_MACRO3(func, v1, v2), PASTE_MACRO35(func, v1, v3, v4, v5, v6, v7, v8, v9, v10, v11, v12, v13, v14, v15, v16, v17, v18, v19, v20, v21, v22, v23, v24, v25, v26, v27, v28, v29, v30, v31, v32, v33, v34, v35)
#define PASTE_MACRO37(func, v1, v2, v3, v4, v5, v6, v7, v8, v9, v10, v11, v12, v13, v14, v15, v16, v17, v18, v19, v20, v21, v22, v23, v24, v25, v26, v27, v28, v29, v30, v31, v32, v33, v34, v35, v36) PASTE_MACRO3(func, v1, v2), PASTE_MACRO36(func, v1, v3, v4, v5, v6, v7, v8, v9, v10, v11, v12, v13, v14, v15, v16, v17, v18, v19, v20, v21, v22, v23, v24, v25, v26, v27, v28, v29, v30, v31, v32, v33, v34, v35, v36)
#define PASTE_MACRO38(func, v1, v2, v3, v4, v5, v6, v7, v8, v9, v10, v11, v12, v13, v14, v15, v16, v17, v18, v19, v20, v21, v22, v23, v24, v25, v26, v27, v28, v29, v30, v31, v32, v33, v34, v35, v36, v37) PASTE_MACRO3(func, v1, v2), PASTE_MACRO37(func, v1, v3, v4, v5, v6, v7, v8, v9, v10, v11, v12, v13, v14, v15, v16, v17, v18, v19, v20, v21, v22, v23, v24, v25, v26, v27, v28, v29, v30, v31, v32, v33, v34, v35, v36, v37)
#define PASTE_MACRO39(func, v1, v2, v3, v4, v5, v6, v7, v8, v9, v10, v11, v12, v13, v14, v15, v16, v17, v18, v19, v20, v21, v22, v23, v24, v25, v26, v27, v28, v29, v30, v31, v32, v33, v34, v35, v36, v37, v38) PASTE_MACRO3(func, v1, v2), PASTE_MACRO38(func, v1, v3, v4, v5, v6, v7, v8, v9, v10, v11, v12, v13, v14, v15, v16, v17, v18, v19, v20, v21, v22, v23, v24, v25, v26, v27, v28, v29, v30, v31, v32, v33, v34, v35, v36, v37, v38)
#define PASTE_MACRO40(func, v1, v2, v3, v4, v5, v6, v7, v8, v9, v10, v11, v12, v13, v14, v15, v16, v17, v18, v19, v20, v21, v22, v23, v24, v25, v26, v27, v28, v29, v30, v31, v32, v33, v34, v35, v36, v37, v38, v39) PASTE_MACRO3(func, v1, v2), PASTE_MACRO39(func, v1, v3, v4, v5, v6, v7, v8, v9, v10, v11, v12, v13, v14, v15, v16, v17, v18, v19, v20, v21, v22, v23, v24, v25, v26, v27, v28, v29, v30, v31, v32, v33, v34, v35, v36, v37, v38, v39)
#define PASTE_MACRO41(func, v1, v2, v3, v4, v5, v6, v7, v8, v9, v10, v11, v12, v13, v14, v15, v16, v17, v18, v19, v20, v21, v22, v23, v24, v25, v26, v27, v28, v29, v30, v31, v32, v33, v34, v35, v36, v37, v38, v39, v40) PASTE_MACRO3(func, v1, v2), PASTE_MACRO40(func, v1, v3, v4, v5, v6, v7, v8, v9, v10, v11, v12, v13, v14, v15, v16, v17, v18, v19, v20, v21, v22, v23, v24, v25, v26, v27, v28, v29, v30, v31, v32, v33, v34, v35, v36, v37, v38, v39, v40)
#define PASTE_MACRO42(func, v1, v2, v3, v4, v5, v6, v7, v8, v9, v10, v11, v12, v13, v14, v15, v16, v17, v18, v19, v20, v21, v22, v23, v24, v25, v26, v27, v28, v29, v30, v31, v32, v33, v34, v35, v36, v37, v38, v39, v40, v41) PASTE_MACRO3(func, v1, v2), PASTE_MACRO41(func, v1, v3, v4, v5, v6, v7, v8, v9, v10, v11, v12, v13, v14, v15, v16, v17, v18, v19, v20, v21, v22, v23, v24, v25, v26, v27, v28, v29, v30, v31, v32, v33, v34, v35, v36, v37, v38, v39, v40, v41)
#define PASTE_MACRO43(func, v1, v2, v3, v4, v5, v6, v7, v8, v9, v10, v11, v12, v13, v14, v15, v16, v17, v18, v19, v20, v21, v22, v23, v24, v25, v26, v27, v28, v29, v30, v31, v32, v33, v34, v35, v36, v37, v38, v39, v40, v41, v42) PASTE_MACRO3(func, v1, v2), PASTE_MACRO42(func, v1, v3, v4, v5, v6, v7, v8, v9, v10, v11, v12, v13, v14, v15, v16, v17, v18, v19, v20, v21, v22, v23, v24, v25, v26, v27, v28, v29, v30, v31, v32, v33, v34, v35, v36, v37, v38, v39, v40, v41, v42)
#define PASTE_MACRO44(func, v1, v2, v3, v4, v5, v6, v7, v8, v9, v10, v11, v12, v13, v14, v15, v16, v17, v18, v19, v20, v21, v22, v23, v24, v25, v26, v27, v28, v29, v30, v31, v32, v33, v34, v35, v36, v37, v38, v39, v40, v41, v42, v43) PASTE_MACRO3(func, v1, v2), PASTE_MACRO43(func, v1, v3, v4, v5, v6, v7, v8, v9, v10, v11, v12, v13, v14, v15, v16, v17, v18, v19, v20, v21, v22, v23, v24, v25, v26, v27, v28, v29, v30, v31, v32, v33, v34, v35, v36, v37, v38, v39, v40, v41, v42, v43)
#define PASTE_MACRO45(func, v1, v2, v3, v4, v5, v6, v7, v8, v9, v10, v11, v12, v13, v14, v15, v16, v17, v18, v19, v20, v21, v22, v23, v24, v25, v26, v27, v28, v29, v30, v31, v32, v33, v34, v35, v36, v37, v38, v39, v40, v41, v42, v43, v44) PASTE_MACRO3(func, v1, v2), PASTE_MACRO44(func, v1, v3, v4, v5, v6, v7, v8, v9, v10, v11, v12, v13, v14, v15, v16, v17, v18, v19, v20, v21, v22, v23, v24, v25, v26, v27, v28, v29, v30, v31, v32, v33, v34, v35, v36, v37, v38, v39, v40, v41, v42, v43, v44)
#define PASTE_MACRO46(func, v1, v2, v3, v4, v5, v6, v7, v8, v9, v10, v11, v12, v13, v14, v15, v16, v17, v18, v19, v20, v21, v22, v23, v24, v25, v26, v27, v28, v29, v30, v31, v32, v33, v34, v35, v36, v37, v38, v39, v40, v41, v42, v43, v44, v45) PASTE_MACRO3(func, v1, v2), PASTE_MACRO45(func, v1, v3, v4, v5, v6, v7, v8, v9, v10, v11, v12, v13, v14, v15, v16, v17, v18, v19, v20, v21, v22, v23, v24, v25, v26, v27, v28, v29, v30, v31, v32, v33, v34, v35, v36, v37, v38, v39, v40, v41, v42, v43, v44, v45)
#define PASTE_MACRO47(func, v1, v2, v3, v4, v5, v6, v7, v8, v9, v10, v11, v12, v13, v14, v15, v16, v17, v18, v19, v20, v21, v22, v23, v24, v25, v26, v27, v28, v29, v30, v31, v32, v33, v34, v35, v36, v37, v38, v39, v40, v41, v42, v43, v44, v45, v46) PASTE_MACRO3(func, v1, v2), PASTE_MACRO46(func, v1, v3, v4, v5, v6, v7, v8, v9, v10, v11, v12, v13, v14, v15, v16, v17, v18, v19, v20, v21, v22, v23, v24, v25, v26, v27, v28, v29, v30, v31, v32, v33, v34, v35, v36, v37, v38, v39, v40, v41, v42, v43, v44, v45, v46)
#define PASTE_MACRO48(func, v1, v2, v3, v4, v5, v6, v7, v8, v9, v10, v11, v12, v13, v14, v15, v16, v17, v18, v19, v20, v21, v22, v23, v24, v25, v26, v27, v28, v29, v30, v31, v32, v33, v34, v35, v36, v37, v38, v39, v40, v41, v42, v43, v44, v45, v46, v47) PASTE_MACRO3(func, v1, v2), PASTE_MACRO47(func, v1, v3, v4, v5, v6, v7, v8, v9, v10, v11, v12, v13, v14, v15, v16, v17, v18, v19, v20, v21, v22, v23, v24, v25, v26, v27, v28, v29, v30, v31, v32, v33, v34, v35, v36, v37, v38, v39, v40, v41, v42, v43, v44, v45, v46, v47)
#define PASTE_MACRO49(func, v1, v2, v3, v4, v5, v6, v7, v8, v9, v10, v11, v12, v13, v14, v15, v16, v17, v18, v19, v20, v21, v22, v23, v24, v25, v26, v27, v28, v29, v30, v31, v32, v33, v34, v35, v36, v37, v38, v39, v40, v41, v42, v43, v44, v45, v46, v47, v48) PASTE_MACRO3(func, v1, v2), PASTE_MACRO48(func, v1, v3, v4, v5, v6, v7, v8, v9, v10, v11, v12, v13, v14, v15, v16, v17, v18, v19, v20, v21, v22, v23, v24, v25, v26, v27, v28, v29, v30, v31, v32, v33, v34, v35, v36, v37, v38, v39, v40, v41, v42, v43, v44, v45, v46, v47, v48)
#define PASTE_MACRO50(func, v1, v2, v3, v4, v5, v6, v7, v8, v9, v10, v11, v12, v13, v14, v15, v16, v17, v18, v19, v20, v21, v22, v23, v24, v25, v26, v27, v28, v29, v30, v31, v32, v33, v34, v35, v36, v37, v38, v39, v40, v41, v42, v43, v44, v45, v46, v47, v48, v49) PASTE_MACRO3(func, v1, v2), PASTE_MACRO49(func, v1, v3, v4, v5, v6, v7, v8, v9, v10, v11, v12, v13, v14, v15, v16, v17, v18, v19, v20, v21, v22, v23, v24, v25, v26, v27, v28, v29, v30, v31, v32, v33, v34, v35, v36, v37, v38, v39, v40, v41, v42, v43, v44, v45, v46, v47, v48, v49)
#define PASTE_MACRO51(func, v1, v2, v3, v4, v5, v6, v7, v8, v9, v10, v11, v12, v13, v14, v15, v16, v17, v18, v19, v20, v21, v22, v23, v24, v25, v26, v27, v28, v29, v30, v31, v32, v33, v34, v35, v36, v37, v38, v39, v40, v41, v42, v43, v44, v45, v46, v47, v48, v49, v50) PASTE_MACRO3(func, v1, v2), PASTE_MACRO50(func, v1, v3, v4, v5, v6, v7, v8, v9, v10, v11, v12, v13, v14, v15, v16, v17, v18, v19, v20, v21, v22, v23, v24, v25, v26, v27, v28, v29, v30, v31, v32, v33, v34, v35, v36, v37, v38, v39, v40, v41, v42, v43, v44, v45, v46, v47, v48, v49, v50)
#define PASTE_MACRO52(func, v1, v2, v3, v4, v5, v6, v7, v8, v9, v10, v11, v12, v13, v14, v15, v16, v17, v18, v19, v20, v21, v22, v23, v24, v25, v26, v27, v28, v29, v30, v31, v32, v33, v34, v35, v36, v37, v38, v39, v40, v41, v42, v43, v44, v45, v46, v47, v48, v49, v50, v51) PASTE_MACRO3(func, v1, v2), PASTE_MACRO51(func, v1, v3, v4, v5, v6, v7, v8, v9, v10, v11, v12, v13, v14, v15, v16, v17, v18, v19, v20, v21, v22, v23, v24, v25, v26, v27, v28, v29, v30, v31, v32, v33, v34, v35, v36, v37, v38, v39, v40, v41, v42, v43, v44, v45, v46, v47, v48, v49, v50, v51)
#define PASTE_MACRO53(func, v1, v2, v3, v4, v5, v6, v7, v8, v9, v10, v11, v12, v13, v14, v15, v16, v17, v18, v19, v20, v21, v22, v23, v24, v25, v26, v27, v28, v29, v30, v31, v32, v33, v34, v35, v36, v37, v38, v39, v40, v41, v42, v43, v44, v45, v46, v47, v48, v49, v50, v51, v52) PASTE_MACRO3(func, v1, v2), PASTE_MACRO52(func, v1, v3, v4, v5, v6, v7, v8, v9, v10, v11, v12, v13, v14, v15, v16, v17, v18, v19, v20, v21, v22, v23, v24, v25, v26, v27, v28, v29, v30, v31, v32, v33, v34, v35, v36, v37, v38, v39, v40, v41, v42, v43, v44, v45, v46, v47, v48, v49, v50, v51, v52)
#define PASTE_MACRO54(func, v1, v2, v3, v4, v5, v6, v7, v8, v9, v10, v11, v12, v13, v14, v15, v16, v17, v18, v19, v20, v21, v22, v23, v24, v25, v26, v27, v28, v29, v30, v31, v32, v33, v34, v35, v36, v37, v38, v39, v40, v41, v42, v43, v44, v45, v46, v47, v48, v49, v50, v51, v52, v53) PASTE_MACRO3(func, v1, v2), PASTE_MACRO53(func, v1, v3, v4, v5, v6, v7, v8, v9, v10, v11, v12, v13, v14, v15, v16, v17, v18, v19, v20, v21, v22, v23, v24, v25, v26, v27, v28, v29, v30, v31, v32, v33, v34, v35, v36, v37, v38, v39, v40, v41, v42, v43, v44, v45, v46, v47, v48, v49, v50, v51, v52, v53)
#define PASTE_MACRO55(func, v1, v2, v3, v4, v5, v6, v7, v8, v9, v10, v11, v12, v13, v14, v15, v16, v17, v18, v19, v20, v21, v22, v23, v24, v25, v26, v27, v28, v29, v30, v31, v32, v33, v34, v35, v36, v37, v38, v39, v40, v41, v42, v43, v44, v45, v46, v47, v48, v49, v50, v51, v52, v53, v54) PASTE_MACRO3(func, v1, v2), PASTE_MACRO54(func, v1, v3, v4, v5, v6, v7, v8, v9, v10, v11, v12, v13, v14, v15, v16, v17, v18, v19, v20, v21, v22, v23, v24, v25, v26, v27, v28, v29, v30, v31, v32, v33, v34, v35, v36, v37, v38, v39, v40, v41, v42, v43, v44, v45, v46, v47, v48, v49, v50, v51, v52, v53, v54)
#define PASTE_MACRO56(func, v1, v2, v3, v4, v5, v6, v7, v8, v9, v10, v11, v12, v13, v14, v15, v16, v17, v18, v19, v20, v21, v22, v23, v24, v25, v26, v27, v28, v29, v30, v31, v32, v33, v34, v35, v36, v37, v38, v39, v40, v41, v42, v43, v44, v45, v46, v47, v48, v49, v50, v51, v52, v53, v54, v55) PASTE_MACRO3(func, v1, v2), PASTE_MACRO55(func, v1, v3, v4, v5, v6, v7, v8, v9, v10, v11, v12, v13, v14, v15, v16, v17, v18, v19, v20, v21, v22, v23, v24, v25, v26, v27, v28, v29, v30, v31, v32, v33, v34, v35, v36, v37, v38, v39, v40, v41, v42, v43, v44, v45, v46, v47, v48, v49, v50, v51, v52, v53, v54, v55)
#define PASTE_MACRO57(func, v1, v2, v3, v4, v5, v6, v7, v8, v9, v10, v11, v12, v13, v14, v15, v16, v17, v18, v19, v20, v21, v22, v23, v24, v25, v26, v27, v28, v29, v30, v31, v32, v33, v34, v35, v36, v37, v38, v39, v40, v41, v42, v43, v44, v45, v46, v47, v48, v49, v50, v51, v52, v53, v54, v55, v56) PASTE_MACRO3(func, v1, v2), PASTE_MACRO56(func, v1, v3, v4, v5, v6, v7, v8, v9, v10, v11, v12, v13, v14, v15, v16, v17, v18, v19, v20, v21, v22, v23, v24, v25, v26, v27, v28, v29, v30, v31, v32, v33, v34, v35, v36, v37, v38, v39, v40, v41, v42, v43, v44, v45, v46, v47, v48, v49, v50, v51, v52, v53, v54, v55, v56)
#define PASTE_MACRO58(func, v1, v2, v3, v4, v5, v6, v7, v8, v9, v10, v11, v12, v13, v14, v15, v16, v17, v18, v19, v20, v21, v22, v23, v24, v25, v26, v27, v28, v29, v30, v31, v32, v33, v34, v35, v36, v37, v38, v39, v40, v41, v42, v43, v44, v45, v46, v47, v48, v49, v50, v51, v52, v53, v54, v55, v56, v57) PASTE_MACRO3(func, v1, v2), PASTE_MACRO57(func, v1, v3, v4, v5, v6, v7, v8, v9, v10, v11, v12, v13, v14, v15, v16, v17, v18, v19, v20, v21, v22, v23, v24, v25, v26, v27, v28, v29, v30, v31, v32, v33, v34, v35, v36, v37, v38, v39, v40, v41, v42, v43, v44, v45, v46, v47, v48, v49, v50, v51, v52, v53, v54, v55, v56, v57)
#define PASTE_MACRO59(func, v1, v2, v3, v4, v5, v6, v7, v8, v9, v10, v11, v12, v13, v14, v15, v16, v17, v18, v19, v20, v21, v22, v23, v24, v25, v26, v27, v28, v29, v30, v31, v32, v33, v34, v35, v36, v37, v38, v39, v40, v41, v42, v43, v44, v45, v46, v47, v48, v49, v50, v51, v52, v53, v54, v55, v56, v57, v58) PASTE_MACRO3(func, v1, v2), PASTE_MACRO58(func, v1, v3, v4, v5, v6, v7, v8, v9, v10, v11, v12, v13, v14, v15, v16, v17, v18, v19, v20, v21, v22, v23, v24, v25, v26, v27, v28, v29, v30, v31, v32, v33, v34, v35, v36, v37, v38, v39, v40, v41, v42, v43, v44, v45, v46, v47, v48, v49, v50, v51, v52, v53, v54, v55, v56, v57, v58)
#define PASTE_MACRO60(func, v1, v2, v3, v4, v5, v6, v7, v8, v9, v10, v11, v12, v13, v14, v15, v16, v17, v18, v19, v20, v21, v22, v23, v24, v25, v26, v27, v28, v29, v30, v31, v32, v33, v34, v35, v36, v37, v38, v39, v40, v41, v42, v43, v44, v45, v46, v47, v48, v49, v50, v51, v52, v53, v54, v55, v56, v57, v58, v59) PASTE_MACRO3(func, v1, v2), PASTE_MACRO59(func, v1, v3, v4, v5, v6, v7, v8, v9, v10, v11, v12, v13, v14, v15, v16, v17, v18, v19, v20, v21, v22, v23, v24, v25, v26, v27, v28, v29, v30, v31, v32, v33, v34, v35, v36, v37, v38, v39, v40, v41, v42, v43, v44, v45, v46, v47, v48, v49, v50, v51, v52, v53, v54, v55, v56, v57, v58, v59)
#define PASTE_MACRO61(func, v1, v2, v3, v4, v5, v6, v7, v8, v9, v10, v11, v12, v13, v14, v15, v16, v17, v18, v19, v20, v21, v22, v23, v24, v25, v26, v27, v28, v29, v30, v31, v32, v33, v34, v35, v36, v37, v38, v39, v40, v41, v42, v43, v44, v45, v46, v47, v48, v49, v50, v51, v52, v53, v54, v55, v56, v57, v58, v59, v60) PASTE_MACRO3(func, v1, v2), PASTE_MACRO60(func, v1, v3, v4, v5, v6, v7, v8, v9, v10, v11, v12, v13, v14, v15, v16, v17, v18, v19, v20, v21, v22, v23, v24, v25, v26, v27, v28, v29, v30, v31, v32, v33, v34, v35, v36, v37, v38, v39, v40, v41, v42, v43, v44, v45, v46, v47, v48, v49, v50, v51, v52, v53, v54, v55, v56, v57, v58, v59, v60)
#define PASTE_MACRO62(func, v1, v2, v3, v4, v5, v6, v7, v8, v9, v10, v11, v12, v13, v14, v15, v16, v17, v18, v19, v20, v21, v22, v23, v24, v25, v26, v27, v28, v29, v30, v31, v32, v33, v34, v35, v36, v37, v38, v39, v40, v41, v42, v43, v44, v45, v46, v47, v48, v49, v50, v51, v52, v53, v54, v55, v56, v57, v58, v59, v60, v61) PASTE_MACRO3(func, v1, v2), PASTE_MACRO61(func, v1, v3, v4, v5, v6, v7, v8, v9, v10, v11, v12, v13, v14, v15, v16, v17, v18, v19, v20, v21, v22, v23, v24, v25, v26, v27, v28, v29, v30, v31, v32, v33, v34, v35, v36, v37, v38, v39, v40, v41, v42, v43, v44, v45, v46, v47, v48, v49, v50, v51, v52, v53, v54, v55, v56, v57, v58, v59, v60, v61)
#define PASTE_MACRO63(func, v1, v2, v3, v4, v5, v6, v7, v8, v9, v10, v11, v12, v13, v14, v15, v16, v17, v18, v19, v20, v21, v22, v23, v24, v25, v26, v27, v28, v29, v30, v31, v32, v33, v34, v35, v36, v37, v38, v39, v40, v41, v42, v43, v44, v45, v46, v47, v48, v49, v50, v51, v52, v53, v54, v55, v56, v57, v58, v59, v60, v61, v62) PASTE_MACRO3(func, v1, v2), PASTE_MACRO62(func, v1, v3, v4, v5, v6, v7, v8, v9, v10, v11, v12, v13, v14, v15, v16, v17, v18, v19, v20, v21, v22, v23, v24, v25, v26, v27, v28, v29, v30, v31, v32, v33, v34, v35, v36, v37, v38, v39, v40, v41, v42, v43, v44, v45, v46, v47, v48, v49, v50, v51, v52, v53, v54, v55, v56, v57, v58, v59, v60, v61, v62)
#define PASTE_MACRO64(func, v1, v2, v3, v4, v5, v6, v7, v8, v9, v10, v11, v12, v13, v14, v15, v16, v17, v18, v19, v20, v21, v22, v23, v24, v25, v26, v27, v28, v29, v30, v31, v32, v33, v34, v35, v36, v37, v38, v39, v40, v41, v42, v43, v44, v45, v46, v47, v48, v49, v50, v51, v52, v53, v54, v55, v56, v57, v58, v59, v60, v61, v62, v63) PASTE_MACRO3(func, v1, v2), PASTE_MACRO63(func, v1, v3, v4, v5, v6, v7, v8, v9, v10, v11, v12, v13, v14, v15, v16, v17, v18, v19, v20, v21, v22, v23, v24, v25, v26, v27, v28, v29, v30, v31, v32, v33, v34, v35, v36, v37, v38, v39, v40, v41, v42, v43, v44, v45, v46, v47, v48, v49, v50, v51, v52, v53, v54, v55, v56, v57, v58, v59, v60, v61, v62, v63)

#endif

// #include "detail/types.hpp"
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
// #include "detail/remove_macros.hpp"
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

#ifndef USE_KX_MACROS
#undef S
#undef C
#undef G
#undef H
#undef I
#undef J
#undef E
#undef F
#undef V
#undef U
#undef kU
#undef xU
// #undef K
#undef DO
#undef XT
#undef XD
#undef nh
#undef wh
#undef ni
#undef wi
#undef nj
#undef wj
#undef nf
#undef wf
#undef finite
#undef closesocket
#undef R
#undef O
#undef R
#undef Z
#undef P
#undef U
#undef SW
#undef CS
#undef CD
#undef ZV
#undef ZK
#undef ZH
#undef ZI
#undef ZJ
#undef ZE
#undef ZF
#undef ZC
#undef ZS
#undef K1
#undef K2
#undef TX
#undef xr
#undef xt
#undef xu
#undef xn
#undef xx
#undef xy
#undef xg
#undef xh
#undef xi
#undef xj
#undef xe
#undef xf
#undef xs
#undef xk
#undef xG
#undef xH
#undef xI
#undef xJ
#undef xE
#undef xF
#undef xS
#undef xK
#undef xC
#undef xB
// #undef kG
#undef kC
#undef kH
// #undef kI
#undef kJ
#undef kE
#undef kF
#undef kS
// #undef kK
#undef KB
#undef UU
#undef KG
#undef KH
// #undef KI
#undef KJ
#undef KE
#undef KF
#undef KC
#undef KS
#undef KP
#undef KM
#undef KD
#undef KN
#undef KU
#undef KV
#undef KT
#undef KZ
#endif


#endif
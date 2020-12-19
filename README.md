# KDB C++ Template Library

- [Introduction](#introduction)
- [Features](#features)
- [Examples](#examples)
- [Building](#building)
- [License](#license)
- [Contact](#contact)

## Introduction
A template library for efficiently converting to/from native C++ types to KDB without any knowledge of the underlying KDB apis. This is a header only library, so you do not need to install
anything to use it in your project. You can just copy the `include` directory into your own project.

The instructions below show how to build the benchmarking and test executables used for library development.

**Please Note!** This project requires a C++17 compatible compiler to build as it's using constexpr and std::variant. You can check compiler
compatiblility with these features at [cppreference.com](https://en.cppreference.com/w/cpp/compiler_support).

## Features

- **Header Only**: The library has no dependencies other than copying a single header file into your project.
- **Zero Overhead**: The library aims to generate code that's as fast as what you would write by hand. Features that you don't use cost nothing.
- **STL Enabled**: Supports conversion of all the basic STL containers!
- **No Macros!**: The macros that are in the `k.h` header file often conflict with template parameters used by popular C++ libraries (boost, eigen etc.). These are undefined by default in this library for better C++ compatibility.
- **Extensible**: You can teach the library to convert your own types and they will work seamlessly with the existing types.

## Examples

### Basic Types

```c++
// just include the kdb.hpp header to pull in all of the functionality
#include <markrooney/kdb.hpp>

// the types live under the kdb::type namespace 
using kdb::type;

// some convenient type aliases are defined since the macros have been removed by the library
atom_bool  z = true;        // 1 byte boolean        (kdb: b)
atom_char  c = 'e';         // 1 byte character      (kdb: c) 
atom_short h = 372;         // 2 byte integer        (kdb: h)
atom_int   i = 65738;       // 4 byte integer        (kdb: i)
atom_long  j = 7245645623;  // 8 byte integer        (kdb: j)
atom_real  x = 174.26;      // 4 byte floating point (kdb: e)
atom_float y = 827784.123;  // 8 byte floating point (kdb: f)

// there are equivalent list types for all of the atom types - these are aliases for a std::vector
// and support all of the operations you are used to for manipulating lists.
list_bool  zl = { false, true, false };
list_char  cl = { 'a', 'b', 'c' };
list_short hl = { 1, 2, 3, 4, 5 };
list_int   il = { 1, 2, 3, 4, 5 };
list_long  jl = { 1, 2, 3, 4, 5 };
list_real  xl = { 26.4, 26.1, 85.3 };
list_float yl = { 100, 57.2, 73.274 };

// there are variant types that can hold any type of object and will be converted to the correct 
// type dynamically (note: there is some overhead vs using concrete types due to checking the 
// type before conversion)
atom_any a = "example";
atom_any b = 42;

// the list_mixed type holds atom_any objects and maps to a list of type 0 in kdb.
list_mixed ml = { 42, "example", false };
ml.push_back(73.5);
ml.push_back('a');
```

### Conversions

```c++
atom_float f = 42.5;
list_float fl = { 42.5, 12.7, 85.2 };
list_mixed ml = { 42, "example", false };

// conversion to a K object is performed via from_native. This will generate
// code for the type at compile time as though you had written the conversion
// by hand.
K kf  = from_native(f);
K kfl = from_native(fl);
K kml = from_native(ml);

// supported types can be nested arbitrarily. all of the std:: types and
// collections are supported by default. it's easy to add your own custom
// types to this too.
template<typename T1, typename T2>
using dict = std::unordered_map<T1,T2>;

dict<atom_symbol, list_float> weather = { 
        {"NYC", {77, 64.5, 71.4, 74.7}},
        {"LDN", {63.2, 51.7, 65.8, 71.5}},
        {"HK",  {87.5, 83.61, 81.2, 76, 79.9}}
};

// conversion is exactly the same as with the simple types
K weather_table = from_native(weather);

// We can convert K datastructures back into native C++ types using to_native.
// In this case the type is inferred from the second argument that we are placing
// the result into.
dict<atom_symbol, list_float> result;
to_native(weather_table, result);

// you can also call to_native and specify the type explicitly.
auto result = to_native<dict<atom_symbol, list_float>>(weather_table)
```

### Adding custom types

```c++
// The KDB_REGISTER macro can be used to teach the library about custom structures
// that you would like to serialize. This macro will generate code to convert the
// data to a mixed list containing the items.
//
// The macro takes a list of fields to include in the conversion. Any fields you
// don't place in the macro will be skipped and will remain uninitialized after
// a call to to_native.
struct MyData {
    float timeout;
    int sessionId;
    std::string sessionName;
};
KDB_REGISTER(MyData, timeout, sessionId, sessionName)

// after registration, conversion of these types is as simple as calling from_native
MyData data = { 3050.0, 100, "example session name" };
K r = from_native(data);

// the new type is also handled automatically within containers
std::vector<MyData> data_list = {
        { 3050.0, 100, "example session name"},
        { 1000.0, 85,  "another session name"},
        { 8472.0, 10,  "more session names"}
};
K y = from_native(data_list);
```

## Building
1. Checkout the project with submodules. This will also checkout vcpkg for you.
```bash
# clone the project from github along with any submodules
git clone --recurse-submodules https://github.com/markrooney/kdb-templates.git
# change directory into the project
cd kdb-templates
```

2. Bootstrap and initialize vcpkg for your system.
```bash
# initialize vcpkg on your system by running the bootstrap script
./thirdparty/vcpkg/bootstrap-vcpkg.sh
```

3. Run cmake to build the executables.

```bash
# create the build directory and initialize cmake there.
cmake -DCMAKE_BUILD_TYPE=Release -B build .
# perform the build inside the build directory
cmake --build build
```

4. Run the benchmark and test executables.

```bash
# run the benchmarks
./build/benchmarking
# run the tests
./build/test-runner
```

## License

Copyright 2020 Mark Rooney

Licensed under the Apache License, Version 2.0 (the "License");
you may not use this file except in compliance with the License.
You may obtain a copy of the License at

     http://www.apache.org/licenses/LICENSE-2.0

Unless required by applicable law or agreed to in writing, software
distributed under the License is distributed on an "AS IS" BASIS,
WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
See the License for the specific language governing permissions and
limitations under the License.

## Contact

If you have any suggestions or issues relating to the library, please [open an issue on GitHub](https://github.com/markrooney/kdb-templates/issues/new/choose).

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

```c++
#include <markrooney/kdb.hpp>

using kdb::convert;
using kdb::type;

// conversions between C++ and K types are supported via the to_native and from_native
// functions.
int x = 200;

// from_native will pick the appropriate K type automatically at compile time
// to avoid any overhead.
K kobj = from_native(x);

// to_native will attempt to convert the kobject to the native type and will
// throw an exception if it's not the correct type.
auto y = to_native<int>(kobj); 

// to_native can also infer the type and possibly avoid a copy/default construction
// if you already have a variable to put the result in.
int z;
to_native(kobj, z);

// some convenient type aliases are defined since the macros have been removed by the library
atom_bool  z = true;
atom_real  x = 174.26;      // 4 byte floating point as defined via the E macro.
atom_float y = 827784.123;  // 8 byte floating point as defined via the F macro.

// there are equivalent list types for all of the atom types - these are aliases for a std::vector
// and support all of the operations you are used to for manipulating lists.
list_bool  zl = { false, true, false };
list_real  xl = { 26.4, 26.1, 85.3 };
list_float yl = { 100, 57.2, 73.274 };

// there are variant types that can hold any type of object and will be converted to the correct 
// type dynamically (note: there is some overhead vs using concrete types due to checking the 
// type before conversion)
atom_any a = "example";
atom_any b = 42;

// the list_mixed type holds atom_any objects and maps to a list of type 0 in kdb.
list_mixed ml = { 42, "example", false };
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

# kdb-templates
A template library for converting to/from native C++ types to KDB without any knowledge of the underlying KDB apis. This is a header only library, so you do not need to install
anything to use it in your project. You can just copy the `include` directory into your own project.

The instructions below show how to build the benchmarking and test executables used for library development.

**Please Note!** This project requires a C++17 compatible compiler to build as it's using constexpr and std::variant. You can check compiler
compatiblility with these features at [cppreference.com](https://en.cppreference.com/w/cpp/compiler_support).

## Building the Tests/Benchmarks
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
./vcpkg/bootstrap-vcpkg.sh
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



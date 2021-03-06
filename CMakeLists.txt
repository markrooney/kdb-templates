cmake_minimum_required(VERSION 3.14)

set(CMAKE_TOOLCHAIN_FILE ${CMAKE_SOURCE_DIR}/thirdparty/vcpkg/scripts/buildsystems/vcpkg.cmake
        CACHE STRING "Vcpkg toolchain file")

project(Example)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -Wall -march=native")

# ------------------------------------------------------------------------------------- #
# Export Interface                                                                      #
# ------------------------------------------------------------------------------------- #

add_library(kdb-cpp INTERFACE)
target_include_directories(kdb-cpp INTERFACE release/)

# ------------------------------------------------------------------------------------- #
# Dependencies                                                                          #
# ------------------------------------------------------------------------------------- #

find_package(doctest CONFIG REQUIRED)
find_package(GTest CONFIG REQUIRED)
find_package(benchmark CONFIG REQUIRED)

include_directories(
        "${CMAKE_SOURCE_DIR}/thirdparty/kx/c/c"
        "${CMAKE_SOURCE_DIR}/include")

# ------------------------------------------------------------------------------------- #
# Benchmarks                                                                            #
# ------------------------------------------------------------------------------------- #

add_executable(benchmarking
        "${CMAKE_SOURCE_DIR}/benchmarks/bench_atom_conversion.cpp"
        "${CMAKE_SOURCE_DIR}/thirdparty/kx/l64/c.o")

target_link_libraries(benchmarking
        "kdb-cpp"
        "benchmark::benchmark"
        pthread)

# ------------------------------------------------------------------------------------- #
# Unit Tests                                                                            #
# ------------------------------------------------------------------------------------- #

add_executable(test-runner
        "${CMAKE_SOURCE_DIR}/tests/test.cpp"
        "${CMAKE_SOURCE_DIR}/tests/test_atom_conversion.cpp"
        "${CMAKE_SOURCE_DIR}/tests/test_list_conversion.cpp"
        "${CMAKE_SOURCE_DIR}/tests/test_nested_conversion.cpp"
        "${CMAKE_SOURCE_DIR}/tests/test_custom_types.cpp"
        "${CMAKE_SOURCE_DIR}/tests/test_stl_conversion.cpp"
        "${CMAKE_SOURCE_DIR}/thirdparty/kx/l64/c.o")

target_include_directories(test-runner
        PRIVATE
        "${CMAKE_SOURCE_DIR}/thirdparty/kx/c/c"
        "${CMAKE_SOURCE_DIR}/include")

target_link_libraries(test-runner
        "kdb-cpp"
        "doctest::doctest"
        "pthread")
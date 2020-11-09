cmake_minimum_required(VERSION 3.14)
project(Example)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -march=native")

include(FetchContent)

# ------------------------------------------------------------------------------------- #
# Dependencies                                                                          #
# ------------------------------------------------------------------------------------- #

FetchContent_Declare(
        doctest
        GIT_REPOSITORY https://github.com/onqtam/doctest.git
        GIT_TAG        2.4.1
)
FetchContent_MakeAvailable(doctest)

FetchContent_Declare(
        googletest
        GIT_REPOSITORY https://github.com/google/googletest.git
        GIT_TAG         master
)
FetchContent_MakeAvailable(googletest)

FetchContent_Declare(
        benchmark
        GIT_REPOSITORY https://github.com/google/benchmark.git
        GIT_TAG        master
)
FetchContent_MakeAvailable(benchmark)

include_directories(
        "${CMAKE_SOURCE_DIR}/thirdparty"
        "${CMAKE_SOURCE_DIR}/include")

# ------------------------------------------------------------------------------------- #
# Benchmarks                                                                            #
# ------------------------------------------------------------------------------------- #

add_executable(benchmarking
        "${CMAKE_SOURCE_DIR}/benchmarks/bench_atom_conversion.cpp"
        "${CMAKE_SOURCE_DIR}/c.o")

target_link_libraries(benchmarking
        benchmark
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
        "${CMAKE_SOURCE_DIR}/c.o")

target_include_directories(test-runner
        PRIVATE
        "${CMAKE_SOURCE_DIR}/thirdparty"
        "${CMAKE_SOURCE_DIR}/include")

target_link_libraries(test-runner
        "pthread")
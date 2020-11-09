#include <iostream>
#include <vector>
#include <benchmark/benchmark.h>

#define KXVER 3
#include <kx/k.h>

#include <markrooney/kdb.hpp>

static void BM_CreatingAndReleasingKObjects(benchmark::State& state) {
    khp((S) "",-1);
    int data = 42;

    while (state.KeepRunning()) {
        K obj = ki(data);
        r0(obj);
    }
}
BENCHMARK(BM_CreatingAndReleasingKObjects);

static void BM_CreatingFromTemplate(benchmark::State& state) {
    khp((S) "",-1);
    int data = 42;

    while (state.KeepRunning()) {
        K obj = kdb::convert::from_native(data);
        r0(obj);
    }
}
BENCHMARK(BM_CreatingFromTemplate);

static void BM_CreatingFromAtomIntType(benchmark::State& state) {
    khp((S) "",-1);
    kdb::type::atom_int data = 42;

    while (state.KeepRunning()) {
        K obj = kdb::convert::from_native(data);
        r0(obj);
    }
}
BENCHMARK(BM_CreatingFromAtomIntType);

static void BM_CreatingFromAnyType(benchmark::State& state) {
    khp((S) "",-1);
    kdb::type::atom_any data = 42;

    while (state.KeepRunning()) {
        K obj = kdb::convert::from_native(data);
        r0(obj);
    }
}
BENCHMARK(BM_CreatingFromAnyType);

static void BM_CreatingListConcat(benchmark::State& state) {
    khp((S) "",-1);
    int data = 42;

    while (state.KeepRunning()) {
        K list = ktn(KI, 0);
        for (int i = 0; i < state.range(0); i++) {
            ja(&list, &data);
        }
        r0(list);
    }
}
BENCHMARK(BM_CreatingListConcat)->Range(8, 8<<12);

static void BM_CreatingListPreAlloc(benchmark::State& state) {
    khp((S) "",-1);
    int data = 42;

    while (state.KeepRunning()) {
        K list = ktn(KI, state.range(0));
        for (int i = 0; i < state.range(0); i++) {
            kI(list)[i] = data;
        }
        r0(list);
    }
}
BENCHMARK(BM_CreatingListPreAlloc)->Range(8, 8<<12);

static void BM_CreatingListMemSet(benchmark::State& state) {
    khp((S) "",-1);
    int data = 42;

    while (state.KeepRunning()) {
        K list = ktn(KI, state.range(0));
        std::memset(kI(list), data, sizeof(int) * state.range(0));
        r0(list);
    }
}
BENCHMARK(BM_CreatingListMemSet)->Range(8, 8<<12);

static void BM_CreatingListFromVectorNaive(benchmark::State& state) {
    khp((S) "",-1);

    std::vector<int> data;
    for (int i = 0; i < state.range(0); i++) {
        data.push_back(i);
    }

    while (state.KeepRunning()) {
        int n = data.size();
        K list = ktn(KI, 0);
        for (int i = 0; i < n; i++) {
            ja(&list, &data[i]);
        }
        r0(list);
    }
}
BENCHMARK(BM_CreatingListFromVectorNaive)->Range(8, 8<<12);

static void BM_CreatingListFromVectorPreAlloc(benchmark::State& state) {
    khp((S) "",-1);

    std::vector<int> data;
    for (int i = 0; i < state.range(0); i++) {
        data.push_back(i);
    }

    while (state.KeepRunning()) {
        int n = data.size();
        K list = ktn(KI, n);
        for (int i = 0; i < n; i++) {
            kI(list)[i] = data[i];
        }
        r0(list);
    }
}
BENCHMARK(BM_CreatingListFromVectorPreAlloc)->Range(8, 8<<12);

static void BM_CreatingListFromVectorMemCpy(benchmark::State& state) {
    khp((S) "",-1);

    std::vector<int> data;
    for (int i = 0; i < state.range(0); i++) {
        data.push_back(i);
    }

    while (state.KeepRunning()) {
        int n = data.size();
        K list = ktn(KI, n);
        std::memcpy(kI(list), data.data(), sizeof(int) * n);
        r0(list);
    }
}
BENCHMARK(BM_CreatingListFromVectorMemCpy)->Range(8, 8<<12);

static void BM_CreatingListFromVectorTemplate(benchmark::State& state) {
    khp((S) "",-1);

    std::vector<int> data;
    for (int i = 0; i < state.range(0); i++) {
        data.push_back(i);
    }

    while (state.KeepRunning()) {
        K list = kdb::convert::from_native(data);
        r0(list);
    }
}
BENCHMARK(BM_CreatingListFromVectorTemplate)->Range(8, 8<<12);

static void BM_CreatingListFromListTypes(benchmark::State& state) {
    khp((S) "",-1);

    kdb::type::list_int data;

    for (int i = 0; i < state.range(0); i++) {
        data.push_back(i);
    }

    while (state.KeepRunning()) {
        K list = kdb::convert::from_native(data);
        r0(list);
    }
}
BENCHMARK(BM_CreatingListFromListTypes)->Range(8, 8<<12);

static void BM_CreatingListFromAnyListTypes(benchmark::State& state) {
    khp((S) "",-1);

    kdb::type::list_int data;

    for (int i = 0; i < state.range(0); i++) {
        data.push_back(i);
    }

    kdb::type::any_list test = data;

    while (state.KeepRunning()) {
        K list = kdb::convert::from_native(test);
        r0(list);
    }
}
BENCHMARK(BM_CreatingListFromAnyListTypes)->Range(8, 8<<12);


struct instr {
    kdb::type::atom_symbol symbol;
    kdb::type::atom_float price;
    kdb::type::atom_long quantity;
};

KDB_REGISTER_TYPE(instr,
    &instr::symbol,
    &instr::price,
    &instr::quantity)

static void BM_CreatingStructNoTemplate(benchmark::State& state) {
    khp((S) "",-1);

    instr data = { .symbol = "MSFT", .price = 23.7, .quantity = 15768 };

    while (state.KeepRunning()) {
        K list = ktn(0, 3);
        kK(list)[0] = ks(data.symbol.data());
        kK(list)[1] = kf(data.price);
        kK(list)[2] = kj(data.quantity);
        r0(list);
    }
}
BENCHMARK(BM_CreatingStructNoTemplate);

static void BM_CreatingStructConcat(benchmark::State& state) {
    khp((S) "",-1);

    instr data = { .symbol = "MSFT", .price = 23.7, .quantity = 15768 };

    while (state.KeepRunning()) {
        K list = ktn(0, 0);
        jk(&list, ks(data.symbol.data()));
        jk(&list, kf(data.price));
        jk(&list, kf(data.quantity));
        r0(list);
    }
}
BENCHMARK(BM_CreatingStructConcat);

static void BM_CreatingStructTemplate(benchmark::State& state) {
    khp((S) "",-1);

    instr data = { .symbol = "MSFT", .price = 23.7, .quantity = 15768 };

    while (state.KeepRunning()) {
        K list = kdb::convert::from_native(data);
        r0(list);
    }
}
BENCHMARK(BM_CreatingStructTemplate);

BENCHMARK_MAIN();
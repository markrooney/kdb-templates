#include <vector>
#include <benchmark/benchmark.h>

#define KXVER 3
#include <kx/k.h>

#include <markrooney/kdb.hpp>

using namespace kdb::convert;
using namespace kdb::type;

static void CreatingAtomMANUAL(benchmark::State &state) {
  khp((S) "", -1);
  int data = 42;

  while (state.KeepRunning()) {
    K obj = ki(data);
    r0(obj);
    benchmark::DoNotOptimize(obj);
  }
}
BENCHMARK(CreatingAtomMANUAL);

static void CreatingAtomTEMPLATE(benchmark::State &state) {
  khp((S) "", -1);
  int data = 42;

  while (state.KeepRunning()) {
    K obj = from_native(data);
    r0(obj);
    benchmark::DoNotOptimize(obj);
  }
}
BENCHMARK(CreatingAtomTEMPLATE);

static void CreatingAtomVARIANTTEMPLATE(benchmark::State &state) {
  khp((S) "", -1);
  atom_any data = 42;

  while (state.KeepRunning()) {
    K obj = from_native(data);
    r0(obj);
    benchmark::DoNotOptimize(obj);
  }
}
BENCHMARK(CreatingAtomVARIANTTEMPLATE);

static void CreatingListFromVectorMANUAL(benchmark::State &state) {
  khp((S) "", -1);

  std::vector<int> data;
  for (int i = 0; i < state.range(0); i++) {
    data.push_back(i);
  }

  for (auto _ : state) {
      int n = data.size();
      K list = ktn(KI, n);
      for (int i = 0; i < n; i++) {
          kI(list)[i] = data[i];
      }
      r0(list);
      benchmark::DoNotOptimize(list);
  }
}
BENCHMARK(CreatingListFromVectorMANUAL)->Range(8, 8 << 16);

static void CreatingListFromVectorTEMPLATE(benchmark::State &state) {
  khp((S) "", -1);

  std::vector<int> data;
  for (int i = 0; i < state.range(0); i++) {
    data.push_back(i);
  }

  for (auto _ : state) {
    K list = from_native(data);
    r0(list);
    benchmark::DoNotOptimize(list);
  }
}
BENCHMARK(CreatingListFromVectorTEMPLATE)->Range(8, 8 << 16);

struct wrapper {
  atom_float one;
  atom_long two;
};

KDB_REGISTER_TYPE(wrapper,
                  &wrapper::one,
                  &wrapper::two)

struct instr {
  atom_float price;
  atom_long quantity;
  wrapper data;
};

KDB_REGISTER_TYPE(instr,
                  &instr::price,
                  &instr::quantity,
                  &instr::data)

static void CreatingStructMANUAL(benchmark::State &state) {
  khp((S) "", -1);

  instr data = { .price = 23.7, .quantity = 15768, .data = { .one = 42.6134, .two = 2747 } };

  for (auto _ : state) {
    K list = ktn(0, 3);
    kK(list)[0] = kf(data.price);
    kK(list)[1] = kj(data.quantity);

    K inner = ktn(0, 2);
    kK(inner)[0] = kf(data.data.one);
    kK(inner)[1] = kj(data.data.two);
    kK(list)[2] = inner;

    r0(list);
  }
}
BENCHMARK(CreatingStructMANUAL);

static void CreatingStructTEMPLATE(benchmark::State &state) {
  khp((S) "", -1);

  auto data = instr{.price = 23.7, .quantity = 15768, .data = { .one = 42.6134, .two = 2747 }};

  for (auto _ : state) {
    K list = kdb::convert::from_native(data);
    r0(list);
  }
}
BENCHMARK(CreatingStructTEMPLATE);

BENCHMARK_MAIN();
#include <vector>
#include <benchmark/benchmark.h>

#define KXVER 3
#include <kx/k.h>

#undef U
#undef P
#undef R

#include <markrooney/kdb.hpp>

#include <arrow/api.h>


/*
static void BM_CreatingAndReleasingKObjects(benchmark::State &state) {
  khp((S) "", -1);
  int data = 42;

  while (state.KeepRunning()) {
    K obj = ki(data);
    r0(obj);
  }
}
BENCHMARK(BM_CreatingAndReleasingKObjects);

static void BM_CreatingFromTemplate(benchmark::State &state) {
  khp((S) "", -1);
  int data = 42;

  while (state.KeepRunning()) {
    K obj = kdb::convert::from_native(data);
    r0(obj);
  }
}
BENCHMARK(BM_CreatingFromTemplate);

static void BM_CreatingFromAtomIntType(benchmark::State &state) {
  khp((S) "", -1);
  kdb::type::atom_int data = 42;

  while (state.KeepRunning()) {
    K obj = kdb::convert::from_native(data);
    r0(obj);
  }
}
BENCHMARK(BM_CreatingFromAtomIntType);

static void BM_CreatingFromAnyType(benchmark::State &state) {
  khp((S) "", -1);
  kdb::type::atom_any data = 42;

  while (state.KeepRunning()) {
    K obj = kdb::convert::from_native(data);
    r0(obj);
  }
}
BENCHMARK(BM_CreatingFromAnyType);

static void BM_CreatingListConcat(benchmark::State &state) {
  khp((S) "", -1);
  int data = 42;

  while (state.KeepRunning()) {
    K list = ktn(KI, 0);
    for (int i = 0; i < state.range(0); i++) {
      ja(&list, &data);
    }
    r0(list);
  }
}
BENCHMARK(BM_CreatingListConcat)->Range(8, 8 << 12);

static void BM_CreatingListPreAlloc(benchmark::State &state) {
  khp((S) "", -1);
  int data = 42;

  while (state.KeepRunning()) {
    K list = ktn(KI, state.range(0));
    for (int i = 0; i < state.range(0); i++) {
      kI(list)[i] = data;
    }
    r0(list);
  }
}
BENCHMARK(BM_CreatingListPreAlloc)->Range(8, 8 << 12);

static void BM_CreatingListMemSet(benchmark::State &state) {
  khp((S) "", -1);
  int data = 42;

  while (state.KeepRunning()) {
    K list = ktn(KI, state.range(0));
    std::memset(kI(list), data, sizeof(int) * state.range(0));
    r0(list);
  }
}
BENCHMARK(BM_CreatingListMemSet)->Range(8, 8 << 12);

static void BM_CreatingListFromVectorNaive(benchmark::State &state) {
  khp((S) "", -1);

  std::vector<int> data;
  for (int i = 0; i < state.range(0); i++) {
    data.push_back(i);
  }

  for (auto _ : state) {
    int n = data.size();
    K list = ktn(KI, 0);
    for (int i = 0; i < n; i++) {
      ja(&list, &data[i]);
    }
    r0(list);
  }
}
BENCHMARK(BM_CreatingListFromVectorNaive)->Range(8, 8 << 12);

static void BM_CreatingListFromVectorPreAlloc(benchmark::State &state) {
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
  }
}
BENCHMARK(BM_CreatingListFromVectorPreAlloc)->Range(8, 8 << 12);

static void BM_CreatingListFromVectorMemCpy(benchmark::State &state) {
  khp((S) "", -1);

  std::vector<int> data;
  for (int i = 0; i < state.range(0); i++) {
    data.push_back(i);
  }

  for (auto _ : state) {
    int n = data.size();
    K list = ktn(KI, n);
    std::memcpy(kI(list), data.data(), sizeof(int) * n);
    r0(list);
  }
}
BENCHMARK(BM_CreatingListFromVectorMemCpy)->Range(8, 8 << 12);

static void BM_CreatingListFromVectorTemplate(benchmark::State &state) {
  khp((S) "", -1);

  std::vector<int> data;
  for (int i = 0; i < state.range(0); i++) {
    data.push_back(i);
  }

  for (auto _ : state) {
    K list = kdb::convert::from_native(data);
    r0(list);
  }
}
BENCHMARK(BM_CreatingListFromVectorTemplate)->Range(8, 8 << 12);

static void BM_CreatingListFromListTypes(benchmark::State &state) {
  khp((S) "", -1);

  kdb::type::list_int data;

  for (int i = 0; i < state.range(0); i++) {
    data.push_back(i);
  }

  for (auto _ : state) {
    K list = kdb::convert::from_native(data);
    r0(list);
  }
}
BENCHMARK(BM_CreatingListFromListTypes)->Range(8, 8 << 12);

static void BM_CreatingListFromAnyListTypes(benchmark::State &state) {
  khp((S) "", -1);

  kdb::type::list_int data;

  for (int i = 0; i < state.range(0); i++) {
    data.push_back(i);
  }

  kdb::type::any_list test = data;

  for (auto _ : state) {
    K list = kdb::convert::from_native(test);
    r0(list);
  }
}
BENCHMARK(BM_CreatingListFromAnyListTypes)->Range(8, 8 << 12);
*/

struct wrapper {
  kdb::type::atom_float one;
  kdb::type::atom_long two;
};

KDB_REGISTER_TYPE(wrapper,
                  &wrapper::one,
                  &wrapper::two)

struct instr {
  kdb::type::atom_float price;
  kdb::type::atom_long quantity;
  wrapper data;
};

KDB_REGISTER_TYPE(instr,
                  &instr::price,
                  &instr::quantity,
                  &instr::data)

struct mapping {
  int quantity;
  float price;
  short marker;
  long size;
  float high;
  float low;
  float open;
  float close;
};

static void BM_CreatingDictWithoutTemplate(benchmark::State &state) {
  khp((S) "", -1);

  arrow::Result<std::unique_ptr<arrow::Buffer>> maybe_buffer = arrow::AllocateBuffer(4096);

  mapping map = {
    .quantity = 100,
    .price = 421.0,
    .marker = 4,
    .size = 137498234,
    .high = 5,
    .low = 8,
    .open = 1,
    .close = 3
  };

  for (auto _ : state) {
    K keys = ktn(KS, 8);
    K values = ktn(0, 8);

    kS(keys)[0] = ss((char *) "quantity");
    kS(keys)[1] = ss((char *) "price");
    kS(keys)[2] = ss((char *) "marker");
    kS(keys)[3] = ss((char *) "size");
    kS(keys)[4] = ss((char *) "high");
    kS(keys)[5] = ss((char *) "low");
    kS(keys)[6] = ss((char *) "open");
    kS(keys)[7] = ss((char *) "close");

    kK(values)[0] = ki(map.quantity);
    kK(values)[1] = kf(map.price);
    kK(values)[2] = kh(map.marker);
    kK(values)[3] = kj(map.size);
    kK(values)[4] = kf(map.high);
    kK(values)[5] = kf(map.low);
    kK(values)[6] = kf(map.open);
    kK(values)[7] = kf(map.close);

    K dict = xD(keys, values);
    r0(dict);
  }
}
BENCHMARK(BM_CreatingDictWithoutTemplate);

static void BM_CreatingStructNoTemplate(benchmark::State &state) {
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
BENCHMARK(BM_CreatingStructNoTemplate);

static void BM_CreatingStructTemplate(benchmark::State &state) {
  khp((S) "", -1);

  instr data = { .price = 23.7, .quantity = 15768, .data = { .one = 42.6134, .two = 2747 } };

  for (auto _ : state) {
    K list = kdb::convert::from_native(data);
    r0(list);
  }
}
BENCHMARK(BM_CreatingStructTemplate);


BENCHMARK_MAIN();
#!/bin/bash


echo "#include <benchmark/benchmark.h>"

echo "#include \"generate/generate_all.h\""

RANGE=16

for i in $(seq 1 $RANGE); do
  echo "static void BM_GenerateDynamicAll$i(benchmark::State &state) {
  for (auto _ : state) {
    generate::GenerateDynamic($i);
  }
}";
done

for i in $(seq 1 $RANGE); do
  if [ $i -ge 12 ] && [ $i -lt 16 ]; then
    echo "BENCHMARK(BM_GenerateDynamicAll$i)->Iterations(50);"
  else
    echo "BENCHMARK(BM_GenerateDynamicAll$i);"
  fi
done

echo "BENCHMARK_MAIN();"

#!/bin/bash


echo "#include <benchmark/benchmark.h>"

echo "#include \"generate/generate_all.h\""

RANGE=16

for i in $(seq 1 $RANGE); do
  echo "static void BM_GenerateMemoedAll$i(benchmark::State &state) {
  for (auto _ : state) {
    generate::GenerateMemoed($i);
  }
}";
done

for i in $(seq 1 $RANGE); do
  if [ $i -ge 12 ]; then
    echo "BENCHMARK(BM_GenerateMemoedAll$i)->Iterations(50);"
  else
    echo "BENCHMARK(BM_GenerateMemoedAll$i);"
  fi
done

echo "BENCHMARK_MAIN();"

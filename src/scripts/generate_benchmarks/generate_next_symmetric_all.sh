#!/bin/bash


echo "#include <benchmark/benchmark.h>"

echo "#include \"generate/generate_next_symmetric.h\""

RANGE=15

for i in $(seq 1 $RANGE); do
  x=$((2 * i))
  echo "static void BM_GenerateNextSymmetricAll$x(benchmark::State &state) {
  generate::SymmetricGenerator generator($x);

  for (auto _ : state) {
    for (auto num = generator.GenerateNext();
        num != generate::SymmetricGenerator::kErrorWord; num = generator.GenerateNext())
      ;
  }
}";
done

for i in $(seq 1 $RANGE); do
  x=$((2 * i))
  echo "BENCHMARK(BM_GenerateNextSymmetricAll$x);"
done

echo "BENCHMARK_MAIN();"

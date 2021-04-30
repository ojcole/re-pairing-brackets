#!/bin/bash


echo "#include <benchmark/benchmark.h>"

echo "#include \"generate/generate_next.h\""

RANGE=20

for i in $(seq 1 $RANGE); do
  echo "static void BM_GenerateNextAll$i(benchmark::State &state) {
  generate::Generator generator($i);

  for (auto _ : state) {
    for (auto num = generator.GenerateNext();
        num != generate::Generator::kErrorWord; num = generator.GenerateNext())
      ;
  }
}";
done

for i in $(seq 1 $RANGE); do
  echo "BENCHMARK(BM_GenerateNextAll$i);"
done

echo "BENCHMARK_MAIN();"

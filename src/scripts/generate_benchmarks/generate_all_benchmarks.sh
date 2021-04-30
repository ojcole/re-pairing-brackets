bazel run //benchmark/generate/all:generate_dynamic_all > ./results/benchmarks/all_generation/dynamic.txt
bazel run //benchmark/generate/all:generate_simple_all > ./results/benchmarks/all_generation/simple.txt
bazel run //benchmark/generate/all:generate_simple_memo_all > ./results/benchmarks/all_generation/memo.txt
bazel run //benchmark/generate/next:generate_next_all_string > ./results/benchmarks/all_generation/next.txt
bazel run //benchmark/generate/next:generate_swapping_all > ./results/benchmarks/all_generation/swapping.txt

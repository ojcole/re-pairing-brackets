bazel run //benchmark/generate/random:generate_random_symmetric_hard > results/benchmarks/random_generation/symmetric_hard.txt
bazel run //benchmark/generate/random:generate_random_hard > results/benchmarks/random_generation/hard.txt
bazel run //benchmark/generate/random:generate_random_uniform > results/benchmarks/random_generation/uniform.txt
bazel run //benchmark/generate/random:generate_random_symmetric > results/benchmarks/random_generation/symmetric.txt

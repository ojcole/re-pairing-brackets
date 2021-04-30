load("@rules_cc//cc:defs.bzl", "cc_binary")
load("//benchmark:cc_opts.bzl", "COPTS")

cc_binary(
    name = "exhaustive_bench",
    srcs = ["solve_exhaustive.cc"],
    copts = COPTS,
    data = [
        "exhaustive_bench_set100.txt",
        "exhaustive_bench_set200.txt",
        "exhaustive_bench_set50.txt",
    ],
    deps = [
        "//generate:generate_random",
        "//solve:solve_approximate",
        "//solve/exhaustive:solve_exhaustive",
        "@benchmark",
    ],
)

cc_binary(
    name = "solve_exhaustive_random_uniform",
    srcs = ["solve_exhaustive_random_uniform.cc"],
    copts = COPTS,
    deps = [
        "//generate:generate_random",
        "//solve/exhaustive:solve_exhaustive",
        "@benchmark",
    ],
)

cc_binary(
    name = "solve_exhaustive_random_symmetric_hard",
    srcs = ["solve_exhaustive_random_symmetric_hard.cc"],
    copts = COPTS,
    deps = [
        "//generate:generate_random",
        "//solve/exhaustive:solve_exhaustive",
        "@benchmark",
    ],
)

cc_binary(
    name = "solve_exhaustive_random_symmetric",
    srcs = ["solve_exhaustive_random_symmetric.cc"],
    copts = COPTS,
    deps = [
        "//generate:generate_random",
        "//solve/exhaustive:solve_exhaustive",
        "@benchmark",
    ],
)

cc_binary(
    name = "solve_exhaustive_random_hard",
    srcs = ["solve_exhaustive_random_hard.cc"],
    copts = COPTS,
    deps = [
        "//generate:generate_random",
        "//solve/exhaustive:solve_exhaustive",
        "@benchmark",
    ],
)

cc_binary(
    name = "solve_exhaustive_random_uniform_no_greedy",
    srcs = ["solve_exhaustive_random_uniform_no_greedy.cc"],
    copts = COPTS,
    deps = [
        "//generate:generate_random",
        "//solve/exhaustive:solve_exhaustive",
        "@benchmark",
    ],
)

cc_binary(
    name = "solve_exhaustive_random_symmetric_hard_no_greedy",
    srcs = ["solve_exhaustive_random_symmetric_hard_no_greedy.cc"],
    copts = COPTS,
    deps = [
        "//generate:generate_random",
        "//solve/exhaustive:solve_exhaustive",
        "@benchmark",
    ],
)

cc_binary(
    name = "solve_exhaustive_random_symmetric_no_greedy",
    srcs = ["solve_exhaustive_random_symmetric_no_greedy.cc"],
    copts = COPTS,
    deps = [
        "//generate:generate_random",
        "//solve/exhaustive:solve_exhaustive",
        "@benchmark",
    ],
)

cc_binary(
    name = "solve_exhaustive_random_hard_no_greedy",
    srcs = ["solve_exhaustive_random_hard_no_greedy.cc"],
    copts = COPTS,
    deps = [
        "//generate:generate_random",
        "//solve/exhaustive:solve_exhaustive",
        "@benchmark",
    ],
)

load("@rules_cc//cc:defs.bzl", "cc_library", "cc_test")

cc_library(
    name = "results",
    srcs = ["results_output.cc"],
    hdrs = ["results_output.h"],
    visibility = ["//visibility:public"],
    deps = [
        ":random_sample",
        "//generate:generate_all",
        "//solve/parallel:solve",
    ],
)

cc_library(
    name = "random_sample",
    srcs = ["random_sample_width.cc"],
    hdrs = ["random_sample_width.h"],
    visibility = ["//visibility:public"],
    deps = [
        "//generate:generate_random",
        "//helpers/parallel:compute_parallel",
        "//solve/derived:derived_strategy",
        "//solve/exhaustive:solve_exhaustive",
    ],
)

cc_library(
    name = "compute_hardness",
    srcs = ["hardness.cc"],
    hdrs = ["hardness.h"],
    visibility = ["//visibility:public"],
    deps = [
        "//solve:solution",
        "//solve/exhaustive:solve_exhaustive",
    ],
)

cc_test(
    name = "hardness_test",
    size = "small",
    srcs = ["hardness_test.cc"],
    deps = [
        ":compute_hardness",
        "//generate:generate_random",
        "//solve:solve_approximate",
        "//solve/repairings:all_repairings",
        "@gtest",
        "@gtest//:gtest_main",
    ],
)

cc_test(
    name = "random_sample_width_test",
    size = "small",
    srcs = ["random_sample_width_test.cc"],
    deps = [
        ":random_sample",
        "@gtest",
        "@gtest//:gtest_main",
    ],
)

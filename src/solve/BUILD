load("@rules_cc//cc:defs.bzl", "cc_library", "cc_test")

cc_library(
    name = "solution",
    srcs = [
        "solution.cc",
    ],
    hdrs = [
        "solution.h",
    ],
    visibility = ["//visibility:public"],
    deps = ["//helpers:constants"],
)

cc_library(
    name = "solve_approximate",
    srcs = ["solve_approximate.cc"],
    hdrs = ["solve_approximate.h"],
    visibility = ["//visibility:public"],
    deps = [
        "//helpers/solutions:combine_solutions",
        "//solve/derived:derived_strategy",
        "//solve/greedy:solve_greedy",
    ],
)

cc_library(
    name = "solve_test_helpers",
    srcs = ["solve_test_helpers.cc"],
    hdrs = ["solve_test_helpers.h"],
    visibility = ["//solve:__subpackages__"],
    deps = [
        ":solution",
    ],
)

cc_test(
    name = "solution_test",
    size = "small",
    srcs = ["solution_test.cc"],
    deps = [
        ":solution",
        "@gtest",
        "@gtest//:gtest_main",
    ],
)

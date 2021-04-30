load("@rules_cc//cc:defs.bzl", "cc_library", "cc_test")

cc_library(
    name = "derived_strategy",
    srcs = [
        "derived_strategy.cc",
        "free_moves.cc",
        "obvious_moves.cc",
    ],
    hdrs = [
        "derived_strategy.h",
        "free_moves.h",
        "obvious_moves.h",
    ],
    visibility = ["//visibility:public"],
    deps = [
        "//helpers:traversal",
        "//helpers/solutions:combine_solutions",
        "//solve:solution",
        "//solve/greedy",
    ],
)

cc_test(
    name = "free_moves_test",
    srcs = ["free_moves_test.cc"],
    deps = [
        ":derived_strategy",
        "//generate:generate_random",
        "@gtest",
        "@gtest//:gtest_main",
    ],
)

cc_test(
    name = "obvious_moves_test",
    srcs = ["obvious_moves_test.cc"],
    deps = [
        ":derived_strategy",
        "//generate:generate_random",
        "@gtest",
        "@gtest//:gtest_main",
    ],
)

cc_test(
    name = "derived_strategy_test",
    srcs = ["derived_strategy_test.cc"],
    deps = [
        ":derived_strategy",
        "//generate:generate_all",
        "//solve:solve_test_helpers",
        "@gtest",
        "@gtest//:gtest_main",
    ],
)

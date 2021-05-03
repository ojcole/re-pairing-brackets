load("@rules_cc//cc:defs.bzl", "cc_library", "cc_test")

cc_library(
    name = "solve_greedy",
    srcs = [
        "greedy_strategy_1.cc",
        "greedy_strategy_2.cc",
        "solve_greedy.cc",
        "solve_simple_greedy.cc",
    ],
    hdrs = [
        "greedy_strategy_1.h",
        "greedy_strategy_2.h",
        "solve_greedy.h",
        "solve_simple_greedy.h",
    ],
    visibility = ["//visibility:public"],
    deps = [
        "//solve:solution",
    ],
)

cc_library(
    name = "greedy",
    srcs = ["greedy.cc"],
    hdrs = ["greedy.h"],
    visibility = ["//visibility:public"],
    deps = [
        ":solve_greedy",
        "//helpers/solutions:combine_solutions",
        "//solve:solution",
    ],
)

cc_library(
    name = "strahler",
    srcs = [
        "calculate_strahler.cc",
    ],
    hdrs = [
        "calculate_strahler.h",
    ],
    visibility = ["//visibility:public"],
    deps = [
        "//solve:solution",
    ],
)

cc_test(
    name = "calculate_strahler_test",
    size = "medium",
    srcs = ["calculate_strahler_test.cc"],
    deps = [
        ":solve_greedy",
        ":strahler",
        "//generate:generate_all",
        "@gtest",
        "@gtest//:gtest_main",
    ],
)

cc_test(
    name = "solve_simple_greedy_test",
    size = "small",
    srcs = ["solve_simple_greedy_test.cc"],
    deps = [
        ":solve_greedy",
        "//generate:generate_all",
        "//solve:solve_test_helpers",
        "@gtest",
        "@gtest//:gtest_main",
    ],
)

cc_test(
    name = "solve_greedy_test",
    size = "small",
    srcs = ["solve_greedy_test.cc"],
    deps = [
        ":solve_greedy",
        "//generate:generate_all",
        "//solve:solve_test_helpers",
        "@gtest",
        "@gtest//:gtest_main",
    ],
)

load("@rules_cc//cc:defs.bzl", "cc_binary", "cc_library", "cc_test")
load("//manual:cc_opts.bzl", "COPTS")

cc_library(
    name = "manual_search",
    srcs = ["manual_search.cc"],
    hdrs = ["manual_search.h"],
    copts = COPTS,
    visibility = ["//visibility:public"],
    deps = [
        "//generate:generate_next",
        "//helpers:manipulators",
        "//helpers:traversal",
        "//helpers:verifiers",
        "//solve:solution",
        "//solve/predicate:width_check",
    ],
)

cc_binary(
    name = "manual",
    srcs = ["main.cc"],
    copts = COPTS,
    data = glob(["data_files/*"]),
    deps = [
        ":manual_search",
        "//generate:generate_next_symmetric",
        "//search:width_search",
        "//solve/exhaustive:solve_exhaustive",
        "//solve/greedy",
        "//solve/minimise:minimise_width",
        "//solve/predicate:width_check",
        "//stats:compute_hardness",
        "//stats:results",
    ],
)

cc_binary(
    name = "manual_genned",
    srcs = ["manual_genned.cc"],
    copts = COPTS,
    deps = [
        "//generate:generate_next",
        "//generate:generate_next_symmetric",
        "//helpers:catalan",
        "//helpers:nchoosek",
        "//search:width_search",
    ],
)

cc_test(
    name = "manual_search_test",
    srcs = ["manual_search_test.cc"],
    data = glob(["test_files/*"]),
    deps = [
        ":manual_search",
        "//generate:generate_random",
        "//helpers:manipulators",
        "@gtest",
        "@gtest//:gtest_main",
    ],
)

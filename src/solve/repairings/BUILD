load("@rules_cc//cc:defs.bzl", "cc_library", "cc_test")

cc_library(
    name = "all_repairings",
    srcs = ["all_repairings.cc"],
    hdrs = ["all_repairings.h"],
    visibility = ["//visibility:public"],
    deps = [
        "//solve:solution",
        "//solve/exhaustive:solve_exhaustive",
    ],
)

cc_test(
    name = "all_repairings_test",
    srcs = ["all_repairings_test.cc"],
    deps = [
        ":all_repairings",
        "//generate:generate_all",
        "//solve:solve_test_helpers",
        "@gtest",
        "@gtest//:gtest_main",
    ],
)

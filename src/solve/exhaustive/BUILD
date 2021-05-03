load("@rules_cc//cc:defs.bzl", "cc_library", "cc_test")

cc_library(
    name = "solve_exhaustive",
    srcs = [
        "solve_exhaustive.cc",
    ],
    hdrs = [
        "solve_exhaustive.h",
    ],
    visibility = ["//visibility:public"],
    deps = [
        "//solve:solution",
        "//solve:solve_approximate",
    ],
)

cc_test(
    name = "solve_exhaustive_test",
    size = "small",
    srcs = ["solve_exhaustive_test.cc"],
    deps = [
        "//generate:generate_all",
        "//solve:solve_test_helpers",
        "//solve/exhaustive:solve_exhaustive",
        "@gtest",
        "@gtest//:gtest_main",
    ],
)

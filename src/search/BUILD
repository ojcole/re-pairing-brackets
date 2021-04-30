load("@rules_cc//cc:defs.bzl", "cc_library")

cc_library(
    name = "width_search",
    srcs = [
        "segment_width_search.cc",
        "width_search.cc",
    ],
    hdrs = [
        "segment_width_search.h",
        "width_search.h",
    ],
    visibility = ["//visibility:public"],
    deps = [
        "//generate:generate_next",
        "//generate:generate_next_symmetric",
        "//generate:generate_random",
        "//helpers:manipulators",
        "//helpers:verifiers",
        "//helpers/parallel:compute_parallel",
        "//helpers/parallel:reducers",
        "//solve:solution",
        "//solve/derived:derived_strategy",
        "//solve/predicate:width_check",
    ],
)

cc_library(
    name = "random_walk_search",
    srcs = ["random_walk.cc"],
    hdrs = ["random_walk.h"],
    visibility = ["//visibility:public"],
    deps = [
        "//helpers:constants",
        "//helpers:verifiers",
        "//helpers/parallel:compute_parallel",
        "//helpers/parallel:reducers",
        "//solve/predicate:width_check",
    ],
)

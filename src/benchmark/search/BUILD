load("@rules_cc//cc:defs.bzl", "cc_binary")
load("//benchmark:cc_opts.bzl", "COPTS")

cc_binary(
    name = "random_width_search",
    srcs = ["random_width_search.cc"],
    copts = COPTS,
    deps = [
        "//generate:generate_random",
        "//search:width_search",
        "@benchmark",
    ],
)

cc_binary(
    name = "hard_width_search",
    srcs = ["symmetric_hard_width_search.cc"],
    copts = COPTS,
    deps = [
        "//search:width_search",
        "@benchmark",
    ],
)

cc_binary(
    name = "random_walk_search",
    srcs = ["random_walk_search.cc"],
    copts = COPTS,
    deps = [
        "//search:random_walk_search",
        "@benchmark",
    ],
)

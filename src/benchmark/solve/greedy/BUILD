load("@rules_cc//cc:defs.bzl", "cc_binary")
load("//benchmark:cc_opts.bzl", "COPTS")

cc_binary(
    name = "solve_greedy_simple",
    srcs = ["solve_greedy_simple.cc"],
    copts = COPTS,
    deps = [
        "//generate:generate_next",
        "//generate:generate_random",
        "//solve/greedy:solve_greedy",
        "@benchmark",
    ],
)

cc_binary(
    name = "solve_greedy_strahler",
    srcs = ["solve_greedy_strahler.cc"],
    copts = COPTS,
    deps = [
        "//generate:generate_next",
        "//generate:generate_random",
        "//solve/greedy:strahler",
        "@benchmark",
    ],
)

load("@rules_cc//cc:defs.bzl", "cc_binary")

cc_binary(
    name = "main",
    srcs = ["main.cc"],
    copts = [
        "-std=c++2a",
        "-Ofast",
        "-march=native",
    ],
    deps = [
        "//generate:generate_all",
        "//generate:generate_next",
        "//generate:generate_random",
        "//generate:generate_xyz",
        "//helpers:catalan",
        "//search:random_walk_search",
        "//search:width_search",
        "//solve/chistikov:solve_chistikov",
        "//solve/derived:derived_strategy",
        "//solve/exhaustive:solve_exhaustive",
        "//solve/greedy:solve_greedy",
        "//solve/greedy:strahler",
        "//solve/minimise:minimise_width",
        "//solve/parallel:solve",
        "//solve/predicate:width_check",
        "//solve/repairings:all_repairings",
        "//stats:compute_hardness",
        "//stats:random_sample",
        "//stats:results",
    ],
)

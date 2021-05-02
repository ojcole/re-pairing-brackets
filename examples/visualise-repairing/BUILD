load("@rules_cc//cc:defs.bzl", "cc_binary")
load("@//:copts.bzl", "COPTS")

cc_binary(
    name = "visualise-repairing",
    srcs = ["main.cc"],
    copts = COPTS,
    deps = [
        "@repairings//solve/exhaustive:solve_exhaustive",
        "@repairings//stats:results",
    ],
)

load("@rules_cc//cc:defs.bzl", "cc_library", "cc_binary")

cc_library(
    name = "common_deps",
    deps = [
        "@hello",
    ],
)

cc_binary(
    name = "sample",
    srcs = [
        "main.cpp",
    ],
    deps = [
        ":common_deps"
    ],
    linkopts = select({
        "@platforms//os:linux": ["-static-libstdc++", "-static-libgcc"],
        "//conditions:default": [],
    }),
)


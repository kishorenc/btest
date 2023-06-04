load("@rules_cc//cc:defs.bzl", "cc_library", "cc_binary")

cc_library(
    name = "headers",
    hdrs = glob([
        "include/**/*.h",
        "include/**/*.hpp",
    ]),
    includes = ["include"],
)

filegroup(
    name = "src_files",
    srcs = glob(["src/*.cpp"]),
)

cc_library(
    name = "common_deps",
    deps = [
        ":headers",
        "@hello",
        "@hnsw",
        "@com_github_facebookresearch_faiss//:faiss"
    ],
)

cc_binary(
    name = "sample",
    srcs = [
        ":src_files"
    ],
    deps = [
        ":common_deps",
    ],
    copts = ["-fopenmp", "-g", "-O2"],
    linkopts = ["-fopenmp"]
#    linkopts = select({
#        "@platforms//os:linux": ["-static-libstdc++", "-static-libgcc"],
#        "//conditions:default": [],
#    }),
)


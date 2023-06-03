load("@rules_foreign_cc//foreign_cc:defs.bzl", "cmake")

package(default_visibility = ["//visibility:public"])

licenses(["notice"])  # MIT

exports_files(["LICENSE"])

filegroup(
    name = "all_srcs",
    srcs = glob(["**"]),
    visibility = ["//visibility:public"],
)

CMAKE_CACHE_ENTRIES = {
    "CMAKE_PREFIX_PATH": "$$EXT_BUILD_DEPS$$/openblas",
}

cmake(
    name = "faiss",
    generate_args = [
        "-G Ninja",
        "-DFAISS_ENABLE_GPU=OFF",
        "-DFAISS_ENABLE_PYTHON=OFF",
        "-DFAISS_ENABLE_C_API=OFF",
        "-DBUILD_TESTING=OFF",
        "-DCMAKE_BUILD_TYPE=Release",
        "-DFAISS_OPT_LEVEL=general",
    ],
    cache_entries = CMAKE_CACHE_ENTRIES,
    lib_source = "//:all_srcs",
    out_static_libs = [
        "libfaiss.a",
    ],
    targets = [
        "faiss",
    ],
    deps = [
        "@com_github_xianyi_openblas//:openblas"
    ]
)

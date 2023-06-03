load("@rules_foreign_cc//foreign_cc:defs.bzl", "cmake")

package(default_visibility = ["//visibility:public"])

filegroup(
    name = "all_srcs",
    srcs = glob(["**"]),
    visibility = ["//visibility:public"],
)

cmake(
    name = "openblas",
    lib_source = "//:all_srcs",
    out_data_dirs = ["share"],
    out_static_libs = select({
        "@bazel_tools//src/conditions:darwin": ["libopenblas.a"],
        "@bazel_tools//src/conditions:linux": ["libopenblas.a"],
        "@bazel_tools//src/conditions:windows": ["openblas.lib"],
    }),
    visibility = ["//visibility:public"],
)

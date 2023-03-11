load("@rules_foreign_cc//foreign_cc:defs.bzl", "cmake")

package(default_visibility = ["//visibility:public"])

filegroup(
    name = "all_srcs",
    srcs = glob(["**"]),
    visibility = ["//visibility:public"],
)

cmake(
    name = "hello",
    build_args = ["-j8"],
    lib_source = "//:all_srcs",
    out_static_libs = ["libhello.a"],
)

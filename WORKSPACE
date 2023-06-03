load("@bazel_tools//tools/build_defs/repo:http.bzl", "http_archive", "http_file")
load("@bazel_tools//tools/build_defs/repo:git.bzl", "new_git_repository")

http_archive(
    name = "rules_foreign_cc",
    patches = ["//bazel:foreign_cc.patch"],
    sha256 = "2a4d07cd64b0719b39a7c12218a3e507672b82a97b98c6a89d38565894cf7c51",
    strip_prefix = "rules_foreign_cc-0.9.0",
    url = "https://github.com/bazelbuild/rules_foreign_cc/archive/refs/tags/0.9.0.tar.gz",
)

load("@rules_foreign_cc//foreign_cc:repositories.bzl", "rules_foreign_cc_dependencies")
rules_foreign_cc_dependencies()

new_git_repository(
    name = "hello",
    build_file = "//bazel:hello.BUILD",
    remote = "https://github.com/kishorenc/hello-cmake.git",
    commit = "cd1c702d0eba38c0c6130a6094257389427cfd4b"
)

new_git_repository(
    name = "hnsw",
    build_file = "//bazel:hnsw.BUILD",
    commit = "573ab84a7f7645f98778cbb181ba762c5d2f19b5",
    remote = "https://github.com/typesense/hnswlib.git",
)

http_archive(
    name = "com_github_xianyi_openblas",
    build_file = "//bazel:openblas.BUILD",
    sha256 = "5d9491d07168a5d00116cdc068a40022c3455bf9293c7cb86a65b1054d7e5114",
    strip_prefix = "OpenBLAS-0.3.23",
    url = "https://github.com/xianyi/OpenBLAS/archive/refs/tags/v0.3.23.tar.gz",
)

http_archive(
    name = "com_github_facebookresearch_faiss",
    build_file = "//bazel:faiss.BUILD",
    sha256 = "c08779395e30340a88ec4a963cac4e8959545a2a9d7f3b6eac01be701d1018f6",
    strip_prefix = "faiss-1.7.4",
    url = "https://github.com/facebookresearch/faiss/archive/v1.7.4.zip",
)

load("@bazel_tools//tools/build_defs/repo:http.bzl", "http_archive")
load("@bazel_tools//tools/build_defs/repo:git.bzl", "git_repository")

# 添加 libcurl 作为外部依赖
http_archive(
    name = "curl",
    urls = ["https://curl.se/download/curl-7.79.1.tar.gz"],  # 使用合适的版本
    strip_prefix = "curl-7.79.1",
)

http_archive(
    name = "rules_cuda",
    sha256 = "9039c00f5cfe0ac5ff1110d20706bc41d6dbd52c737f303e9a4cea0994ec19a9",
    strip_prefix = "rules_cuda-0503ead4724517db445796cbcdfc8400ce88c853",
    urls = ["https://github.com/cloudhan/rules_cuda/archive/0503ead4724517db445796cbcdfc8400ce88c853.tar.gz"],
)
load("@rules_cuda//cuda:repositories.bzl", "register_detected_cuda_toolchains", "rules_cuda_dependencies")
rules_cuda_dependencies()
register_detected_cuda_toolchains()

# Local cuda library.
new_local_repository(
    name = "cuda_includes",
    build_file_content = """
package(default_visibility = ["//visibility:public"])
cc_library(
    name = "cuda",
    hdrs = glob(["*.h", "**/*.h", "*.hpp", "**/*.hpp"])
)
""",
    path = "/usr/local/cuda/include",
)
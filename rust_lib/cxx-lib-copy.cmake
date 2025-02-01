# 该 CMake 脚本用于查找 Rust 构建结果中, 由 CXX 库产生的 `libcxxbridge1.a` 静态库
#
# 由于 Rust 构建时会将构建结果生成到一个具有 Hash 值后缀的目录下, 故需要递归查找该文件的具体位置,
# 并在找到后将文件复制到 Rust 的构建目录 (`target` 目录) 下

cmake_minimum_required(VERSION 3.20)

# 在 rust 生成库目标路径下, 查找 cxx 库编译输出静态库 (libcxxbridge1.a) 路径信息
file(GLOB_RECURSE cxx_lib_file "${rust_lib_target}/build/libcxxbridge1.a")
message(NOTICE "Find cxx lib \"${cxx_lib_file}\"")

# 将查找到的文件拷贝到 Rust 构建输出文件
file(COPY "${cxx_lib_file}" DESTINATION "${rust_lib_target}")
message(NOTICE "Copy \"${cxx_lib_file}\" into \"${rust_lib_target}\"")

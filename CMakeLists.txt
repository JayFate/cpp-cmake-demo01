cmake_minimum_required(VERSION 3.10)
project(MyProject VERSION 1.0)

# 设置 C++ 标准
set(CMAKE_CXX_STANDARD 11)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

# 包含头文件路径
include_directories(${PROJECT_SOURCE_DIR}/src/include)

# 为 VSCode 的 IntelliSense 导出编译命令
set(CMAKE_EXPORT_COMPILE_COMMANDS ON)

# 添加子目录
add_subdirectory(src)
add_subdirectory(tests)

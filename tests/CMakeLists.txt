# 使用 FetchContent 自动下载 GTest
include(FetchContent)
FetchContent_Declare(
  googletest
  GIT_REPOSITORY https://github.com/google/googletest.git
  GIT_TAG release-1.12.1
)
# 避免覆盖父项目的编译器/链接器设置
set(gtest_force_shared_crt ON CACHE BOOL "" FORCE)
FetchContent_MakeAvailable(googletest)

# 创建测试目标
add_executable(TestMyLib test_main.cpp)

# 链接库和 GTest 到测试目标
target_link_libraries(TestMyLib PRIVATE MyLib gtest gtest_main)

# 启用测试
enable_testing()
add_test(NAME TestMyLib COMMAND TestMyLib)

# 设置 IDE 包含路径（仅用于 IDE，不影响实际构建）
set_target_properties(TestMyLib PROPERTIES
    INTERFACE_INCLUDE_DIRECTORIES "${gtest_SOURCE_DIR}/include"
)

# 为 VSCode 的 IntelliSense 导出编译命令
set(CMAKE_EXPORT_COMPILE_COMMANDS ON)

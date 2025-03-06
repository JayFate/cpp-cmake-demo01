# 创建库目标
add_library(MyLib STATIC
    lib/module1.cpp
    lib/module2.cpp
)

# 指定库的头文件
target_include_directories(MyLib PUBLIC ${CMAKE_SOURCE_DIR}/src/include)

# 创建可执行文件目标
add_executable(MyExecutable main.cpp)

# 链接库到可执行文件
target_link_libraries(MyExecutable PRIVATE MyLib)

# 添加自定义命令 - 在构建完成后显示消息
add_custom_command(
    TARGET MyExecutable
    POST_BUILD
    COMMAND ${CMAKE_COMMAND} -E echo "构建完成！可执行文件位于: $<TARGET_FILE:MyExecutable>"
)

# 添加自定义目标 - 用于运行可执行文件
add_custom_target(run
    COMMAND $<TARGET_FILE:MyExecutable>
    DEPENDS MyExecutable
    WORKING_DIRECTORY ${CMAKE_CURRENT_BINARY_DIR}
    COMMENT "运行 MyExecutable..."
)

# 添加另一个自定义目标 - 用于清理并重新构建
add_custom_target(rebuild
    COMMAND ${CMAKE_COMMAND} --build ${CMAKE_BINARY_DIR} --target clean
    COMMAND ${CMAKE_COMMAND} --build ${CMAKE_BINARY_DIR}
    COMMENT "清理并重新构建项目..."
) 
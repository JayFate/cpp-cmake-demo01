# cpp-cmake-demo01

## 1、创建构建目录

在项目根目录下创建一个构建目录：

```
mkdir build
cd build
```

## 2、配置项目

在构建目录中运行 CMake 以配置项目：

```
cmake ..
```

## 3、编译项目

使用生成的构建系统文件进行编译，假设生成了 Makefile：

```
make
```

## 4、运行可执行文件

编译完成后，可以运行生成的可执行文件：

```
./MyExecutable
```

## 5、运行测试

使用生成的测试目标进行测试：

```
./TestMyLib
```

## 6、使用自定义命令和目标

### 6.1 自定义命令

在 src/CMakeLists.txt 文件中添加自定义命令：

```
add_custom_command(
    TARGET MyExecutable
    POST_BUILD
    COMMAND ${CMAKE_COMMAND} -E echo "Build complete!"
)
```

### 6.2 自定义目标

在 src/CMakeLists.txt 文件中添加自定义目标：

```
add_custom_target(run
    COMMAND ${CMAKE_BINARY_DIR}/MyExecutable
    DEPENDS MyExecutable
)
```

运行自定义目标：

```
make run
```

## 7、跨平台和交叉编译

### 7.1 指定平台

如果需要指定平台进行构建，可以在运行 CMake 时指定平台：

```
cmake -DCMAKE_SYSTEM_NAME=Linux ..
```

### 7.2 使用工具链文件

创建一个工具链文件 toolchain.cmake：

```
set(CMAKE_SYSTEM_NAME Linux)
set(CMAKE_SYSTEM_PROCESSOR arm)
```

使用工具链文件进行构建：

```
cmake -DCMAKE_TOOLCHAIN_FILE=toolchain.cmake ..
```

### .gitignore

```
build
```

### CMakeLists.txt

```cmake
cmake_minimum_required(VERSION 3.10)
project(MyProject VERSION 1.0)

# 设置 C++ 标准
set(CMAKE_CXX_STANDARD 11)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

# 包含头文件路径
# include_directories(${PROJECT_SOURCE_DIR}/src/include)

# 添加 src 子目录
add_subdirectory(src)
add_subdirectory(tests)
```

### src/CMakeLists.txt

```cmake
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

```

### src/include/mylib.h

```cpp
#ifndef MYLIB_H
#define MYLIB_H

namespace MyLib {
    // 模块1: 基本运算函数
    double add(double a, double b);
    double subtract(double a, double b);
    
    // 模块2: 高级运算函数
    double multiply(double a, double b);
    double divide(double a, double b);
    double power(double base, double exponent);
}

#endif // MYLIB_H 
```

### src/lib/module1.cpp

```cpp
#include "mylib.h"

namespace MyLib {
    // 加法函数
    double add(double a, double b) {
        return a + b;
    }
    
    // 减法函数
    double subtract(double a, double b) {
        return a - b;
    }
} 
```

### src/lib/module2.cpp

```cpp
#include "mylib.h"
#include <cmath>
#include <stdexcept>

namespace MyLib {
    // 乘法函数
    double multiply(double a, double b) {
        return a * b;
    }
    
    // 除法函数
    double divide(double a, double b) {
        if (b == 0) {
            throw std::invalid_argument("除数不能为零");
        }
        return a / b;
    }
    
    // 幂运算函数
    double power(double base, double exponent) {
        return std::pow(base, exponent);
    }
} 
```

### src/main.cpp

```cpp
#include <iostream>
#include "mylib.h"

int main() {
    std::cout << "欢迎使用计算器库!" << std::endl;
    
    // 测试基本运算
    double a = 10.0, b = 5.0;
    std::cout << a << " + " << b << " = " << MyLib::add(a, b) << std::endl;
    std::cout << a << " - " << b << " = " << MyLib::subtract(a, b) << std::endl;
    
    // 测试高级运算
    std::cout << a << " * " << b << " = " << MyLib::multiply(a, b) << std::endl;
    std::cout << a << " / " << b << " = " << MyLib::divide(a, b) << std::endl;
    std::cout << a << " ^ " << b << " = " << MyLib::power(a, 2) << std::endl;
    
    return 0;
} 
```

### tests/CMakeLists.txt

```cmake
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
```

### tests/test_main.cpp

```cpp
#include <gtest/gtest.h>
#include "mylib.h"

// 测试模块1
TEST(Module1Test, Addition) {
    EXPECT_DOUBLE_EQ(5.0, MyLib::add(2.0, 3.0));
    EXPECT_DOUBLE_EQ(0.0, MyLib::add(1.0, -1.0));
}

TEST(Module1Test, Subtraction) {
    EXPECT_DOUBLE_EQ(2.0, MyLib::subtract(5.0, 3.0));
    EXPECT_DOUBLE_EQ(-2.0, MyLib::subtract(3.0, 5.0));
}

// 测试模块2
TEST(Module2Test, Multiplication) {
    EXPECT_DOUBLE_EQ(6.0, MyLib::multiply(2.0, 3.0));
    EXPECT_DOUBLE_EQ(-6.0, MyLib::multiply(2.0, -3.0));
}

TEST(Module2Test, Division) {
    EXPECT_DOUBLE_EQ(2.0, MyLib::divide(6.0, 3.0));
    EXPECT_DOUBLE_EQ(0.5, MyLib::divide(1.0, 2.0));
    EXPECT_THROW(MyLib::divide(1.0, 0.0), std::invalid_argument);
}

TEST(Module2Test, Power) {
    EXPECT_DOUBLE_EQ(9.0, MyLib::power(3.0, 2.0));
    EXPECT_DOUBLE_EQ(1.0, MyLib::power(5.0, 0.0));
}

// 主测试入口
int main(int argc, char **argv) {
    ::testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
} 
```


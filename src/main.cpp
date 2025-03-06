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
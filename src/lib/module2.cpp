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
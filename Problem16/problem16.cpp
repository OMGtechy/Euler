// https://projecteuler.net/problem=16
// Problem 16
//
// 215 = 32768 and the sum of its digits is 3 + 2 + 7 + 6 + 8 = 26.
//
// What is the sum of the digits of the number 2^1000?

#include <iostream>
#include <cassert>
#include <cmath>
#include <string>

double solution(int32_t powerOfTwo) {
    // doubles can represent powers of 2 up to 2^1024
    assert(powerOfTwo < 1024);

    int32_t sum = 0;
    auto asString = std::to_string(std::pow(2, powerOfTwo));
    for(char digit : asString) {
        if (digit != '.') {
            sum += digit - '0';
        }
    }

    return sum;
}

int main() {
    std::cout << solution(1000) << std::endl;
}

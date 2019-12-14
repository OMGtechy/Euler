// https://projecteuler.net/problem=6
// Sum square difference
// Problem 6
//
// The sum of the squares of the first ten natural numbers is,
// 1^2 + 2^2 + ... + 10^2 = 385
//
// The square of the sum of the first ten natural numbers is,
// (1 + 2 + ... + 10)^2 = 55^2 = 3025
//
// Hence the difference between the sum of the squares of the first ten natural numbers and the square of the sum is 3025 − 385 = 2640.
//
// Find the difference between the sum of the squares of the first one hundred natural numbers and the square of the sum.

#include <iostream>
#include <cstdint>
#include <cassert>
#include <cmath>

int32_t sumOfSquares(const int32_t limit) {
	int32_t sum = 0;
	for (int32_t i = 0; i <= limit; ++i) {
		sum += static_cast<int32_t>(std::pow(i, 2));
	}

	return sum;
}

int32_t squareOfSums(const int32_t limit) {
	int32_t sum = 0;
	for (int32_t i = 0; i <= limit; ++i) {
		sum += i;
	}

	return static_cast<int32_t>(std::pow(sum, 2));
}

int main() {
	assert(sumOfSquares(10) == 385);
	assert(squareOfSums(10) == 3025);

	std::cout << (squareOfSums(100) - sumOfSquares(100)) << std::endl;
}

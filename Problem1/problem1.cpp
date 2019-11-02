// https://projecteuler.net/problem=1
// Multiples of 3 and 5
// Problem 1
//
// If we list all the natural numbers below 10 that are multiples of 3 or 5,
// we get 3, 5, 6 and 9. The sum of these multiples is 23.
//
// Find the sum of all the multiples of 3 or 5 below 1000. 

#include <cstdint>
#include <iostream>

constexpr int64_t solution(const int64_t limit) {
	int64_t sum_of_multiples = 0;
	for (int64_t i = 0; i < limit; ++i) {
		if (i % 3 == 0 || i % 5 == 0) {
			sum_of_multiples += i;
		}
	}

	return sum_of_multiples;
}

int main() {
	// as per example in question
	static_assert(solution(10) == 23);

	std::cout << solution(1000) << std::endl;
}
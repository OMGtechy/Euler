// https://projecteuler.net/problem=7
// 10001st prime
// Problem 7
//
// By listing the first six prime numbers: 2, 3, 5, 7, 11, and 13, we can see that the 6th prime is 13.
//
// What is the 10001st prime number?

#include <iostream>
#include <vector>
#include <cassert>

#include "eulib_primes.h"

int64_t solution(const size_t limit) {
	const auto primes = eulib::getPrimes<int64_t>([limit](const auto& primes) { return primes.size() >= limit; });
	auto iter = primes.cbegin();
	for (size_t i = 0; i < limit; ++i, ++iter);
	return *iter;
}

int main() {
	assert(solution(6) == 13);

	std::cout << solution(10001) << std::endl;
}
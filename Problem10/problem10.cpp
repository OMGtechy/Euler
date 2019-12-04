// https://projecteuler.net/problem=10
// Summation of primes
// Problem 10
//
// The sum of the primes below 10 is 2 + 3 + 5 + 7 = 17.
//
// Find the sum of all the primes below two million.

#include <iostream>
#include <numeric>
#include <functional>

#include "eulib_primes.h"

int64_t solution(int64_t limit) {
	const auto primes = eulib::getPrimes([limit](const auto& primes) { return primes.back() >= limit; });
	return std::accumulate(primes.cbegin(), primes.cend() - 1 /* the last will be over the limit, hence - 1*/, int64_t(0));
}

int main() {
	std::cout << solution(2'000'000) << std::endl;
}
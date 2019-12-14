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
	const auto primes = eulib::getPrimes<int64_t>([limit](const auto& primes) { return primes.empty() ? false : *primes.crbegin() >= limit; });
	int64_t sum = 0;
	for (auto prime : primes) {
                if (prime < limit) {
		    sum += prime;
                }
	}

	return sum;
}

int main() {
	std::cout << solution(2'000'000) << std::endl;
}

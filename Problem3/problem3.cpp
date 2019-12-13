// https://projecteuler.net/problem=3
// Largest prime factor
// Problem 3
//
// The prime factors of 13195 are 5, 7, 13 and 29.
//
// What is the largest prime factor of the number 600851475143?

#include <cstdint>
#include <cassert>
#include <vector>
#include <iostream>

#include "eulib_primes.h"

int64_t solution(int64_t limit) {
	const auto primeFactors = eulib::getPrimeFactors(limit);
	const auto lastIter = primeFactors.crbegin();

	// return 0 if there aren't any
	return lastIter == primeFactors.crend() ? 0 : lastIter->first;
}

int main() {
	// as per question, largest prime factor of 13195 is 29
	assert(solution(13195) == 29);

	std::cout << solution(600851475143) << std::endl;
}
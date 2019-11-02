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

int64_t solution(int64_t limit) {
	int64_t factor = 2;
	int64_t largestPrimeFactor = 0;

	std::vector<int64_t> primes;
	primes.push_back(factor);

	while (limit >= factor) {
		if (limit % factor == 0) {
			limit /= factor;

			assert(factor > largestPrimeFactor);
			largestPrimeFactor = factor;
		}

		// find the next prime
		bool primeFound = false;
		int64_t candidate = factor;
		while (!primeFound) {
			candidate += 1;
			primeFound = true;
			for (auto prime : primes) {
				if (candidate % prime == 0) {
					primeFound = false;
					break;
				}
			}
		}

		primes.push_back(candidate);
		factor = candidate;
	}

	return largestPrimeFactor;
}

int main() {
	// as per question, largest prime factor of 13195 is 29
	assert(solution(13195) == 29);

	std::cout << solution(600851475143) << std::endl;
}
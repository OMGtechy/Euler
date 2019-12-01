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

int64_t solution(const int64_t limit) {
	int64_t candidate = 1;
	std::vector<int64_t> primes;
	primes.reserve(limit);
	primes.push_back(2);

	while (primes.size() != limit) {
		candidate += 2;
		bool isPrime = true;
		for (auto prime : primes) {
			if (candidate % prime == 0) {
				isPrime = false;
				break;
			}
		}

		if (isPrime) {
			primes.push_back(candidate);
		}
	}

	return primes.back();
}

int main() {
	assert(solution(6) == 13);

	std::cout << solution(10001) << std::endl;
}
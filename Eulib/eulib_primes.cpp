#include "eulib_primes.h"

std::vector<int64_t> eulib::getPrimes(std::function<bool(const std::vector<int64_t>&)> stopCondition) {
	int64_t candidate = 1;
	std::vector<int64_t> primes;
	primes.push_back(2);

	while (!stopCondition(primes)) {
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

	return primes;
}
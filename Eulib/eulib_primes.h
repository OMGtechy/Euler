#pragma once

#include <set>
#include <functional>
#include <map>

namespace eulib {
	template <typename IntegerType>
	std::set<IntegerType> getPrimes(std::function<bool(const std::set<IntegerType>&)> stopCondition, std::set<IntegerType> knownPrimes = {}) {
		if (stopCondition(knownPrimes)) {
			return knownPrimes;
		}

		std::set<IntegerType> primes = std::move(knownPrimes);

		// sieve of eratosthenes
		// create candidates up to limit, limit chose because it does about this many almost instantly
		constexpr size_t sieveSize = 2 << 14;

		// don't use bool here because std::vector<bool> is just ... weird
		std::vector<int8_t> candidates(sieveSize, false);

		// for each number up to and including square root of limit
		size_t n = 2;
		for (; n < static_cast<size_t>(std::ceil(std::sqrt(sieveSize)) + 1); ++n) {
			// true is used to mean "is not prime"
			if (candidates[n]) {
				continue;
			}

			// eliminate numbers that are multiples
			for (size_t multiple = n + n; multiple < sieveSize; multiple += n) {
				candidates[multiple] = true;
			}

			primes.insert(n);
			if (stopCondition(primes)) {
				return primes;
			}
		}

		// others are primes
		for (; n < sieveSize; ++n) {
			if (!candidates[n]) {
				primes.insert(n);
				if (stopCondition(primes)) {
					return primes;
				}
			}
		}

		IntegerType candidate = 1;
		while (!stopCondition(primes)) {
			// fallback in case the sieve hasn't covered
			candidate += 2;
			bool isPrime = true;
			for (auto prime : primes) {
				if (candidate % prime == 0) {
					isPrime = false;
					break;
				}
			}

			if (isPrime) {
				primes.insert(candidate);
			}
		}

		return primes;
	}

	template <typename IntegerType>
	std::map<IntegerType, IntegerType> getPrimeFactors(IntegerType n, const std::set<IntegerType>& knownPrimes = {}) {
		std::map<IntegerType, IntegerType> primeFactors;

		std::set<IntegerType> primes = knownPrimes;
		const auto getMorePrimes = [&primes]() { return getPrimes<IntegerType>([newPrimesRequested = primes.size() + static_cast<size_t>(100)](const auto& newPrimes) { return newPrimes.size() >= newPrimesRequested; }, primes); };

		typename decltype(primes)::iterator nextPrimeIter = primes.cbegin();
		IntegerType factor = 0;

		while (true) {
			for (; nextPrimeIter != primes.cend(); ++nextPrimeIter) {
				factor = *nextPrimeIter;
				while (n % factor == 0) {
					n /= factor;
					primeFactors[factor] += 1;
				}
			}

			if (n < factor) {
				break;
			}

			const auto distance = static_cast<size_t>(std::distance(primes.cbegin(), nextPrimeIter));

			// the number primes aquired each time is arbitrary but seems to work well enough
			primes = getMorePrimes();

			nextPrimeIter = primes.begin();
			for (size_t i = 0; i < distance; ++i, ++nextPrimeIter);
		}

		return primeFactors;
	}
}
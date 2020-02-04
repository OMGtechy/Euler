#pragma once

#include <set>
#include <functional>
#include <map>
#include <vector>
#include <cmath>

// implementation detail, don't use this outside of eulib
// requires a integer called candidate (next to be checked) and a set of primes called primes
#define EULIB_PRIME_MACRO(CONDITION) \
do { \
    candidate += 2; \
    bool isPrime = true; \
    for (auto prime : primes) { \
        if (candidate % prime == 0) { \
            isPrime = false; \
            break; \
        } \
    } \
\
    if (isPrime) { \
        primes.insert(candidate); \
    } \
} while(CONDITION)

namespace eulib {
        template<typename IntegerType> using PrimeCollection = std::set<IntegerType>;

        size_t estimateLimitNeededForNPrimes(const size_t n) {
            return static_cast<size_t>(std::ceil(std::log(n) * n));
        }

        template <typename IntegerType>
        PrimeCollection<IntegerType> sieveOfEratosthenes(const size_t lastNumberToCheck, PrimeCollection<IntegerType> primes = {}) {
            const auto sieveSize = lastNumberToCheck;
            const auto limit = static_cast<IntegerType>(std::ceil(std::sqrt(sieveSize))) + 1;

            // don't use bool here because std::vector<bool> is just ... weird
            std::vector<int8_t> candidates(sieveSize + 1, false);

            // for each number up to and including square root of limit
            IntegerType n = 2;
            for (; n < limit; ++n) {
                // true is used to mean "is not prime"
                if (candidates[n]) {
                    continue;
                }

                // eliminate numbers that are multiples
                for (size_t multiple = static_cast<size_t>(n) + static_cast<size_t>(n); multiple < sieveSize; multiple += n) {
                    candidates[multiple] = true;
                }

                primes.insert(n);
            }

            // others are primes
            for (; n < sieveSize; ++n) {
                if (!candidates[n]) {
                    primes.insert(n);
                }
            }

            return primes;
        }

        template <typename IntegerType>
        PrimeCollection<IntegerType> getNPrimes(const size_t n, PrimeCollection<IntegerType> knownPrimes = {}) {
            if (knownPrimes.size() >= n) {
                return knownPrimes;
            }

            auto primes = sieveOfEratosthenes<IntegerType>(estimateLimitNeededForNPrimes(n * 2), knownPrimes);

            // there will be more than 0 primes by this point, otherwise .size() >= n would have triggered earlier
            IntegerType candidate = *primes.crbegin();

            // fallback in case the sieve hasn't covered
            EULIB_PRIME_MACRO(primes.size() < n);

            return primes;
	}

        template <typename IntegerType>
        PrimeCollection<IntegerType> getPrimesUpTo(const IntegerType limit, PrimeCollection<IntegerType> knownPrimes = {}) {
            if ((!knownPrimes.empty()) && (*knownPrimes.crbegin() >= limit)) {
                return knownPrimes;
            }

            auto primes = sieveOfEratosthenes(limit, knownPrimes);
            auto candidate = primes.size() < 2 ? IntegerType(1) : *primes.crbegin();

            // fallback in case the sieve hasn't covered
            EULIB_PRIME_MACRO(*primes.crbegin() < limit);

            return primes;
        }

	template <typename IntegerType>
	std::map<IntegerType, IntegerType> getPrimeFactors(IntegerType n) {
            if (n < 2) {
                return {};
            }

            std::map<IntegerType, IntegerType> primeFactors;

            const auto maxDivisorToCheck = n;
            PrimeCollection<IntegerType> primes;
            auto primeIter = primes.cbegin();

            while (true) {
                const auto distance = static_cast<size_t>(std::distance(primes.cbegin(), primeIter));
                primes = getNPrimes(primes.size() + 100, primes);
                primeIter = primes.cbegin();
                for (size_t i = 0; i < distance; ++i, ++primeIter);

                IntegerType prime;
                for (; primeIter != primes.cend() && n >= *primeIter; ++primeIter) {
                    prime = *primeIter;
                    if (prime > maxDivisorToCheck) {
                        break;
                    }

                    while (n % prime == 0) {
                        n /= prime;
                        primeFactors[prime] += 1;
                    }
                }

                if (prime > n) {
                    break;
                } 
            }

            return primeFactors;
	}
}

// https://projecteuler.net/problem=9
// Special Pythagorean triplet
// Problem 9
//
// A Pythagorean triplet is a set of three natural numbers, a < b < c, for which,
// a^2 + b^2 = c^2
//  
// For example, 32 + 42 = 9 + 16 = 25 = 52.
//   
// There exists exactly one Pythagorean triplet for which a + b + c = 1000.
// Find the product abc.

#include <iostream>
#include <cstdint>
#include <algorithm>

int32_t solution(const int32_t targetNumber) {

	for (int32_t a = 0; a < targetNumber; ++a) {
		const auto aSquared = static_cast<int32_t>(std::pow(a, 2));

		// a must be less than b, hence a + 1
		for (int32_t b = a + 1; b < targetNumber; ++b) {
			const auto bSquared = static_cast<int32_t>(std::pow(b, 2));

			// b must be less than c, hence b + 1
			for (int32_t c = b + 1; c < targetNumber; ++c) {
				const auto cSquared = static_cast<int32_t>(std::pow(c, 2));

				if (a + b + c == targetNumber && aSquared + bSquared == cSquared) {
					return a * b * c;
				}
			}
		}
	}

	// in case there is no such "special pythagorean triplet"
	return -1;
}

int main() {
	std::cout << solution(1000) << std::endl;
}
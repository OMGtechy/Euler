// https://projecteuler.net/problem=5
// Smallest multiple
// Problem 5
//
// 2520 is the smallest number that can be divided by each of the numbers from 1 to 10 without any remainder.
//
// What is the smallest positive number that is evenly divisible by all of the numbers from 1 to 20 ?

#include <iostream>
#include <cstdint>
#include <cassert>

constexpr int32_t solution(const int32_t limit) {
	bool found = false;
	int32_t candidate = 2;
	while(!found) {
		found = true;
		for (int32_t divisor = 1; divisor <= limit; ++divisor) {
			if (candidate % divisor != 0) {
				found = false;
				candidate += 2;
				break;
			}
		}
	}

	return candidate;
}

int main() {
	assert(solution(10) == 2520);

	std::cout << solution(20) << std::endl;
}
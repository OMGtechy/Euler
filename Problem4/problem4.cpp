// https://projecteuler.net/problem=4
// Largest palindrome product
// Problem 4
//
// A palindromic number reads the same both ways. The largest palindrome made from the product of two 2 digit numbers is 9009 = 91 × 99.
//
// Find the largest palindrome made from the product of two 3 digit numbers.
// NOTE: I could have done it with strings, but where's the fun in that?

#include <cstdint>
#include <iostream>
#include <cmath>
#include <cassert>
#include <algorithm>

int32_t digitsInNumber(const int32_t number) {
	return static_cast<int32_t>(std::floor(std::log10(std::abs(number)))) + 1;
}

int32_t getColumnValue(const int32_t number, const int32_t column) {
	const auto powerAbove = static_cast<int32_t>(std::floor(std::pow(10, column)));
	const auto power = powerAbove / 10;
	const auto lowerValues = number % powerAbove;
	const auto coefficientOfPower = lowerValues / power;
	return coefficientOfPower * power;
}

bool isPalindromeNumber(int32_t number) {
	auto numberOfDigitsLeft = digitsInNumber(number);
	
	while (numberOfDigitsLeft > 1) {

		auto highestDigit = getColumnValue(number, numberOfDigitsLeft) / static_cast<int32_t>(std::floor(std::pow(10, numberOfDigitsLeft - 1)));
		auto lowestDigit = number % 10;

		if (highestDigit != lowestDigit) {
			return false;
		}

		number -= getColumnValue(number, numberOfDigitsLeft);
		number /= 10;
		numberOfDigitsLeft -= 2;
	}

	return true;
}

int32_t solution(const int32_t digits) {
	const auto maxWithNDigits = static_cast<int32_t>(std::floor(std::pow(10, digits))) - 1;
	const auto minWithNDigits = static_cast<int32_t>(std::floor(std::pow(10, digits - 1)));

	int32_t largestPalindromeNumber = 0;

	for (int32_t leftOperand = maxWithNDigits; leftOperand > minWithNDigits; --leftOperand) {
		for (int32_t rightOperand = maxWithNDigits; rightOperand > minWithNDigits; --rightOperand) {
			const auto product = leftOperand * rightOperand;

			if (product < largestPalindromeNumber) {
				break;
			}

			if (isPalindromeNumber(product)) {
				largestPalindromeNumber = std::max(largestPalindromeNumber, product);
			}
		}
	}

	// if one isn't found, it'll just return 0
	return largestPalindromeNumber;
}

int main() {
	// questions states largest 2 digit product 9009
	assert(solution(2) == 9009);

	assert(digitsInNumber(1) == 1);
	assert(digitsInNumber(10) == 2);
	assert(digitsInNumber(100) == 3);
	assert(digitsInNumber(9) == 1);
	assert(digitsInNumber(99) == 2);
	assert(digitsInNumber(999) == 3);
	assert(digitsInNumber(-1) == 1);
	assert(digitsInNumber(-10) == 2);
	assert(digitsInNumber(-100) == 3);
	assert(digitsInNumber(-9) == 1);
	assert(digitsInNumber(-99) == 2);
	assert(digitsInNumber(-999) == 3);

	assert(getColumnValue(1000, 3) == 0);
	assert(getColumnValue(1010, 3) == 0);
	assert(getColumnValue(1100, 3) == 100);
	assert(getColumnValue(1001, 3) == 0);
	assert(getColumnValue(54321, 1) == 1);
	assert(getColumnValue(54321, 2) == 20);
	assert(getColumnValue(54321, 3) == 300);
	assert(getColumnValue(-1000, 3) == 0);
	assert(getColumnValue(-1010, 3) == 0);
	assert(getColumnValue(-1100, 3) == -100);
	assert(getColumnValue(-1001, 3) == 0);
	assert(getColumnValue(-54321, 1) == -1);
	assert(getColumnValue(-54321, 2) == -20);
	assert(getColumnValue(-54321, 3) == -300);

	assert(isPalindromeNumber(1));
	assert(isPalindromeNumber(-1));
	assert(isPalindromeNumber(101));
	assert(isPalindromeNumber(-101));
	assert(isPalindromeNumber(1654561));
	assert(isPalindromeNumber(-1654561));
	assert(isPalindromeNumber(99999));
	assert(isPalindromeNumber(-99999));

	assert(!isPalindromeNumber(12));
	assert(!isPalindromeNumber(-12));
	assert(!isPalindromeNumber(1212));
	assert(!isPalindromeNumber(-1212));
	assert(!isPalindromeNumber(16554561));
	assert(!isPalindromeNumber(-16554561));
	assert(!isPalindromeNumber(10000));
	assert(!isPalindromeNumber(-10000));
	assert(!isPalindromeNumber(10100));
	assert(!isPalindromeNumber(-10100));
	assert(!isPalindromeNumber(900099));
	assert(!isPalindromeNumber(-900099));

	std::cout << solution(3) << std::endl;
}
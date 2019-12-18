// https://projecteuler.net/problem=15
// Problem 15
//
// Starting in the top left corner of a 2×2 grid, and only being able to move to the right and down,
// there are exactly 6 routes to the bottom right corner.
//
// How many such routes are there through a 20×20 grid?

#include <iostream>
#include <cstdint>
#include <cassert>

#include "bitter_variable_unsigned_integer.hpp"

// Calculates how many times can "k" items be chosen from "n" total
bitter::VariableUnsignedInteger nChooseK(int32_t n, int32_t k) {
    if (k > n) {
        // doesn't make sense, you can't choose more items than exist
        bitter::VariableUnsignedInteger result(1);
        result = 1;
        return result;
    }

    // Formula for this is:
    //
    //     n!
    // ----------
    // (n - k)!k!
    //
    // However, calculating such factorials will create huge numbers since
    // I plan on using values such as 40 for n and/or k, which is 8.15915283 x 10^47
    // log2 of that is nearly 160; one would need a 160 bit integer for that.
    // I like powers of 2, so 256 bit integers are used

    // I could probably solve this by canceling out fractions a bit or doing the
    // whole problem iteratively, but this seemed like a nice oppurtunity to try
    // out my own BigInt implementation that's been sat on GitHub for a while.
    // Of course, outside of these toy projects ... writing your own BigInt
    // it's a great idea most of the time.

    // n!
    bitter::VariableUnsignedInteger numerator{256 / 8};
    numerator = 1;
    for(uint64_t i = 1; i <= n; ++i) {
        numerator *= i;
    }

    // k!
    bitter::VariableUnsignedInteger denominator{256 / 8};
    denominator = 1;
    for(uint64_t i = 1; i <= k; ++i) {
        denominator *= i;
    }

    // (n - k)!
    for(uint64_t i = 1; i <= (n - k); ++i) {
        denominator *= i;
    }

    return numerator / denominator;
}

bitter::VariableUnsignedInteger solution(uint64_t n) {
    // when calculating the first few values of the sequence by hand,
    // it turned out to be something called a "binomial[2n/n]" sequence.
    // This function computes that for some value of n.
    return nChooseK(2 * n, n);
}

int main() {
    assert(nChooseK(2, 1) == 2);
    assert(nChooseK(2, 2) == 1);
    assert(nChooseK(3, 1) == 3);
    assert(nChooseK(3, 2) == 3);
    assert(nChooseK(3, 3) == 1);
    assert(nChooseK(4, 1) == 4);
    assert(nChooseK(4, 2) == 6);
    assert(nChooseK(4, 3) == 4);
    assert(nChooseK(4, 4) == 1);

    assert(solution(2) == 6);

    std::cout << solution(20) << std::endl;
}

// https://projecteuler.net/problem=14
// Problem 14
//
// The following iterative sequence is defined for the set of positive integers:
//
// n → n/2 (n is even)
// n → 3n + 1 (n is odd)
//
// Using the rule above and starting with 13, we generate the following sequence:
// 13 → 40 → 20 → 10 → 5 → 16 → 8 → 4 → 2 → 1
//
// It can be seen that this sequence (starting at 13 and finishing at 1) contains 10 terms.
// Although it has not been proved yet (Collatz Problem), it is thought that all starting numbers finish at 1.
//
// Which starting number, under one million, produces the longest chain?
//
// NOTE: Once the chain starts the terms are allowed to go above one million.

#include <iostream>

constexpr int64_t calculateNextNumberInSequence(int64_t n) {
    if (n % 2 == 0) {
        // this is safe since we just checked it's divisible by 2
        return n / 2;
    }

    return (3 * n) + 1;
}

constexpr int64_t calculateSequenceLength(int64_t n) {
    int64_t sequenceLength = 1;
    while(n != 1) {
        n = calculateNextNumberInSequence(n);
        ++sequenceLength;
    }

    return sequenceLength;
}

constexpr int64_t solution() {
    struct Candidate {
        int64_t n = 0;
        int64_t sequenceLength = 0;
    } candidate;
    for(int64_t n = 1; n < 1'000'000; ++n) {
        const auto sequenceLength = calculateSequenceLength(n);
        if (candidate.sequenceLength < sequenceLength) {
            candidate = { n, sequenceLength };
        }
    }

    return candidate.n;
}

int main() {
    std::cout << solution() << std::endl;
}

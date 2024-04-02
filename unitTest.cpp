#include <iostream>
#include <bitset>
#include <cmath>
#include <cstring>
#include <vector>

void printBitsInReverse(std::bitset<32> bits) {
    for (int i = 31; i >= 0; --i) {
        std::cout << bits[i];
    }
    std::cout << std::endl;
}

// Extracted core logic into a testable function
bool testOverflowDetection(float loopBound, float loopIncrement) {
    unsigned int* boundBitsPtr = reinterpret_cast<unsigned int*>(&loopBound);
    unsigned int* incrementBitsPtr = reinterpret_cast<unsigned int*>(&loopIncrement);

    std::bitset<32> boundBits(*boundBitsPtr);
    std::bitset<32> incrementBits(*incrementBitsPtr);

    unsigned long exponentBound = (boundBits.to_ulong() >> 23) & 0xFF;
    unsigned long exponentIncrement = (incrementBits.to_ulong() >> 23) & 0xFF;

    int exponentDifference = exponentBound - exponentIncrement;

    return exponentDifference >= 24;
}

// Main program adapted for testing
int main() {
    // Test cases
    struct TestCase {
        float loopBound;
        float loopIncrement;
        bool expectedOverflow;
    };

    std::vector<TestCase> testCases = {
        {1e30f, 1e6f, false}, // No overflow expected
        {1e38f, 1e20f, true}, // Overflow expected
        // Add more test cases, especially edge cases
    };

    for (const auto& test : testCases) {
        bool overflowDetected = testOverflowDetection(test.loopBound, test.loopIncrement);
        std::cout << "Testing with loopBound = " << test.loopBound
                  << ", loopIncrement = " << test.loopIncrement << " -> ";
        std::cout << (overflowDetected ? "Overflow detected." : "No overflow.") << std::endl;

        if (overflowDetected != test.expectedOverflow) {
            std::cout << "Test failed!" << std::endl;
        } else {
            std::cout << "Test passed!" << std::endl;
        }
    }

    return 0;
}

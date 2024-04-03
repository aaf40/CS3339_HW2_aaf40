#include<iostream>
#include<string>
#include<bitset>

int main(int argc, char* argv[]) {
    if (argc != 3) {
        std::cout << "Error: Program requires exactly two floating-point values as input." << std::endl;
        return 1;
    }

    float loopBound = std::stof(argv[1]);
    float loopIncrement = std::stof(argv[2]);

    unsigned int* loopBoundBitsPtr = reinterpret_cast<unsigned int*>(&loopBound);
    std::bitset<32> loopBoundBits(*loopBoundBitsPtr);

    unsigned int* loopIncrementBitsPtr = reinterpret_cast<unsigned int*>(&loopIncrement);
    std::bitset<32> loopIncrementBits(*loopIncrementBitsPtr);

    std::cout << "Loop Bound Bits: " << loopBoundBits << std::endl;
    std::cout << "Loop Increment Bits: " << loopIncrementBits << std::endl;

    // Extracting the exponent bits and converting them to an integer
    unsigned int loopBoundExponent = ((*loopBoundBitsPtr >> 23) & 0xFF);
    unsigned int loopIncrementExponent = ((*loopIncrementBitsPtr >> 23) & 0xFF);

    // Calculating the difference in exponents
    int exponentDifference = loopBoundExponent - loopIncrementExponent;

    // Determining potential for overflow
    if (exponentDifference >= 24) {
        std::cout << "Warning: Possible overflow!" << std::endl;
        // Placeholder for calculating and displaying the overflow threshold
    } else {
        std::cout << "No overflow detected." << std::endl;
    }

    return 0;
}

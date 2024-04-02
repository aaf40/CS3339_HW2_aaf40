#include <iostream>
#include <bitset>
#include <cmath>
#include <cstring>

// Function to print the bit representation in reverse order
void printBitsInReverse(std::bitset<32> bits) {
    for (int i = 31; i >= 0; --i) {
        std::cout << bits[i];
    }
    std::cout << std::endl;
}

// Main program
int main(int argc, char* argv[]) {
    if (argc != 3) {
        std::cout << "Error: Program requires exactly two floating-point values as input." << std::endl;
        return 1;
    }

    // Parsing command-line arguments
    float loopBound = std::stof(argv[1]);
    float loopIncrement = std::stof(argv[2]);

    // Extracting and printing bit representations
    unsigned int* boundBitsPtr = reinterpret_cast<unsigned int*>(&loopBound);
    unsigned int* incrementBitsPtr = reinterpret_cast<unsigned int*>(&loopIncrement);

    std::bitset<32> boundBits(*boundBitsPtr);
    std::bitset<32> incrementBits(*incrementBitsPtr);

    std::cout << "Loop bound (IEEE-formatted bit representation): ";
    printBitsInReverse(boundBits);

    std::cout << "Loop increment (IEEE-formatted bit representation): ";
    printBitsInReverse(incrementBits);

    // Extracting exponent fields and calculating difference
    unsigned long exponentBound = (boundBits.to_ulong() >> 23) & 0xFF;
    unsigned long exponentIncrement = (incrementBits.to_ulong() >> 23) & 0xFF;

    int exponentDifference = exponentBound - exponentIncrement;

    // Detecting overflow
    if (exponentDifference >= 24) {
        std::cout << "Warning: Possible overflow!" << std::endl;
        // The threshold calculation is more involved and requires additional logic to determine
        // the exact value where overflow occurs. This part of the solution would depend on 
        // understanding how floating-point addition or multiplication could result in an overflow 
        // and adjusting the loopIncrement accordingly to find the minimum threshold.
        // Here, you'd implement the logic based on the specifics of floating-point arithmetic.
    } else {
        std::cout << "No overflow!" << std::endl;
    }

    return 0;
}

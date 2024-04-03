#include<iostream>
#include<string>
#include<bitset>

void printFormattedBits(unsigned int bits) {
    std::bitset<32> bitset(bits);
    std::string bitString = bitset.to_string();
    std::cout << bitString.substr(0, 1) << " ";
    std::cout <<  bitString.substr(1, 8) << " ";
    std::cout <<  bitString.substr(9, 23) << std::endl;
}

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
    printFormattedBits(*loopBoundBitsPtr);
    std::cout << "Loop Increment Bits: " << loopIncrementBits << std::endl;
    printFormattedBits(*loopIncrementBitsPtr);

    unsigned int loopBoundExponent = ((*loopBoundBitsPtr >> 23) & 0xFF);
    unsigned int loopIncrementExponent = ((*loopIncrementBitsPtr >> 23) & 0xFF);

    int exponentDifference = loopBoundExponent - loopIncrementExponent;

    if (exponentDifference >= 24) {
        std::cout << "Warning: Possible overflow!" << std::endl;

        unsigned int thresholdExponent = loopBoundExponent - 24;
        unsigned int thresholdBits = (thresholdExponent << 23); 
        float* thresholdPtr = reinterpret_cast<float*>(&thresholdBits);
        float overflowThreshold = *thresholdPtr;

        std::cout << "Overflow threshold: " << overflowThreshold << std::endl;
        std::bitset<32> thresholdBitset(thresholdBits);
        std::cout << "Threshold Bits: " << thresholdBitset << std::endl;
    } else {
        std::cout << "No overflow detected." << std::endl;
    }

    return 0;
}

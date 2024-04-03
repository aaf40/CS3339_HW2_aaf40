#include <iostream>
#include <string>
#include <bitset>

void printFormattedBits(unsigned int bits, const std::string &label)
{
    std::bitset<32> bitset(bits);
    std::string bitString = bitset.to_string();
    if (!label.empty()) {
        std::cout << label << ": " << bitString.substr(0, 1) << " " << bitString.substr(1, 8) << " " << bitString.substr(9, 23) << std::endl;
    } else {
        std::cout << bitString.substr(0, 1) << " " << bitString.substr(1, 8) << " " << bitString.substr(9, 23) << std::endl;
    }
}


int main(int argc, char *argv[])
{
    if (argc != 3)
    {
        std::cout << "Error: Program requires exactly two floating-point values as input." << std::endl;
        return 1;
    }

    float loopBound = std::stof(argv[1]);
    float loopIncrement = std::stof(argv[2]);

    unsigned int *loopBoundBitsPtr = reinterpret_cast<unsigned int *>(&loopBound);
    unsigned int *loopIncrementBitsPtr = reinterpret_cast<unsigned int *>(&loopIncrement);

    printFormattedBits(*loopBoundBitsPtr, "Loop Bound");
    printFormattedBits(*loopIncrementBitsPtr, "Loop Counter");

    unsigned int loopBoundExponent = ((*loopBoundBitsPtr >> 23) & 0xFF);
    unsigned int loopIncrementExponent = ((*loopIncrementBitsPtr >> 23) & 0xFF);

    int exponentDifference = loopBoundExponent - loopIncrementExponent;

    if (exponentDifference >= 24)
    {
        std::cout << "\nWarning: Possible overflow!" << std::endl;
        std::cout << "Overflow threshold:" << std::endl;

        unsigned int thresholdExponent = loopBoundExponent - 24;
        unsigned int thresholdBits = (thresholdExponent << 23);
        float *thresholdPtr = reinterpret_cast<float *>(&thresholdBits);
        float overflowThreshold = *thresholdPtr;

        std::cout << "        " << overflowThreshold << std::endl;
         std::cout << "        ";

        printFormattedBits(thresholdBits, "");
    }
    else
    {
        std::cout << "\nThere is no overflow!" << std::endl;
    }

    return 0;
}
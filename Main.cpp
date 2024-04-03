#include<iostream>
#include<string>

int main(int argc, char* argv[]) {
    // Check for the correct number of command-line arguments
    if (argc != 3) {
        std::cout << "Error: Program requires exactly two floating-point values as input." << std::endl;
        return 1; // Exit with an error status
    }

    // Parsing command-line arguments to floating-point values
    float loopBound = std::stof(argv[1]);
    float loopIncrement = std::stof(argv[2]);

    // Placeholder for the rest of your program logic

    return 0; // Successful execution
}

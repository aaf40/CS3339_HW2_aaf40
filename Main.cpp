#include <iostream>
#include "FloatBits.h"



int main(int argc, char* argv[]) {
    if (argc != 3) {
        cerr << "Usage: " << argv[0] << " <floating-point number 1> <floating-point number 2>\n";
        exit(1);
    }

    try {
        float number1 = stof(argv[1]);
        float number2 = stof(argv[2]);
        //cout << "Number 1: " << number1 << "\n";
        //cout << "Number 2: " << number2 << "\n";

        FloatBits floatBits1(number1);
        FloatBits floatBits2(number2);

        cout << "Number 1: " << floatBits1.value << ", Bits: " << floatBits1.to_string() << endl;
        cout << "Number 2: " << floatBits2.value << ", Bits: " << floatBits2.to_string() << endl;
    } catch (const exception& e) {
        cerr << "Error parsing arguments as floating-point numbers: " << e.what() << "\n";
        exit(2);
    }

    return 0;
}

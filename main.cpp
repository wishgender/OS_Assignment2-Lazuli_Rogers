//= laz r
//= 11-22-2025 21:30
//= main.cpp

//= Dependencies =//
#include <iostream>
#include <fstream>
#include <sstream>
#include <string>
#include <vector>
#include "System.hpp"

const std::string inputPath = "input.bank";

int main() {
    System sys(inputPath);

    if (sys.isSafeState()) {
        std::cout << "Safe\n";
        auto seq = sys.safeSequence();
        for (int p : seq) std::cout << p << " ";
        std::cout << "\n";
    } else {
        std::cout << "System is not in a safe state.\nNo safe sequence exists.\n";
    }
}
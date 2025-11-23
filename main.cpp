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
        
        srand(time(NULL));
        int pid = rand() % sys.getProcessCount();
        std::vector<int> request = sys.getRandomRequest(pid);
        std::cout << "Process P[" << pid << "] requests the following:\n";
        for (int i : request) std::cout << i << " ";
        if (sys.request(pid, request)) std::cout << "Request granted\n";
        else std::cout << "Request denied\n";
    } else {
        std::cout << "System is not in a safe state.\nNo safe sequence exists.\n";
    }
}
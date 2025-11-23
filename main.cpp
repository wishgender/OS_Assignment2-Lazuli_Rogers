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

bool emptyRequest(std::vector<int>);

int main() {
    System sys(inputPath);

    if (sys.isSafeState()) {
        std::cout << "The system is in a safe state\nSafe sequence:\n";
        auto seq = sys.safeSequence();
        for (int p : seq) std::cout << p << " ";
        std::cout << "\n";
        
        int pid;
        std::vector<int> request;
        srand(time(NULL));
        do {
            pid = rand() % sys.getProcessCount();
            request = sys.getRandomRequest(pid);
        } while (emptyRequest(request));
        
        char resTypeID = 'A';
        std::cout << "Process P[" << pid << "] requests the following resources:\n";
        for (auto i = 0; i < sys.getResourceCount(); i++) {
            std::cout << resTypeID++ << ' ';
        }
        std::cout << '\n';
        for (int i : request) std::cout << i << " ";
        if (sys.request(pid, request)) std::cout << "\nSafe! Request granted!\n";
        else std::cout << "\nInsufficient resources--must wait. Request denied!\n";
    } else {
        std::cout << "System is not in a safe state.\nNo safe sequence exists.\n";
    }
}

bool emptyRequest(std::vector<int> request) {
    for (int i : request) {
        if (i > 0) return false;
    }
    return true;
}
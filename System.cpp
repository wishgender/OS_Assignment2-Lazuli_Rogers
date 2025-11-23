//= laz r
//= 11-22-2025 21:12
//= System.cpp

//= Dependencies =//
#include "System.hpp"
#include <sstream>
#include <stdexcept>
#include <queue>

//===============================//
//==    Algorithm Functions    ==//
//===============================//

//= check safe state
bool System::isSafeState() const {
    std::vector<int> work = available;
    std::vector<bool> finish(n, false);
    int done = 0;

    while (done < n) {
        bool progress = false;

        for (int i = 0; i < n; i++) {
            if (!finish[i]) {
                bool canRun = true;
                for(int j = 0; j < m; j++) {
                    if (need[i][j] > work [j]) {
                        canRun = false;
                        break;
                    }
                }

                if (canRun) {
                    //= Emulate process i finishing and releasing resources
                    for (int j = 0; j < m; j++) {
                        work[j] += allocation[i][j];
                    }
                    finish[i] = true;
                    done++;
                    progress = true;
                }
            }
        }
        if (!progress) return false;
    }
    return true;
}

//= get safe sequence
std::vector<int> System::safeSequence() const {
    std::vector<int> work = available;
    std::vector<bool> finish(n, false);
    std::vector<int> sequence;

    int done = 0;

    while (done < n) {
        bool progress = false;

        for (int i = 0; i < n; i++) {
            if (!finish[i]) {
                bool canRun = true;
                for (int j = 0; j < m; j++) {
                    if (need[i][j] > work [j]) canRun = false;
                }
                if (canRun) {
                    for (int j = 0; j < m; j++) {
                        work[j] += allocation[i][j];
                    }
                    finish[i] = true;
                    sequence.push_back(i);
                    done++;
                    progress = true;
                }
            }
        }
        if (!progress) {
            std::cout << "System is not in a safe state--No safe sequence exists.";
            exit(2);
        }
    }
    return sequence;
}

//===============================//
//==       Parsing Input       ==//
//===============================//

std::vector<std::string> System::readBlock(std::ifstream& in) {
    std::vector<std::string> block;
    std::string line;

    //= skip blank lines
    while (std::getline(in, line) &&
            line.find_first_not_of(" \t") == std::string::npos);
    if (!in) return block;

    block.push_back(line);

    //= Read until next blank line
    while (std::getline(in, line)) {
        if (line.find_first_not_of(" \t") == std::string::npos)
            break;
        block.push_back(line);
    }

    return block;
}

std::vector<int> System::parseVector(const std::string& line) {
    std::istringstream in(line);
    int x;
    std::vector<int> v;
    while (in >> x) v.push_back(x);
    return v;
}

std::vector<std::vector<int>> System::parseMatrix(const std::vector<std::string>& block) {
    std::vector<std::vector<int>> M;
    for (const auto& row : block) {
        M.push_back(parseVector(row));
    }
    return M;
}

//===============================//
//==      Initialization       ==//
//===============================//

System::System(const std::string& filename) {
    loadFromFile(filename);
    computeNeed();
}

void System::loadFromFile(const std::string& filename) {
    std::ifstream file(filename);
    if (!file) {
        throw std::runtime_error("Cannot open file: " + filename);
    }

    //= Read n and m
    n = std::stoi(readBlock(file)[0]);
    m = std::stoi(readBlock(file)[0]);

    //= read resource instances vector
    instances = parseVector(readBlock(file)[0]);

    //= read allocation and maximum need matrices
    allocation = parseMatrix(readBlock(file));
    maximum    = parseMatrix(readBlock(file));

    //= read available resource instances
    available = parseVector(readBlock(file)[0]);
}

void System::computeNeed() {
    need.resize(n, std::vector<int>(m));

    for (int i = 0; i < n; i++) {
        for (int j = 0; j < m; j++) {
            need[i][j] = maximum[i][j] - allocation[i][j];
        }
    }
}

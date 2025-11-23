//= laz r
//= 11-21-2025 01:34
//= System.hpp
#pragma once
//= Dependencies =//
#include <vector>
#include <string>
#include <iostream>
#include <fstream>

class System {
public:
    System(const std::string& filename);   // load Banker's Algorithm input

    //= Algorithm functions
    bool isSafeState() const;
    std::vector<int> safeSequence() const;
    bool request(int pid, const std::vector<int>& req);

    //= Getters
    int getProcessCount() const { return n; }
    int getResourceCount() const { return m; }

    const std::vector<int>& getInstances() const { return instances; }
    const std::vector<int>& getAvailable() const { return available; }

    const std::vector<std::vector<int>>& getAllocation() const { return allocation; }
    const std::vector<std::vector<int>>& getMaximum() const { return maximum; }
    const std::vector<std::vector<int>>& getNeed() const { return need; }

    std::vector<int> getRandomRequest(int pid) const;
private:
    int n; //= number of processes
    int m; //= number of resource types

    std::vector<int> instances;
    std::vector<int> available;
    std::vector<std::vector<int>> allocation;
    std::vector<std::vector<int>> maximum;
    std::vector<std::vector<int>> need;

    std::vector<std::string> readBlock(std::ifstream& in);
    std::vector<int> parseVector(const std::string& line);
    std::vector<std::vector<int>> parseMatrix(const std::vector<std::string>& block);

    void computeNeed();
    void loadFromFile(const std::string& filename);
};

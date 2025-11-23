//= laz r
//= 11-22-2025 18:41
//= inputGen.cpp

//= Dependencies =//
#include <vector>
#include <string>
#include <iostream>
#include <fstream>

const int TEST_SEED = 1;
const int MAX_PROCESSES = 4;
const int MAX_RESOURCE_TYPES = 7;

const std::string outputPath = "input.bank";

//= randomize
int main() {
    // srand(TEST_SEED);
    srand(time(NULL));
    //= initialize number of processes
    int processes = (rand() % MAX_PROCESSES)+2;
    //= initialize number of resource types
    int resourceTypes = (rand() % MAX_RESOURCE_TYPES)+2;

    std::vector<int> available(resourceTypes);
    std::vector<std::vector<int>> allocation(processes, std::vector<int>(resourceTypes));
    std::vector<std::vector<int>> max(processes, std::vector<int>(resourceTypes));

    //= initialize resources of each type
    for (auto i = 0; i < resourceTypes; i++) {
        int instances = (rand() % 9)+2;
        available[i] = instances;
    }
    
    std::ofstream output(outputPath);

    // std::cout << "Processes: " << processes << "\nTypes of resources: " << resourceTypes << "\nAvailable:\n";
    output << processes << "\n\n" << resourceTypes << "\n\n";
    
    for (unsigned i = 0; i < available.size(); i++) {
        // std::cout << available[i] << ' ';
        output << available[i] << '\t';
    }
    output << "\n\n";
    // output << "\n\n";
    // std:: cout << '\n';

    std::vector<int> availableCopy(available);
    for (auto i = 0; i < processes; i++) {
        // std::cout << "\nProcess " << i+1 << '\n';
        // char resType = 'A';


        for (auto j = 0; j < resourceTypes; j++) {
            int allocating = rand() % availableCopy[j];
            // std::cout << "Allocating " << allocating << " of Resource Type " << resType++ << " to Process " << i+1 << std::endl;
            allocation[i][j] =allocating;
            
            int maxRequest;
            do {
                maxRequest = rand() % available[j];
            } while (maxRequest < allocating);
            
            max[i][j] = maxRequest;
            
            availableCopy[j] = availableCopy[j]-allocating;
        }
    }


    // output << "\nAllocation:\n";
    for (auto i = 0; i < processes; i++) {
        for (auto j = 0; j < resourceTypes; j++) {
            output << allocation[i][j] << '\t';
        }
        output << '\n';
    }
    
    output << "\n";
    // output << "\nMaximum Requestable:\n";
    for (auto i = 0; i < processes; i++) {
        for (auto j = 0; j < resourceTypes; j++) {
            output << max[i][j] << '\t';
        }
        output << '\n';
    }

    output << "\n";
    for (unsigned i = 0; i < availableCopy.size(); i++) {
        // std::cout << availableCopy[i] << ' ';
        output << availableCopy[i] << '\t';
    }
    output << "\n";

    output.close();
}


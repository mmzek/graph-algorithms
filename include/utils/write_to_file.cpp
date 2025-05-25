#include "write_to_file.h"

#include <fstream>
#include <iostream>

void toFile(int representationChoice, int algorythmChoice, const unsigned long long duration, const int size, const float density) {
    std::string fileName;
    std::string algorythmName;
    switch (algorythmChoice) {
        case 1: {
            algorythmName = "Dijkstra";
            break;
        }
        case 2: {
            algorythmName = "Bellman-Ford";
            break;
        }
        default: {
            std::cerr << "Unknown operation" << std::endl;
            break;
        }
    }
    switch (representationChoice) {
        case 1: {
            fileName = "adjacency_list.txt";
            break;
        }
        case 2: {
            fileName = "adjacency_matrix.txt";
            break;
        }
        default: {
            std::cerr << "Unknown operation" << std::endl;
            break;
        }
    }


    std::ofstream file(fileName, std::ios::app);
    if (!file.is_open()) {
        std::cerr << "Error opening file: " << fileName << std::endl;
        return;
    }

    file<< "\nNumber of vertexes: "<< size;
    file<< "\nGraph density: "<< density*100 << "%";
    file << "\n" << algorythmName << " results measured in nanoseconds: " << duration << "\n";
}
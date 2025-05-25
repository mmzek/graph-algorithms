#include "performance_tests.h"

#include <iostream>
#include <random>
#include <chrono>

#include "utils/write_to_file.h"
#include "adjacency_list.h"
#include "adjacency_matrix.h"

const int sizes[] = {10,50,100,500,1000};
constexpr float densities[] = {0.25, 0.5, 0.75, 1.0};

void create_list(int size, float density,int algorithmChoice, AdjacencyList<int>& list) {
    int graphSize = size*(size -1);
    for (int j =0; j< static_cast<int>(density) * graphSize;j++) {
        std::random_device rd;
        std::mt19937 gen(rd());
        std::uniform_int_distribution<int> dist_v1(0, size-1);
        std::uniform_int_distribution<int> dist_v2(0, size-1);
        const int v1 = dist_v1(gen);
        const int v2 = dist_v2(gen);
        int w = 0;
        if (algorithmChoice == 1) {
            std::uniform_int_distribution<int> dist_pos(0, INT32_MAX);
            w = dist_pos(gen);
        }else if (algorithmChoice == 2) {
            std::uniform_int_distribution<int> dist_neg(INT32_MIN, INT32_MAX);
            w = dist_neg(gen);
        }
        list.addEdge(v1, v2, w);
    }
}
void create_matrix(int size, float density,int algorithmChoice, AdjacencyMatrix<int>& matrix) {
    int graphSize = size*(size -1);
    for (int j =0; j<graphSize*static_cast<int>(density);j++) {
        std::random_device rd;
        std::mt19937 gen(rd());
        std::uniform_int_distribution<int> dist_v1(0, size-1);
        std::uniform_int_distribution<int> dist_v2(0, size-1);
        const int v1 = dist_v1(gen);
        const int v2 = dist_v2(gen);
        int w = 0;
        if (algorithmChoice == 1) {
            std::uniform_int_distribution<int> dist_pos(0, INT32_MAX);
            w = dist_pos(gen);
        }else if (algorithmChoice == 2) {
            std::uniform_int_distribution<int> dist_neg(INT32_MIN, INT32_MAX);
            w = dist_neg(gen);
        }
         matrix.addEdge(v1, v2, w);
    }
}

void performance_tests(int representationChoice, int algorithmChoice, int size, float density) {
    long long currentDuration = 0;

    for (int i = 0; i < 100; i++) {

        AdjacencyList<int> list(size);
        AdjacencyMatrix<int> matrix(size);

        if (representationChoice ==1) {
            create_list(size, density,algorithmChoice,list);
        }else if (representationChoice==2) {
            create_matrix(size,density,algorithmChoice,matrix);
        }

        switch (representationChoice) {
            case 1: {
                if (algorithmChoice == 1) {
                    auto start = std::chrono::high_resolution_clock::now();
                    list.dijkstra_algorithm(0,size-1);
                    auto stop = std::chrono::high_resolution_clock::now();
                    auto duration = duration_cast<std::chrono::nanoseconds>(stop - start);
                    currentDuration += duration.count();
                    break;
                }
                if (algorithmChoice == 2) {
                    auto start = std::chrono::high_resolution_clock::now();
                    list.bellman_ford_algorithm(0,size-1);
                    auto stop = std::chrono::high_resolution_clock::now();
                    auto duration = duration_cast<std::chrono::nanoseconds>(stop - start);
                    currentDuration += duration.count();
                    break;
                }
            }
            case 2: {
                if (algorithmChoice == 1) {
                    auto start = std::chrono::high_resolution_clock::now();
                    matrix.dijkstra_algorithm(0,size-1);
                    auto stop = std::chrono::high_resolution_clock::now();
                    auto duration = duration_cast<std::chrono::nanoseconds>(stop - start);
                    currentDuration += duration.count();
                    break;
                }
                if (algorithmChoice == 2) {
                    auto start = std::chrono::high_resolution_clock::now();
                    matrix.bellman_ford_algorithm(0,size-1);
                    auto stop = std::chrono::high_resolution_clock::now();
                    auto duration = duration_cast<std::chrono::nanoseconds>(stop - start);
                    currentDuration += duration.count();
                    break;
                }
            }
            default:
                std::cout << "Wrong choice\n";
                break;
        }
    }
    toFile(representationChoice, algorithmChoice, currentDuration / 100, size, density);

    std::string algorithmName;
    if (algorithmChoice ==1) {
        algorithmName = "Dijkstra";
    }else if (algorithmChoice ==2){
        algorithmName = "Bellman-Ford";
    }
    std::cout << "\nTime duration of " <<algorithmName<< " for " << size << " vertex count with " << density*100 <<
            "% presorted values was written to file." << "\n";
}


int chooseAlgorithm() {
    while (true) {
        int representationChoice =0;
        std::cout << "\nChoose the representation:\n1-Adjacency list\n2-Adjacency matrix\n3-All tests at once\n0-Exit\n";
        std::cin >> representationChoice;

        if (representationChoice == 0) return 0;
        if (representationChoice != 3) {
            int algorithmChoice = 0;
            std::cout << "\nChoose the algorithm:\n1-Dijkstra\n2-Bellman-Ford\n";
            std::cin >> algorithmChoice;
            int sizeChoice = 0;
            int densityChoice = 0;
            std::cout <<
                    "\nChoose graph size:\n1-10\n2-50\n3-100\n4-500\n5-1000\n";
            std::cin >> sizeChoice;
            std::cout << "\nChoose graph density:\n1-25%\n2-50%\n3-75%\n4-100%\n";
            std::cin >> densityChoice;

            const int size = sizes[sizeChoice - 1];
            const float density = densities[densityChoice - 1];
            performance_tests(representationChoice, algorithmChoice, size, density);

            }else {
                for (int rep =1; rep<=2; rep ++) {
                    for (int algorithm =1; algorithm<=2; algorithm ++) {
                        for (int size : sizes) {
                            for (float density : densities) {
                                performance_tests(rep, algorithm, size, density);
                            }
                        }
                    }
                }
            }
        }
}
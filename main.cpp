#include "include/adjacency_list.h"
#include "include/adjacency_matrix.h"
#include "include/performance_tests.h"


void driver() {
    constexpr int size = 5;
    constexpr float density = 1.0;
    AdjacencyList<int> list(size);
    AdjacencyMatrix<int> matrix(size);

    create_list(size, density, 1,list);
    list.display();
    std::vector<int> pathL = list.dijkstra_algorithm(0,size-1);
    list.path_display(pathL, "Dijkstra", 0, size-1);

    create_list(size, density, 2,list);
    list.display();
    std::vector<int> pathLB = list.bellman_ford_algorithm(0,size-1);
    list.path_display(pathLB, "Bellman-Ford", 0, size-1);

    create_matrix(size, density, 1,matrix);
    matrix.display();
    std::vector<int> pathM = matrix.dijkstra_algorithm(0,size-1);
    matrix.path_display(pathM, "Dijkstra", 0, size-1);

    create_matrix(size, density, 2,matrix);
    matrix.display();
    std::vector<int> pathMB = matrix.bellman_ford_algorithm(0,size-1);
    matrix.path_display(pathMB, "Bellman-Ford", 0, size-1);
}

int main() {
    int choice = 0;
    std::cout << "\nChoose the action:\n1-Performance tests\n2-Driver\n";
    std::cin >> choice;
    if (choice == 1) {
        chooseAlgorithm();
    } if (choice == 2) {
        driver();
    }
}

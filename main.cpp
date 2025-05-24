#include "include/adjacency_list.h"
#include "include/adjacency_matrix.h"

int main() {
    AdjacencyMatrix<int> list(5);
    list.addEdge(2,3,4);
    list.addEdge(3,2,3);
    list.addEdge(2, 1, 1);
    list.addEdge(1, 4, 2);
    list.display();
    AdjacencyList<int> matrix(5);
    matrix.addEdge(2,3,4);
    matrix.addEdge(3,2,3);
    matrix.addEdge(2, 1, 1);
    matrix.addEdge(1, 4, 2);
    matrix.display();
}

#ifndef ADJACENCY_MATRIX_H
#define ADJACENCY_MATRIX_H
#include <iostream>
#include <vector>

template<typename T>
class AdjacencyMatrix {
    std::vector<std::vector<T>> matrix;

public:
    explicit AdjacencyMatrix(int size);
    void addEdge(T v1, T v2, T w);
    void display();
};

template<typename T>
AdjacencyMatrix<T>::AdjacencyMatrix(int size) {
    matrix.resize(size, std::vector<T>(size, 0));
}

template<typename T>
void AdjacencyMatrix<T>::addEdge(T v1,T v2,T w) {
    matrix[v1][v2] = w;
}

template<typename T>
void AdjacencyMatrix<T>::display() {
    std::cout<<"Adjacency matrix: \n   ";

    for (int i=0; i<matrix.size();i++) {
        std::cout<<" "<<i<<" ";
    }
    std::cout<<std::endl<<"   ";
    for (int i=0; i<matrix.size();i++) {
        std::cout<<" _ ";
    }
    std::cout<<std::endl;
    for (int j=0; j<matrix.size(); j++) {
        std::cout<<j<<" | ";
        for (int i=0; i<matrix[j].size(); i++) {
            std::cout<<matrix[j][i]<<"  ";
        }std::cout<<std::endl;
    }
    std::cout<<std::endl;
}
#endif //ADJACENCY_MATRIX_H

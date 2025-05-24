#ifndef ADJACENCY_LIST_H
#define ADJACENCY_LIST_H
#include <iostream>
#include <vector>

template<typename T>
struct Node {
    T vertex = 0;
    T weight = 0;
    Node() = default;
    Node(T v, T w) : vertex(v), weight(w) {}
};

template<typename T>
class AdjacencyList {
    std::vector<std::vector<Node<T>>> list;

public:
    explicit AdjacencyList(int size);
    void addEdge(T v1, T v2, T w);
    void display();
};

template<typename T>
AdjacencyList<T>::AdjacencyList(int size) : list(size) {}

template<typename T>
void AdjacencyList<T>::addEdge(T v1,T v2,T w) {
    Node<T> neighbour(v2, w);
    list[v1].push_back(neighbour);
}

template<typename T>
void AdjacencyList<T>::display() {
    std::cout<<"Adjacency list: \n";
    for (int j=0; j<list.size(); j++) {
        std::cout<<j;
        for (int i=0; i<list[j].size(); i++) {
            std::cout<<" -> ["<<list[j][i].vertex<<", "<<list[j][i].weight<<"]";
        }
        std::cout<<std::endl;
    }
}
#endif //ADJACENCY_LIST_H

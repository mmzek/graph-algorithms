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
    std::vector<T> dijkstra_algorithm(T v1, T v2);
    std::vector<T> bellman_ford_algorithm(T v1, T v2);
    void path_display(std::vector<T>& previous, const std::string& text, T start, T end);
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
    std::cout<<"\nAdjacency matrix: \n   ";

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
}

template<typename T>
std::vector<T> AdjacencyMatrix<T>::dijkstra_algorithm(T v1, T v2) {
    std::priority_queue<std::vector<T>, std::vector<std::vector<T>>, std::greater<std::vector<T>>> queue;
    std::vector<T> distance(matrix.size(), INT_MAX);
    std::vector<T> previous(matrix.size(), -1);
    distance[v1] = 0;
    queue.push({v1, 0});
    while (!queue.empty()){
        std::vector<T> current = queue.top();
        queue.pop();

        T current_distance = current[0];
        T u = current[1];

        if (current_distance > distance[u]) continue;

        for (int v = 0; v < matrix.size(); ++v) {
            T weight = matrix[u][v];
            if (weight == 0) continue;

            if (distance[v] > distance[u] + weight) {
                distance[v] = distance[u] + weight;
                previous[v] = u;
                queue.push({distance[v], v});
            }
        }

    }
    return previous;
}

template<typename T>
std::vector<T> AdjacencyMatrix<T>::bellman_ford_algorithm(T v1, T v2) {
    std::vector<T> distance(matrix.size(), INT_MAX);
    std::vector<T> previous(matrix.size(), -1);
    distance[v1] = 0;
    for (int i = 0; i < matrix.size() - 1; ++i) {
        bool updated = false;
        for (int u = 0; u < matrix.size(); ++u) {
            if (distance[u] == INT_MAX) continue;
            for (int v = 0; v < matrix.size(); ++v) {
                T weight = matrix[u][v];
                if (weight == 0) continue;

                if (distance[v] > distance[u] + weight) {
                    distance[v] = distance[u] + weight;
                    previous[v] = u;
                    updated = true;
                }
            }
        }
        if (!updated) break;
    }
    for (int u = 0; u < matrix.size(); ++u) {
        if (distance[u]==INT_MAX) continue;
        for (int v = 0; v < matrix.size(); ++v) {
            T weight = matrix[u][v];
            if (weight == 0) continue;

            if (distance[v] > distance[u] + weight) {
                std::cout<<"Negative cycle";
                return {};
            }
        }
    }
    return previous;
}

template<typename T>
void AdjacencyMatrix<T>::path_display(std::vector<T>& previous, const std::string& text, T start, T end) {
    if (matrix.empty()) {
        std::cout << "Graph is empty!" << std::endl;
        return;
    }
    std::vector<T> path;
    T current = end;
    if (previous[end] == -1 && start != end) {
        std::cout << "No path from " << start << " to " << end << std::endl;
        return;
    }
    while (current!=-1&& current != start) {
        path.push_back(current);
        current = previous[current];
    }
    path.push_back(start);
    std::cout<<"\n"<<text<<" shortest path: ";
    if (!path.empty()) {
        for (int i = path.size(); i > 0; --i) {
            std::cout << path[i-1];
            if (i-1 != 0) {
                std::cout << " -> ";
            }
        }
    }
    std::cout << std::endl;
}
#endif //ADJACENCY_MATRIX_H




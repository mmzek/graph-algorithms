#ifndef ADJACENCY_LIST_H
#define ADJACENCY_LIST_H
#include <iostream>
#include <queue>
#include <vector>

template<typename T>
struct Node {
    T vertex = 0;
    T weight = 0;
    Node() = default;
    Node(T v, T w) : vertex(v), weight(w) {}
    bool operator>(const Node<T>& other) const {
        return weight > other.weight;
    }
};

template<typename T>
class AdjacencyList {
public:    
    std::vector<std::vector<Node<T>>> list;
    
    explicit AdjacencyList(int size);
    void addEdge(T v1, T v2, T w);
    void display();

    std::vector<T> dijkstra_algorithm(T v1, T v2);
    std::vector<T> bellman_ford_algorithm(T v1, T v2);
    void path_display(std::vector<T>& previous, const std::string& text, T start, T end);
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
    std::cout<<"\nAdjacency list: \n";
    for (int j=0; j<list.size(); j++) {
        std::cout<<j;
        for (int i=0; i<list[j].size(); i++) {
            std::cout<<" -> ["<<list[j][i].vertex<<", "<<list[j][i].weight<<"]";
        }
        std::cout<<std::endl;
    }
}

template<typename T>
std::vector<T> AdjacencyList<T>::dijkstra_algorithm(T v1, T v2) {
        std::priority_queue<Node<T>, std::vector<Node<T>>, std::greater<Node<T>>> queue;
        std::vector<T> distance(list.size(), INT_MAX);
        std::vector<T> previous(list.size(), -1);
        distance[v1] = 0;
        queue.push(Node<T>(v1, 0));
        while (!queue.empty()){
            Node<T> current = queue.top();
            queue.pop();
            T u = current.vertex;

            if (current.weight > distance[u]) continue;

            for (const Node<T>& neighbor : list[u]){
                T v = neighbor.vertex;
                T weight = neighbor.weight;
                if (distance[v] > distance[u] + weight)
                {
                    distance[v] = distance[u] + weight;
                    previous[v]=u;
                    queue.push(Node<T>(v, distance[v]));
                }
            }
        }
    return previous;
}

template<typename T>
std::vector<T> AdjacencyList<T>::bellman_ford_algorithm(T v1, T v2) {
    std::vector<T> distance(list.size(), INT_MAX);
    std::vector<T> previous(list.size(), -1);
    distance[v1] = 0;
    for (int i = 0; i < list.size() - 1; ++i) {
        bool updated = false;
        for (int u = 0; u < list.size(); ++u) {
            for (const Node<T>& neighbor : list[u]) {
                T v = neighbor.vertex;
                T weight = neighbor.weight;
                if (distance[u] != INT_MAX && distance[v] > distance[u] + weight) {
                    distance[v] = distance[u] + weight;
                    previous[v] = u;
                    updated = true;
                }
            }
        }
        if (!updated) break;
    }
    for (int u = 0; u < list.size(); ++u) {
        if (distance[u] == INT_MAX) continue;
        for (const Node<T>& neighbor : list[u]) {
            T v = neighbor.vertex;
            T weight = neighbor.weight;
            if (distance[v] > distance[u] + weight) {
                std::cerr<<"Negative cycle";
                return {};
            }
        }
    }
    return previous;
}

template<typename T>
void AdjacencyList<T>::path_display(std::vector<T>& previous, const std::string& text, T start, T end) {
    if (list.empty()) {
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

#endif //ADJACENCY_LIST_H

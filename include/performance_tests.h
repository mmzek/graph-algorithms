#ifndef PERFORMANCE_TESTS_H
#define PERFORMANCE_TESTS_H

#include "adjacency_list.h"
#include "adjacency_matrix.h"

void create_list(int size, float density,int algorithmChoice, AdjacencyList<int>& list);
void create_matrix(int size, float density,int algorithmChoice, AdjacencyMatrix<int>& matrix);
void performance_tests(int representationChoice, int algorithmChoice, int size, float density);
int chooseAlgorithm();


#endif //PERFORMANCE_TESTS_H
cmake_minimum_required(VERSION 3.30)
project(graph_algorithms)

set(CMAKE_CXX_STANDARD 20)

add_executable(graph_algorithms main.cpp
        include/adjacency_matrix.h
        include/adjacency_list.h
        include/utils/write_to_file.h
        include/utils/write_to_file.cpp
        include/performance_tests.cpp
        include/performance_tests.h
)

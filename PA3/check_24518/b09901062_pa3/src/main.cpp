#include <fstream>
#include <iostream>

#include "graph.h"

using namespace std;

int main(int argc, char* argv[]) {
    fstream fin(argv[1]);
    // fout.open(argv[2], ios::out);
    char graph_type;
    fin >> graph_type;
    vector<int> x{ 1, 2, 3, 4 };
    int vertices_num, edges_num;
    fin >> vertices_num;
    fin >> edges_num;

    int from, to, weight;
    if (graph_type == 'u') {
        UndirectedGraph graph(vertices_num, edges_num);
        while (fin >> from >> to >> weight) {
            graph.addEdge(from, to, weight);
        }
        graph.MST();
        graph.printRemoveEdges(argv[2]);
    } else {
        DirectedGraph graph(vertices_num, edges_num);
        while (fin >> from >> to >> weight) {
            graph.addEdge(from, to, weight);
        }
        graph.augmentMST();
        graph.printRemoveEdges(argv[2]);
    }

    // UndirectedGraph graph(14);
    // graph.addEdge(1, 2, 1);
    // graph.addEdge(2, 3, 1);
    // graph.addEdge(3, 4, 1);
    // graph.addEdge(4, 6, 1);
    // graph.addEdge(4, 7, 1);
    // graph.addEdge(5, 6, 1);
    // graph.addEdge(3, 5, 1);
    // graph.addEdge(7, 8, 1);
    // graph.addEdge(6, 10, 1);
    // graph.addEdge(5, 9, 1);
    // graph.addEdge(10, 9, 1);
    // graph.addEdge(10, 11, 1);
    // graph.addEdge(11, 12, 1);
    // graph.addEdge(11, 13, 1);
    // graph.addEdge(12, 13, 1);
    // graph.getCycle();
}
#ifndef _GRAPH_H_
#define _GRAPH_H_
#include <fstream>
#include <iostream>
#include <unordered_map>
#include <vector>
using namespace std;

#define WHITE 0
#define GRAY 1
#define BLACK 2

struct Edge {
    int u;    // from
    int v;    // to
    int16_t weight;

    bool operator<(const Edge &e) const {
        return (this->weight < e.weight);
    }
    bool operator==(const Edge &e) const {
        return (e.u == u) && (e.v == v) && (e.weight == weight);
    }
    Edge &operator=(const Edge &e) {
        u = e.u;
        v = e.v;
        weight = e.weight;
        return *(this);
    }
};

class UndirectedGraph {
   public:
    UndirectedGraph(int, int);

    void addEdge(int, int, int);

    void removeEdge(int, int);

    bool hasEdge(int, int);

    vector<int> getAdjacentVertices(int);

    vector<vector<int>> getAdjacencyList();

    unordered_map<int, unordered_map<int, int>> getWeightList();

    void setRemoveEdges(vector<Edge>);

    void printRemoveEdges(string);

    void MST();

    int Degree(int);
    // void getCycle();

   private:
    // void printCycles(int &);
    // void dfs_cycle(int, int, vector<int> &, vector<int> &, int &);
    // vector<int> generateCycle(vector<int>, int);

    int num_vertices_;
    vector<vector<int>> adjacency_list_;
    unordered_map<int, unordered_map<int, int>> weight_list_;
    vector<Edge> edges_;
    vector<Edge> remove_edges_;
    // int cyclenumber;
    // vector<vector<int>> cycles;
};

class DirectedGraph {
   public:
    DirectedGraph(int, int);

    void addEdge(int, int, int);

    void removeEdge(int, int);

    bool hasEdge(int, int);

    vector<int> getAdjacentVertices(int);

    vector<vector<int>> getAdjacencyList();

    unordered_map<int, unordered_map<int, int>> getWeightList();

    bool hasCycle();

    void setRemoveEdges(vector<Edge>);

    void printRemoveEdges(string);

    void MST(vector<Edge> &);

    int Degree(int);

    void augmentMST();
    // void getCycle();

   private:
    // void printCycles(int &);
    // void dfs_cycle(int, int, vector<int> &, vector<int> &, int &);
    // vector<int> generateCycle(vector<int>, int);
    bool Dfs(int, vector<bool> &, vector<int> &);

    int num_vertices_;
    vector<vector<int>> adjacency_list_;
    unordered_map<int, unordered_map<int, int>> weight_list_;
    vector<Edge> edges_;
    vector<Edge> remove_edges_;
    // int cyclenumber;
    // vector<vector<int>> cycles;
};

struct subset {
    int parent;
    int rank;
};

class DisjoinSet {
   public:
    DisjoinSet(int &);
    ~DisjoinSet();
    void makeSet();
    int find(int &) const;
    void Union(int &, int &);

   private:
    int nSubset_ = 0;
    subset *subs_;
};

#endif
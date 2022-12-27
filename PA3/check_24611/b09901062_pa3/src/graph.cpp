#include "graph.h"

#include <algorithm>
#include <unordered_map>
#include <vector>
using namespace std;

UndirectedGraph::UndirectedGraph(int num_vertices, int edges) : num_vertices_(num_vertices), adjacency_list_(num_vertices) {}

vector<int> UndirectedGraph::getAdjacentVertices(int u) { return adjacency_list_[u]; }

vector<vector<int>> UndirectedGraph::getAdjacencyList() { return adjacency_list_; }

unordered_map<int, unordered_map<int, int>> UndirectedGraph::getWeightList() { return weight_list_; }

int UndirectedGraph::Degree(int u) { return adjacency_list_[u].size(); }

void UndirectedGraph::setRemoveEdges(vector<Edge> map) {
    sort(map.begin(), map.end());
    remove_edges_ = map;
}

void UndirectedGraph::addEdge(int u, int v, int w) {
    // for undirected graph
    adjacency_list_[u].push_back(v);
    weight_list_[u][v] = w;
    adjacency_list_[v].push_back(u);
    weight_list_[v][u] = w;

    Edge e;
    e.u = u;
    e.v = v;
    e.weight = w;
    edges_.push_back(e);
}

void UndirectedGraph::removeEdge(int u, int v) {
    adjacency_list_[u].erase(remove(adjacency_list_[u].begin(), adjacency_list_[u].end(), v),
                             adjacency_list_[u].end());
}

bool UndirectedGraph::hasEdge(int u, int v) {
    return find(adjacency_list_[u].begin(), adjacency_list_[u].end(), v) != adjacency_list_[u].end();
}

void UndirectedGraph::printRemoveEdges(string outpath) {
    fstream fout;
    fout.open(outpath, ios::out);
    int sum = 0;
    for (auto e : remove_edges_) {
        cout << e.u << " ";
        cout << e.v << " ";
        cout << e.weight << endl;
        sum += e.weight;
    }
    cout << remove_edges_.size() << " edges left!" << endl;
    cout << sum << " is the ans" << endl;
    fout << sum << endl;
    for (auto e : remove_edges_) {
        fout << e.u << " ";
        fout << e.v << " ";
        fout << e.weight << endl;
    }
}

void UndirectedGraph::MST() {
    DisjoinSet s(num_vertices_);
    sort(edges_.begin(), edges_.end());
    for (int32_t i = edges_.size() - 1; i >= 0; --i) {
        if (s.find(edges_[i].u) != s.find(edges_[i].v))
            s.Union(edges_[i].u, edges_[i].v);
        else
            remove_edges_.push_back(edges_[i]);
    }
}
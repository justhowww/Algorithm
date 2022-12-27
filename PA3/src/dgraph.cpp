#include <algorithm>
#include <unordered_map>
#include <vector>

#include "graph.h"
using namespace std;

DirectedGraph::DirectedGraph(int num_vertices, int edges) : num_vertices_(num_vertices), adjacency_list_(num_vertices) {}

vector<int> DirectedGraph::getAdjacentVertices(int u) { return adjacency_list_[u]; }

vector<vector<int>> DirectedGraph::getAdjacencyList() { return adjacency_list_; }

unordered_map<int, unordered_map<int, int>> DirectedGraph::getWeightList() { return weight_list_; }

int DirectedGraph::Degree(int u) { return adjacency_list_[u].size(); }

void DirectedGraph::setRemoveEdges(vector<Edge> map) {
    sort(map.begin(), map.end());
    remove_edges_ = map;
}

void DirectedGraph::addEdge(int u, int v, int w) {
    // for undirected graph
    adjacency_list_[u].push_back(v);
    weight_list_[u][v] = w;

    Edge e;
    e.u = u;
    e.v = v;
    e.weight = w;
    edges_.push_back(e);
}

// need to update remove weight list and struct
void DirectedGraph::removeEdge(int u, int v) {
    adjacency_list_[u]
        .erase(remove(adjacency_list_[u].begin(), adjacency_list_[u].end(), v),
               adjacency_list_[u].end());
}

bool DirectedGraph::hasEdge(int u, int v) {
    return find(adjacency_list_[u].begin(), adjacency_list_[u].end(), v) != adjacency_list_[u].end();
}

bool DirectedGraph::hasCycle() {
    vector<bool> visited(num_vertices_, false);
    vector<int> path;
    for (int u = 0; u < num_vertices_; u++) {
        if (visited[u])
            continue;
        if (Dfs(u, visited, path))
            return true;
    }
    return false;
}

void DirectedGraph::printRemoveEdges(string outpath) {
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

bool DirectedGraph::Dfs(int u, vector<bool> &visited, vector<int> &path) {
    vector<int> cycle;

    visited[u] = BLACK;
    path.push_back(u);
    for (int v : adjacency_list_[u]) {
        if (visited[v]) {
            if (find(path.begin(), path.end(), v) != path.end()) {
                cout << "Cycle: ";
                for (auto &vertex : path) {
                    cout << vertex << " ";
                }
                cout << endl;
                return true;    // Cycle found
            }
        } else {
            if (Dfs(v, visited, path))
                return true;
        }
    }
    path.pop_back();
    return false;
}

void DirectedGraph::MST(vector<Edge> &temp) {
    DisjoinSet s(num_vertices_);
    sort(edges_.begin(), edges_.end());
    for (int32_t i = edges_.size() - 1; i >= 0; --i) {
        if (s.find(edges_[i].u) != s.find(edges_[i].v))
            s.Union(edges_[i].u, edges_[i].v);
        else
            temp.push_back(edges_[i]);
    }
}

void DirectedGraph::augmentMST() {
    vector<Edge> tempRemoval;
    MST(tempRemoval);    // The edges that is out of maximum spanning tree
    // Now we need to try adding new edges without generating new cycle.
    // First, we remove them from original graph.
    for (Edge e : tempRemoval) {
        removeEdge(e.u, e.v);
    }
    sort(tempRemoval.begin(), tempRemoval.end(), [](const Edge e1, const Edge e2) {
        return e1.weight > e2.weight;
    });

    // Now we add the assumed-removed edges back, if it has positive weight. We must remove negative weights edges -> smaller
    for (Edge e : tempRemoval) {
        if (e.weight < 0) {
            remove_edges_.push_back(e);
            continue;
        }

        // try add edge back
        addEdge(e.u, e.v, e.weight);

        if (hasCycle()) {
            removeEdge(e.u, e.v);
            remove_edges_.push_back(e);
        }
    }
}
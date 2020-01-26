#include "simple.h"

SimpleAlgorithm::SimpleAlgorithm(size_t _n, size_t _m)
: L(_n, 0), adj(_n, vs()) {
    n = _n;
    m = _m;
}

bool SimpleAlgorithm::update_label(size_t u, size_t original_vertex) {
    if (u == original_vertex) {
        // we have found a cycle by returning to the original vertex
        return false;
    }

    for (size_t i = 0; i < adj[u].size(); i++) {
        size_t next_vertex = adj[u][i];

        if (L[u] >= L[next_vertex]) {
            L[next_vertex] = L[u] + 1;
            if (!update_label(next_vertex, original_vertex)) {
                // cycle found
                return false;
            }
        }
    }

    // successfully completed the updates
    return true;
}

bool SimpleAlgorithm::insert_edge(size_t u, size_t v) {
    /* inserts directed edge u to v
     * in case of failure (cycle or otherwise) returns false */
    
    if (u < 0 || u >= n || v < 0 || v >= n) {
        std::cout << "Nodes are in range [0, n)\n";
        return false;
    }

    adj[u].push_back(v);
    if (L[u] >= L[v]) { // we have to update v's label
        L[v] = L[u] + 1;
        if (!update_label(v, u)) {
            // cycle found
            return false;
        }
    }

    return true;
}

bool SimpleAlgorithm::precedes(size_t u, size_t v) {
    /* returns if node u precedes node v in topological ordering */
    return L[u] < L[v];
}

std::vector < size_t > SimpleAlgorithm::topsort() {
    std::vector < size_t > result;
    std::vector < vs > labels(n, vs());

    for (size_t i = 0; i < n; i++) {
        labels[L[i]].push_back(i);
    }
    
    for (size_t i = 0; i < n; i++) {
        for (size_t j = 0; j < labels[i].size(); j++) {
            result.push_back(labels[i][j]);
        }
    }

    return result;
}
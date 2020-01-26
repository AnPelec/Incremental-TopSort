#include <bits/stdc++.h>
#include <iostream>
#include <utility>

#include "simple.h"

typedef std::pair < size_t, size_t > ss;

bool validate_topsort(size_t n, std::vector < size_t > topsort,
                      std::vector < ss > edges) {
    if (topsort.size() != n) {
        std::cout << "Topological Order is of size " << topsort.size()
                    << " instead of " << n << "\n";
        return false;
    }

    std::vector < size_t > index(n, n);
    for (size_t i = 0; i < topsort.size(); i++) {
        if (topsort[i] < 0 || topsort[i] >= n) { // node value not in [0, n)
            std::cout << "Value of node " << topsort[i] << " is invalid\n";
            return false;
        }
        if (index[topsort[i]] != n) { // we have encountered this node before
            std::cout << "Duplicate of node " << topsort[i] << "was found\n";
            return false;
        }

        index[topsort[i]] = i;
    }

    for (size_t i = 0; i < edges.size(); i++) {
        size_t u = edges[i].first;
        size_t v = edges[i].second;

        if (index[u] >= index[v]) {
            std::cout << "Nodes " << u << ", " << v << " are not in order\n";
            return false;
        }
    }

    return true;
}

int main()
{
    std::vector < ss > edges;

    size_t n = 10, m = 10;
    SimpleAlgorithm graph(n, m);

    for (size_t i = 0; i < n; i++) {
        size_t u = i;
        size_t v = (i + 1)%n;

        edges.push_back(ss(u, v));
        if (!graph.insert_edge(u, v)) {
            break;
        }

        std::vector < size_t > order = graph.topsort();
        if (!validate_topsort(n, order, edges))
            break;
    }
}
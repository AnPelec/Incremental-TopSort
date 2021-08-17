#include <bits/stdc++.h>
#include <iostream>
#include <utility>

#include "idealAlgorithm.h"
// #include "naiveAlgorithm.h"

typedef std::function<bool()> testType;
typedef std::pair < size_t, size_t > ss;

bool validate_topsort(size_t n,
                      std::vector < size_t > topsort,
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

bool testSimple1() {
    size_t n = 10, m = 10;
    // NaiveAlgorithm graph(n, m);
    IdealAlgorithm graph(n, m);
    std::vector < ss > edges;

    for (size_t i = 0; i < n; i++) {
        size_t u = i;
        size_t v = (i + 1)%n;

        edges.push_back(ss(u, v));
        if (!graph.insert_edge(u, v)) {
            break;
        }

        std::vector < size_t > order = graph.topsort();
        if (!validate_topsort(n, order, edges))
            return false;
    }
    return true;
}

bool testSimple2() {
    IdealAlgorithm graph(5, 6);

    if (!graph.insert_edge(4, 2)) return false;
    if (!graph.insert_edge(4, 3)) return false;
    if (!graph.insert_edge(3, 2)) return false;
    if (!graph.insert_edge(4, 0)) return false;
    if (!graph.insert_edge(1, 0)) return false;
    if (!graph.insert_edge(1, 3)) return false;

    std::vector < size_t > order = graph.topsort();
    size_t positions[] = {0, 0, 0, 0, 0};
    for (size_t i = 0; i < order.size(); ++i) {
        positions[order[i]] = i;
    }
    if (positions[4] > positions[2]) return false;
    if (positions[4] > positions[3]) return false;
    if (positions[3] > positions[2]) return false;
    if (positions[4] > positions[0]) return false;
    if (positions[1] > positions[0]) return false;
    if (positions[1] > positions[3]) return false;

    return true;
}

int main()
{
    std::initializer_list<testType> testArray {testSimple1,
                                               testSimple2};

    size_t index = 0;
    size_t failedTests = 0;
    for (auto test : testArray) {
        if (!test()) {
            std::cout << "Test #" << index << " was wrong.\n";
            failedTests += 1;
        }
        index += 1;
    }
    std::cout << failedTests << "/" << index << " tests failed.\n";
    return 0;
}
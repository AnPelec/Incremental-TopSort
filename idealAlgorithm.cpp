#include "idealAlgorithm.h"

IdealAlgorithm::IdealAlgorithm(size_t _n, size_t _m)
: k(_n, 0),
  k_in(_n, BST()),
  key_cache(_n, std::vector<KeyCache>()),
  adj(_n, VectorNode()) {
    n = _n;
    m = _m;
}

/* inserts directed edge u to v
 * in case of failure (cycle or otherwise) returns false */
bool IdealAlgorithm::insert_edge(Node u, Node v) {
    
    if (u < 0 || u >= n || v < 0 || v >= n) {
        std::cout << "Nodes are in range [0, n)\n";
        return false;
    }

    adj[u].push_back(v);
    k_in[v].insert(k_in[v].root, k[u]);
    key_cache[u].push_back(KeyCache(v, LabelLabel(k[u], k[v])));
    size_t index = key_cache[u].size() - 1;

    // if (k[u] < k[v]) {
    //     k_in[u].push_back(k[v])
    //     k_out[u].push_back(k[u])
    if (k[u] >= k[v]) { // we have to update v's label
        std::queue<EdgeIndex> edges_to_traverse;
        edges_to_traverse.push(EdgeIndex(Edge(u, v), index));

        while (!edges_to_traverse.empty()) {
            EdgeIndex edge_index = edges_to_traverse.front();
            Edge next_edge = edge_index.first;
            Index index = edge_index.second;
            edges_to_traverse.pop();

            Node x = next_edge.first;
            Node y = next_edge.second;

            if (y == u) return false;

            // set k_in(x, y) = k(x)
            LabelLabel old_key = key_cache[x][index].second;
            k_in[y].erase(old_key.first);
            k_in[y].insert(k_in[y].root, k[x]);
            key_cache[x][index].second.first = k[x];
            
            // order predecessors of y and obtain s = max_i {k_in(u_i, y) + i}
            Label s = k_in[y].get_max_score(k_in[y].root);
            if (s > k[y]) {
                k[y] = s;

                Index curr_index = 0;
                for (auto out_edge : key_cache[y]) {
                    if (out_edge.second.second <= k[y]) {
                        edges_to_traverse.push(EdgeIndex(Edge(y, adj[y][curr_index]), curr_index));
                    }
                    curr_index += 1;
                }

                key_cache[x][index].second.second = k[y];
            }

            // if s > k(y)
            //      set k(y) = s
            //      add all arcs (y, z) such that k_out(y, z) <= k(y) to the queue
            //      set k_out(x, y) = k(y)
        }
    }

    return true;
}

bool IdealAlgorithm::precedes(Node u, Node v) {
    /* returns if node u precedes node v in topological ordering */
    return k[u] < k[v];
}

std::vector < Node > IdealAlgorithm::topsort() {
    std::vector < Node > result;
    std::vector < std::vector < Label > > labels(n, std::vector<Label>());

    for (Node i = 0; i < n; i++) {
        labels[k[i]].push_back(i);
    }
    
    for (Label i = 0; i < n; i++) {
        for (size_t j = 0; j < labels[i].size(); j++) {
            result.push_back(labels[i][j]);
        }
    }

    return result;
}
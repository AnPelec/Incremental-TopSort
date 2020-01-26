#include <bits/stdc++.h>
#include <iostream>

typedef std::vector < size_t > vs;

class SimpleAlgorithm {
  private:
    size_t n;
    size_t m;
    std::vector < size_t > L; // partial ordering of each node 
    std::vector < vs > adj; // adjacency list

    bool update_label(size_t, size_t);

  public:
    SimpleAlgorithm(size_t, size_t);
    bool insert_edge(size_t, size_t);
    bool precedes(size_t, size_t);
    std::vector < size_t > topsort(void);
};
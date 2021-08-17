#include <bits/stdc++.h>
#include <iostream>
#include <utility>
#include <memory>
#include <queue>

#include "TopSortAlgorithm.h"
#include "bst.h"

class BST;

typedef size_t Node;
typedef size_t Label;
typedef size_t Index;
typedef std::vector < Node > VectorNode;
typedef std::pair < Node, Label > VectorNodeLabel;
typedef std::pair < Node, Node > Edge;
typedef std::pair < Edge, size_t > EdgeIndex;
typedef std::pair < Label, Label > LabelLabel;
typedef std::pair < Node, LabelLabel > KeyCache;

class TopSortAlgorithm;

class IdealAlgorithm : TopSortAlgorithm {
  private:
    size_t n;
    size_t m;
    std::vector < Label > k;                              // partial ordering of each node
    std::vector < BST > k_in;                             // keeps k_in of incoming edges
    std::vector < std:: vector < KeyCache > > key_cache;  // keeps key caches of outgoing edges
    std::vector < VectorNode > adj;                       // adjacency list

  public:
    IdealAlgorithm(size_t, size_t);
    bool insert_edge(Node, Node);
    bool precedes(Node, Node);
    std::vector < Node > topsort(void);
};
#include <vector>

// typedef std::vector < size_t > vs;

// Base class
class TopSortAlgorithm {

  // private:
  //   size_t n;
  //   size_t m;
  //   std::vector < vs > adj; // adjacency list

  public:
    virtual bool precedes(size_t, size_t) = 0;
    virtual bool insert_edge(size_t, size_t) = 0;
    virtual std::vector < size_t > topsort(void) = 0;
};
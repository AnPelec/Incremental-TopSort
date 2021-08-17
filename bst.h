// Code was adopted by tutorialspoint

#include <bits/stdc++.h>
#include <memory>

struct Node {
    int pop; // number of descendants including itself
    int value;
    int max_score; // maximum score of subtree
    std::shared_ptr<struct Node> left, right, parent;
};

// Splay Tree implementation
// For our use every node must also hold the descendant that
// maximizes score = val + idx in non-decreasing order
class BST {
  public:
    std::shared_ptr<Node> root;

    BST() {
        root = nullptr;
    }
    void insert(std::shared_ptr<Node>, int);
    void erase(int);
    int get_max_score(std::shared_ptr<Node>);

  private:

    std::shared_ptr<Node> create_node();
    std::shared_ptr<Node> find(int);
    int get_pop(std::shared_ptr<Node>);
    void update_node(std::shared_ptr<Node>);

    void rotate_left(std::shared_ptr<Node>);
    void rotate_right(std::shared_ptr<Node>);
    
    void splay(std::shared_ptr<Node>);
};
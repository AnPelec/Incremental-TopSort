#include <bits/stdc++.h>
#include <iostream>
#include <iterator>
#include <utility>
#include <cassert>

#include "bst.h"

typedef std::function<bool()> testType;

bool testSimple1() {
    BST tree;
    tree.insert(tree.root, 1);
    tree.insert(tree.root, 1);
    tree.insert(tree.root, 1);
    tree.insert(tree.root, 1);
    tree.insert(tree.root, 6);
    
    if (tree.get_max_score(tree.root) != 7) return false;

    tree.erase(6);
    if (tree.get_max_score(tree.root) != 5) return false;
    
    return true;
}

bool testSimple2() {
    BST tree;
    tree.insert(tree.root, 2);
    tree.insert(tree.root, 2);
    tree.insert(tree.root, 2);
    tree.insert(tree.root, 2);
    tree.insert(tree.root, 2);
    
    if (tree.get_max_score(tree.root) != 7) return false;

    tree.insert(tree.root, 2);
    if (tree.get_max_score(tree.root) != 8) return false;

    tree.erase(2);
    if (tree.get_max_score(tree.root) != 7) return false;

    tree.erase(2);
    tree.insert(tree.root, 2);
    if (tree.get_max_score(tree.root) != 7) return false;
    
    return true;
}

bool testLargeConsecutive1() {
    BST tree;
    for (int i = 1; i < 1000; ++i) {
        tree.insert(tree.root, i);
        if (tree.get_max_score(tree.root) != i+1) return false;
    }
    
    return true;
}

bool testLargeConsecutive2() {
    BST tree;
    for (int i = 1000; i > 0; -- i) {
        tree.insert(tree.root, i);
        if (tree.get_max_score(tree.root) != i+1) return false;
        tree.erase(i);
        if (tree.get_max_score(tree.root) != 1) return false;
    }
    
    return true;
}

int main()
{   
    std::initializer_list<testType> testArray {testSimple1,
                                               testSimple2,
                                               testLargeConsecutive1,
                                               testLargeConsecutive2};

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
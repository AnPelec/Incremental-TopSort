#include "bst.h"

void BST::insert(std::shared_ptr<Node> t, int v) {
    if (root == nullptr) {
        root = create_node();
        root->pop = 1;
        root->value = v;
        root->max_score = v + 1;
        return;
    }
    
    std::shared_ptr<Node> curr = root;
    while (true) {
        if (v > curr->value) {
            if (curr->left != nullptr) curr = curr->left;
            else {
                curr->left = create_node();
                curr->left->parent = curr;
                curr->left->pop = 1;
                curr->left->value = v;
                curr->left->max_score = v+1;
                break;
            }
        } else {
            if (curr->right != nullptr) curr = curr->right;
            else {
                curr->right = create_node();
                curr->right->parent = curr;
                curr->right->pop = 1;
                curr->right->value = v;
                curr->right->max_score = v+1;
                break;
            }
        }
    }
    splay(curr);
}

void BST::erase(int v) {
    std::shared_ptr<Node> curr = find(v);
    if (curr == nullptr) return;

    splay(curr);

    std::shared_ptr<Node> p = curr->left;
    if (p == nullptr) {
        root = curr->right;
        if (root != nullptr)
            root->parent = nullptr;
        return;
    }

    while (p->right != nullptr) p = p->right;
    if (curr->right) {
        p->right = curr->right;
        curr->right->parent = p;
        // update parents
        std::shared_ptr<Node> pp = p;
        while(pp != nullptr) {
            update_node(pp);
            pp = pp->parent;
        }
    }
    root = curr->left;
    root->parent = nullptr;
}

std::shared_ptr<Node> BST::find(int v) {
    if (root == NULL) return NULL;
    
    std::shared_ptr<Node> curr = root;
    while (curr != nullptr) {
        if (curr->value == v) break;
        if (curr->value < v) curr = curr->left;
        else curr = curr->right;
    }
    splay(curr);
    return curr;
}

int BST::get_max_score(std::shared_ptr<Node> curr) {

    if (curr == nullptr)
        return 1; // TODO(apelecan): might want to make 0
    return curr->max_score;
}

int BST::get_pop(std::shared_ptr<Node> curr) {
    if (curr == nullptr)
        return 0;
    return curr->pop;
}

void BST::update_node(std::shared_ptr<Node> curr) {
    curr->pop = get_pop(curr->left) + get_pop(curr->right) + 1;
    int left_score = get_max_score(curr->left);
    int curr_score = curr->value + 1 + get_pop(curr->left);
    int right_score = get_max_score(curr->right) + 1 + get_pop(curr->left);
    curr->max_score = std::max(std::max(left_score, right_score), curr_score);
}

void BST::rotate_left(std::shared_ptr<Node> curr) {
    std::shared_ptr<Node> t = curr->right;
    std::shared_ptr<Node> b = t->left;
    std::shared_ptr<Node> d = curr->parent;
    
    if (d != nullptr) {
        if (d->right == curr) d->right = t;
        else d->left = t;
    }
    if (b != nullptr) b->parent = curr;

    curr->parent = t;
    curr->right = b;

    t->parent = d;
    t->left = curr;

    update_node(curr);
    update_node(t);
}

void BST::rotate_right(std::shared_ptr<Node> curr) {
    std::shared_ptr<Node> t = curr->left;
    std::shared_ptr<Node> b = t->right;
    std::shared_ptr<Node> d = curr->parent;
    
    if (d != nullptr) {
        if (d->right == curr) d->right = t;
        else d->left = t;
    }
    if (b != nullptr) b->parent = curr;

    curr->parent = t;
    curr->left = b;

    t->parent = d;
    t->right = curr;

    update_node(curr);
    update_node(t);
}

void BST::splay(std::shared_ptr<Node>curr) {
    if (curr == nullptr) return;

    update_node(curr);

    while (true) {
        std::shared_ptr<Node> next = curr->parent;
        if (next == nullptr) break;

        std::shared_ptr<Node> nextnext = next->parent;
        if (nextnext == nullptr) { // single rotation
            if (next->left == curr) rotate_right(next);
            else rotate_left(next);
            break;
        }

        if (nextnext->left == next) {
            if (next->left == curr) {
                rotate_right(nextnext);
                rotate_right(next);
            } else {
                rotate_left(next);
                rotate_right(nextnext);
            }
        } else {
            if (next->left == curr) {
                rotate_right(next);
                rotate_left(nextnext);
            } else {
                rotate_left(nextnext);
                rotate_left(next);
            }
        }
    }
    root = curr;
}

std::shared_ptr<Node> BST::create_node() {
    std::shared_ptr<Node> node(new Node);
    node->left = nullptr;
    node->right = nullptr;
    node->parent = nullptr;
    node->pop = 1;
    node->value = 0;
    node->max_score = 1;
    return node;
}
#pragma once
#include "tree.h"

using namespace std;

class BinarySearchTree: public BinaryTree {
public:
    BinarySearchTree() { };
    ~BinarySearchTree() { };

    int insert(int key);
    int remove(int key);

private:
    Node* _insert(Node* node, int key);
    Node* _remove(Node* node, int key);
    Node* _findMin(Node* node);
};
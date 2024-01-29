#pragma once
#include "bst.h"

using namespace std;

class AVLTree: public BinarySearchTree {
public:
    AVLTree() {};
    ~AVLTree() {};
    int insert(int key);
    int remove(int key);

private:
    int get_balance_factor(Node* node);
    Node* rebalance(Node* node);
    void balance(Node* node, int key);
    Node* LL(Node* node);
    Node* LR(Node* node);
    Node* RL(Node* node);
    Node* RR(Node* node);
    int check_if_one(Node* node);
    int height(Node* node);
    int checkleaf(Node* node);
    int getheight(Node* node);
};
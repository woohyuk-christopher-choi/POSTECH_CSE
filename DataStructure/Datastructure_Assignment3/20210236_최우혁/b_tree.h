#pragma once
#include <string>

using namespace std;


class BTreeNode {
public:
    int* keys;
    BTreeNode** children;
    int num_keys;
    bool is_leaf;
    BTreeNode* parent;

    BTreeNode(int order, bool is_leaf);
    ~BTreeNode();
};

class BTree {
public:
    int order;
    BTreeNode* root;

    BTree(int order);
    ~BTree();

    int has_elem(int key);
    int insert_elem(int key);
    int delete_elem(int key);
    string postOrder();

private:
    void splitChild(BTreeNode* parent, int child_index);
    void postOrderHelper(BTreeNode* node, string& result);
    int getPred(int index);
    int getSucc(int index);
    void borrowFromPrev(BTreeNode* parent, int child_index);
    void borrowFromNext(BTreeNode* parent, int child_index);
    void merge(BTreeNode* parent, int child_index);
    void removeFromLeaf(BTreeNode* node, int index);
    void removeFromNonLeaf(BTreeNode* node, int index);
    void fill(BTreeNode* node, int index);
};

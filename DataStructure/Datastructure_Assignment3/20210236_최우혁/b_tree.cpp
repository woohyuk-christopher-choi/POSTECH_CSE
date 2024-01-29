#include "b_tree.h"
#include <iostream>
#include <string>

using namespace std;

BTreeNode::BTreeNode(int order, bool is_leaf) {
    this->keys = new int[2*order -1];
    this->children = new BTreeNode*[2 * order];
    this->num_keys = 0;
    this->is_leaf = is_leaf;

    for (int i = 0; i < 2 * order; ++i) {
        this->children[i] = nullptr;
    }
}

BTreeNode::~BTreeNode() {
    delete[] keys;
    delete[] children;
}

BTree::BTree(int order) {
    this->order = order;
    this->root = new BTreeNode(order, true);
}

BTree::~BTree() {
    delete root;
}

void BTree::splitChild(BTreeNode* parent, int child_index) {
    BTreeNode* child = parent->children[child_index];
    BTreeNode* new_child = new BTreeNode(order, child->is_leaf);
    int median = order - 1;

    // Move keys from full child node to new child node
    for (int i = 0; i < median; ++i) {
        new_child->keys[i] = child->keys[i + median + 1];
        child->keys[i + median + 1] = 0;
    }

    // Move child nodes from full child node to new child node (if not a leaf node)
    if (!child->is_leaf) {
        for (int i = 0; i < median + 1; ++i) {
            new_child->children[i] = child->children[i + median + 1];
            child->children[i + median + 1] = nullptr;
        }
    }

    // Insert new child node into parent node
    for (int i = parent->num_keys; i > child_index; --i) {
        parent->children[i + 1] = parent->children[i];
    }
    parent->children[child_index + 1] = new_child;

    // Insert median key from full child node into parent node
    for (int i = parent->num_keys - 1; i >= child_index; --i) {
        parent->keys[i + 1] = parent->keys[i];
    }
    parent->keys[child_index] = child->keys[median];
    child->keys[median] = 0;

    // Update number of keys in child and parent nodes
    child->num_keys = median;
    new_child->num_keys = median;
    parent->num_keys += 1;
}


int BTree::getPred(int index) {
    BTreeNode* current = root->children[index];
    while (!current->is_leaf) {
        current = current->children[current->num_keys];
    }
    return current->keys[current->num_keys - 1];
}

int BTree::getSucc(int index) {
    BTreeNode* current = root->children[index + 1];
    while (!current->is_leaf) {
        current = current->children[0];
    }
    return current->keys[0];
}

void BTree::borrowFromPrev(BTreeNode* parent, int child_index) {
    BTreeNode* child = parent->children[child_index];
    BTreeNode* sibling = parent->children[child_index - 1];

    // Move keys and child nodes of child node to the right
    for (int i = child->num_keys - 1; i >= 0; --i) {
        child->keys[i + 1] = child->keys[i];
    }
    if (!child->is_leaf) {
        for (int i = child->num_keys; i >= 0; --i) {
            child->children[i + 1] = child->children[i];
        }
    }

    // Move key from parent node to child node
    child->keys[0] = parent->keys[child_index - 1];

    // Move rightmost key and child node of sibling node to the parent node and child node, respectively
    if (!sibling->is_leaf) {
        child->children[0] = sibling->children[sibling->num_keys];
    }
    parent->keys[child_index - 1] = sibling->keys[sibling->num_keys - 1];

    // Update number of keys in child and sibling nodes
    child->num_keys += 1;
    sibling->num_keys -= 1;
}

void BTree::borrowFromNext(BTreeNode* parent, int child_index) {
    BTreeNode* child = parent->children[child_index];
    BTreeNode* sibling = parent->children[child_index + 1];

    // Move key from parent node to child node
    child->keys[child->num_keys] = parent->keys[child_index];

    // Move leftmost key and child node of sibling node to the parent node and child node, respectively
    if (!sibling->is_leaf) {
        child->children[child->num_keys + 1] = sibling->children[0];
    }
    parent->keys[child_index] = sibling->keys[0];

    // Move keys and child nodes of sibling node to the left
    for (int i = 1; i < sibling->num_keys; ++i) {
        sibling->keys[i - 1] = sibling->keys[i];
    }
    if (!sibling->is_leaf) {
        for (int i = 1; i <= sibling->num_keys; ++i) {
            sibling->children[i - 1] = sibling->children[i];
        }
    }

    // Update number of keys in child and sibling nodes
    child->num_keys += 1;
    sibling->num_keys -= 1;
}

void BTree::merge(BTreeNode* parent, int child_index) {
    BTreeNode* child = parent->children[child_index];
    BTreeNode* sibling = parent->children[child_index + 1];

    // Move key from parent node to child node
    child->keys[order - 1] = parent->keys[child_index];

    // Move keys and child nodes of sibling node to the child node
    for (int i = 0; i < sibling->num_keys; ++i) {
        child->keys[i + order] = sibling->keys[i];
    }
    if (!child->is_leaf) {
        for (int i = 0; i <= sibling->num_keys; ++i) {
            child->children[i + order] = sibling->children[i];
        }
    }

    // Move keys and child nodes of parent node to the left
    for (int i = child_index + 1; i < parent->num_keys; ++i) {
        parent->keys[i - 1] = parent->keys[i];
    }
    for (int i = child_index + 2; i <= parent->num_keys; ++i) {
        parent->children[i - 1] = parent->children[i];
    }

    // Update number of keys in child and parent nodes
    child->num_keys += sibling->num_keys + 1;
    parent->num_keys -= 1;

    // Delete sibling node
    delete sibling;
}

void BTree::removeFromLeaf(BTreeNode* node, int index) {
    // Move keys to the left to fill the gap left by the removed key
    for (int i = index + 1; i < node->num_keys; ++i) {
        node->keys[i - 1] = node->keys[i];
    }

    // Update number of keys in node
    node->num_keys -= 1;
}

void BTree::removeFromNonLeaf(BTreeNode* node, int index) {
    int key = node->keys[index];

    // Case 1: If the child node to the left of the key has at least order keys, find its predecessor and replace the key with it
    if (node->children[index]->num_keys >= order) {
        int pred = getPred(index);
        node->keys[index] = pred;
        removeFromLeaf(node->children[index], pred);
    }
    // Case 2: If the child node to the right of the key has at least order keys, find its successor and replace the key with it
    else if (node->children[index + 1]->num_keys >= order) {
        int succ = getSucc(index);
        node->keys[index] = succ;
        removeFromLeaf(node->children[index + 1], succ);
    }
    // Case 3: Both children nodes have only order-1 keys, merge the key and the right child into the left child
    else {
        merge(node, index);
        removeFromNonLeaf(node->children[index], order - 1);
    }
}

void BTree::fill(BTreeNode* node, int index) {
    // Case 1: If the previous child node has more than order-1 keys, borrow a key from it
    if (index != 0 && node->children[index - 1]->num_keys >= order) {
        borrowFromPrev(node, index);
    }
    // Case 2: If the next child node has more than order-1 keys, borrow a key from it
    else if (index != node->num_keys && node->children[index + 1]->num_keys >= order) {
        borrowFromNext(node, index);
    }
    // Case 3: Both previous and next child nodes have only order-1 keys, merge the child node with one of its siblings
    else {
        if (index != node->num_keys) {
            merge(node, index);
        } else {
            merge(node, index - 1);
        }
    }
}

int BTree::has_elem(int key) {
    BTreeNode* cur = root;
    int index;
    while (cur) {
        // Check if the key is present in the current node
        for (index = 0; index < cur->num_keys; index++) {
            if (key == cur->keys[index]) {
                return 1;
            } else if (key < cur->keys[index]) {
                break;
            }
        }
        // If the key is not present in the current node, move to the appropriate child node
        cur = cur->children[index];
    }
    // Key not found
    return 0;
}

int BTree::insert_elem(int key) {
    // Case 1: B-tree is empty, create root node
    if (!root) {
        root = new BTreeNode(order, true);
        root->keys[0] = key;
        root->num_keys = 1;
        return 0;
    }
    // Case 2: B-tree is not empty, traverse the tree to find the appropriate leaf node
    BTreeNode* cur = root;
    while (!cur->is_leaf) {
        int index;
        for (index = 0; index < cur->num_keys; index++) {
            if (key < cur->keys[index]) {
                break;
            }
        }
        cur = cur->children[index];
    }
    // Case 3: Insert the key into the appropriate leaf node
    int index;
    for (index = 0; index < cur->num_keys; index++) {
        if (key == cur->keys[index]) {
            return 1; // Key already exists in the tree
        } else if (key < cur->keys[index]) {
            break;
        }
    }
    if (cur->num_keys < (2*order - 1)) {
        // Case 3a: Leaf node has room for the key, insert it
        for (int i = cur->num_keys; i > index; i--) {
            cur->keys[i] = cur->keys[i - 1];
        }
        cur->keys[index] = key;
        cur->num_keys++;
        return 0;
    } else {
        // Case 3b: Leaf node is full, split it and insert the key
        BTreeNode* new_node = new BTreeNode(order, true);
        int mid = (order - 1) / 2;
        if (index <= mid) {
            // Insert the key into the left half of the node
            for (int i = 0; i < mid; i++) {
                new_node->keys[i] = cur->keys[i + mid];
            }
            for (int i = mid; i > index; i--) {
                cur->keys[i] = cur->keys[i - 1];
            }
            cur->keys[index] = key;
        } else {
            // Insert the key into the right half of the node
            for (int i = 0; i < mid; i++) {
                new_node->keys[i] = cur->keys[i + mid + 1];
            }
            for (int i = cur->num_keys - 1; i >= index; i--) {
                cur->keys[i + 1] = cur->keys[i];
            }
            cur->keys[index] = key;
        }
        cur->num_keys = mid + 1;
        new_node->num_keys = order - mid - 1;
        // Link the new node to the parent node
        if (cur == root) {
            root = new BTreeNode(order, false);
            root->keys[0] = new_node->keys[0];
            root->children[0] = cur;
            root->children[1] = new_node;
            root->num_keys = 1;
        } else {
            BTreeNode* parent = cur->parent;
            int parent_index;
            for (parent_index = 0; parent_index < parent->num_keys; parent_index++) {
                if (cur->keys[0] < parent->keys[parent_index]) {
                    break;
                }
            }
            for (int i = parent->num_keys        ; i > parent_index; i--) {
            parent->keys[i] = parent->keys[i - 1];
        }
        for (int i = parent->num_keys + 1; i > parent_index + 1; i--) {
            parent->children[i] = parent->children[i - 1];
        }
        parent->keys[parent_index] = new_node->keys[0];
        parent->children[parent_index] = cur;
        parent->children[parent_index + 1] = new_node;
        parent->num_keys++;
        new_node->parent = parent;
    }
    return 0;
    }
}

int BTree::delete_elem(int key) {
    if (!root) {
        return 1; // Tree is empty
    }
    BTreeNode* cur = root;
    BTreeNode* parent = nullptr;
    int index;
    while (!cur->is_leaf) {
        parent = cur;
        for (index = 0; index < cur->num_keys; index++) {
            if (key < cur->keys[index]) {
                break;
            }
            if (key == cur->keys[index]) {
                index++;
                break;
            }
        }
        cur = cur->children[index];
    }
    // Now 'cur' is a leaf node that may contain the key to be deleted
    for (index = 0; index < cur->num_keys; index++) {
        if (key == cur->keys[index]) {
            break;
        }
    }
    if (index == cur->num_keys) {
        return 1; // Key not found in the tree
    }
    // Case 1: Leaf node has more than the minimum number of keys, simply delete the key
    if (cur->num_keys > order / 2 || cur == root) {
        removeFromLeaf(cur, index);
        return 0;
    }
    // Case 2: Leaf node has the minimum number of keys, try to borrow from a neighbor
    if (index > 0 && cur->parent->children[index - 1]->num_keys > order / 2) {
        borrowFromPrev(cur->parent, index);
        removeFromLeaf(cur, index);
        return 0;
    }
    if (index < cur->num_keys && cur->parent->children[index + 1]->num_keys > order / 2) {
        borrowFromNext(cur->parent, index);
        removeFromLeaf(cur, index);
        return 0;
    }
    // Case 3: Leaf node has the minimum number of keys and cannot borrow from a neighbor, merge with a neighbor
    if (index == cur->num_keys) {
        index--;
    }
    merge(cur->parent, index);
    removeFromLeaf(cur, index);
    return 0;
}

void BTree::postOrderHelper(BTreeNode* node, string& result) {
    if (!node) {
        return;
    }
    // 초기화
    result = "";
    for (int i = 0; i < node->num_keys; ++i) {
        postOrderHelper(node->children[i], result);
        postOrderHelper(node->children[i+1], result);
        result += to_string(node->keys[i]) + " ";
    }
}

string BTree::postOrder() {
    string result;
    postOrderHelper(root, result);
    return result;
}


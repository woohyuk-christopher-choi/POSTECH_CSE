#include "mst.h"
#include <iostream>
#include <string>

using namespace std;

string MultiWayTree::preOrder() {
  string output;
  _preOrder(output, _root);
  if (!output.empty())
    output.pop_back();
  return output;
}

void MultiWayTree::_preOrder(string& output, MultiNode *cur) {
  if(cur == NULL)
      return;

  output.append(cur->print_key());
  output.append(" ");
  _preOrder(output, cur->left);
  _preOrder(output, cur->middle);
  _preOrder(output, cur->right);
}

int MultiWaySearchTree::insert(int key){
    if (_root == nullptr){
        _root = new MultiNode();
        _root->key1 = key;
        return 0;
    }
    MultiNode* node = _root;

    while (node){
    if (key == node->key1 || key == node->key2){
        return -1;
    }
        if (key < node->key1){
            node = node->left;
        }
        else if(key > node->key1 && key < node->key2){
            node = node->middle;
        }
        else if(key > node->key2){
            node = node->right;
        }
    }

    _root = _insert(_root, key);
    return 0;
}


MultiNode* MultiWaySearchTree::_insert(MultiNode* curr, int key){
    if (curr == nullptr){
        MultiNode* newnode = new MultiNode();
        newnode->key1 = key;
        return newnode;
    }
    else if (curr->key1 != 0 && curr->key2 == 0){
        if (key < curr->key1){
            curr->key2 = curr->key1;
            curr->key1 = key;
        }
        else {
            curr->key2 = key;
        }
        return curr;
    }
    else if (curr->key1 != 0 && curr->key2 != 0){
        if(key < curr->key1){
            curr->left = _insert(curr->left, key);
        }
        else if (key > curr->key1 && key < curr->key2){
            curr->middle = _insert(curr->middle, key);
        }
        else if (key > curr->key2){
            curr->right = _insert(curr->right, key);
        }
    }

    return curr;

}


int MultiWaySearchTree::remove(int key) {
    MultiNode *cur = _root;
    MultiNode *parent = nullptr;

    while (cur != nullptr && (cur->key1 != key && cur->key2 != key)) {
        parent = cur;
        if (cur->key1 > key) {
            cur = cur->left;
        } else if (cur->key2 == 0 || cur->key2 > key) {
            cur = cur->middle;
        } else {
            cur = cur->right;
        }
    }

    if (cur == nullptr) {
        return -1;
    }

    if (cur->key1 == key) {
        if (cur->left == nullptr && cur->right == nullptr) {
            if (parent == nullptr) {
                _root = cur->middle;
            } else if (parent->left == cur) {
                parent->left = cur->middle;
            } else if (parent->middle == cur) {
                parent->middle = cur->middle;
            } else {
                parent->right = cur->middle;
            }
            delete cur;
        } 
        else {
            MultiNode *minNode = cur->right; // Changed from cur->middle to cur->right
            MultiNode *minParent = cur;
            while (minNode->left != nullptr) {
                minParent = minNode;
                minNode = minNode->left;
            }
            cur->key1 = minNode->key1;
            if (minParent->left == minNode) {
                minParent->left = minNode->middle;
            } else {
                minParent->middle = minNode->middle;
            }
            delete minNode;
        }
    } 
    else {
        if (cur->middle == nullptr && cur->right == nullptr) {
            if (parent == nullptr) {
                _root = cur->left;
            } else if (parent->left == cur) {
                parent->left = cur->left;
            } else if (parent->middle == cur) {
                parent->middle = cur->left;
            } else {
                parent->right = cur->left;
            }
            delete cur;
        } 
        else if (cur->right == nullptr) {
            cur->key2 = 0;
        } 
        else {
            MultiNode *maxNode = cur->middle;
            MultiNode *maxParent = cur;
            while (maxNode->right != nullptr) {
                maxParent = maxNode;
                maxNode = maxNode->right;
            }
            cur->key2 = maxNode->key2;
            if (maxNode->key2 == 0) {
                cur->key2 = maxNode->key1;
            }
            if (maxParent->right == maxNode){
                maxParent->right = maxNode->middle;
            }
            else{
                maxParent->middle = maxNode->middle;
            }
            delete maxNode;
        }
    }
    return key;
}


#include "tree.h"
#include "bst.h"
#include "dabst.h"
#include <iostream>
#include <string>

using namespace std;

string DABSTree::inOrder() {
  string output;
  _inOrder(output, _root);
  if (!output.empty())
    output.pop_back();
  return output;
}

string DABSTree::preOrder() {
  string output;
  _preOrder(output, _root);
  if (!output.empty())
    output.pop_back();
  return output;
}
  
void DABSTree::_inOrder(string& output, Node *cur) {
  if(cur == NULL)
      return;
  _inOrder(output, cur->left);
  output.append(cur->print_key());
  output.append("(");
  output.append(cur->print_count());
  output.append(")");
  output.append(" ");
  _inOrder(output, cur->right);
}

void DABSTree::_preOrder(string& output, Node *cur) {
  if(cur == NULL)
      return;
  output.append(cur->print_key());
  output.append("(");
  output.append(cur->print_count());
  output.append(")");
  output.append(" ");
  _preOrder(output, cur->left);
  _preOrder(output, cur->right);
}

Node* DABSTree::_insert(Node* node, int key){
  if (node == nullptr){
    node = new Node(key);
  }
  else if (key == node->key){
    node->count++;
  }
  else if (key < node->key){
    node->left = _insert(node->left, key);
  }
  else {
    node->right = _insert(node->right, key);
  }
  return node;
}

int DABSTree::find(int key) {
    Node* cur = _root;
    while (cur != NULL) {
        if (key == cur->key) {
            return cur->count;
        }
        else if (key < cur->key) {
            cur = cur->left;
        }
        else {
            cur = cur->right;
        }
    }
    return 0;
}

Node* DABSTree::minValueNode(Node* node) {
    Node* cur = node;
    while (cur->left != NULL) {
        cur = cur->left;
    }
    return cur;
}

int DABSTree::insert(int key){
  if (find(key)){
    _insert(_root, key);
    return _root->count;
  }
  else{
    _root = _insert(_root, key);
    return 1;
  }
}

Node* DABSTree::_remove(Node* node, int key) {
    if (node == NULL) {
        return node;
    }
    if (key < node->key) {
        node->left = _remove(node->left, key);
    }
    else if (key > node->key) {
        node->right = _remove(node->right, key);
    }
    else {
        if (node->count > 1) {
            node->count--;
        }
        else {
            if (node->left == NULL) {
                Node* temp = node->right;
                delete node;
                return temp;
            }
            else if (node->right == NULL) {
                Node* temp = node->left;
                delete node;
                return temp;
            }
            Node* temp = minValueNode(node->right);
            node->key = temp->key;
            node->count = temp->count;
            node->right = _remove(node->right, temp->key);
        }
    }
    return node;
}

int DABSTree::remove(int key) {
    if (!find(key)) {
        return -1;
    }
    else {
        _remove(_root, key);
        if (_root == NULL) {
            return 0;
        }
        return _root->count;
    }
}


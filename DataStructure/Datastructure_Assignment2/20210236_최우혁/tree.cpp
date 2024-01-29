#include "tree.h"
#include <iostream>
#include <cstring>
#include <string>
#include <cmath>

using namespace std;

/* This is given function. DO NOT MODIFY THIS FUNCTION */
int findIndex(const char *str, int start, int end) {
  if (start > end)
    return -1;

  string s;

  for (int i = start; i <= end; i++) {

    // if open parenthesis, push it
    if (str[i] == '(')
      s.push_back(str[i]);

    // if close parenthesis
    else if (str[i] == ')') {
      if (s.back() == '(') {
        s.pop_back();

        if (!s.length())
          return i;
      }
    }
  }
  // if not found return -1
  return -1;
}

/* This is given function. DO NOT MODIFY THIS FUNCTION */
Node *BinaryTree::_buildFromString(const char *data, int start, int end) {
  if (start > end)
    return NULL;

  Node *root = new Node(data[start]);
  int index = -1;

  if (start + 1 <= end && data[start + 1] == '(') // if the first node is not the end and start with bracket, 
    index = findIndex(data, start + 1, end);

  if (index != -1) {
    root->left = _buildFromString(data, start + 2, index - 1);
    root->right = _buildFromString(data, index + 2, end - 1);
  }
  return root;
}

/* This is given function. DO NOT MODIFY THIS FUNCTION */
void BinaryTree::buildFromString(const char *data) {
  Node *root = _buildFromString(data, 0, strlen(data) - 1);
  _root = root;
}

string BinaryTree::preOrder(int node_value) {
  string answer;
  _preorder(_root, node_value, answer);
  return answer;
}

string BinaryTree::postOrder(int node_value) {
  string answer;
  _postorder(_root, node_value, answer);
  return answer;
}

string BinaryTree::inOrder(int node_value) {
  string answer;
  _inorder(_root, node_value, answer);
  return answer;
}

int BinaryTree::getDepth(int node_value) {
  if (_root == nullptr){
    return -1;
  }
  return findDepth(_root, node_value, 0);
}

bool BinaryTree::isReverseComplete() {

  Node* cur = _root;

  int totalnode = countnode();
  int level = 0;

  if (cur == nullptr){
    return false;
  }

  while (cur != nullptr){
    level++;
    if(cur->left != nullptr){
      if(level == pow(2, ceil(log2(totalnode))) -1){
        return false;
      }

      cur = cur->left;
    }
    else if (cur->right != nullptr){
      return false;
    }
    else{
      if (level != pow(2, ceil(log2(totalnode))) -1){
        return false;
      }

      totalnode = totalnode - (pow(2,ceil(log2(totalnode-level+1))) -1);
      level = 0;
      cur = cur->right;
    }
  }
  return true;
}


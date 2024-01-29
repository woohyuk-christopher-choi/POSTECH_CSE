#pragma once
#include <string>

using namespace std;

struct Node {
  Node(char input_value) : value(input_value), left(NULL), right(NULL) {}
  char value;
  Node *left;
  Node *right;
};

class BinaryTree {
public:
  BinaryTree() { _root = NULL; };
  ~BinaryTree() {
    delete[] _root;
    _root = NULL;
  };
  void buildFromString(const char *data);

  string preOrder(int node_value);
  string postOrder(int node_value);
  string inOrder(int node_value);
  int getDepth(int node_value);
  bool isReverseComplete();

private:
  Node *_root;
  Node *_buildFromString(const char *data, int start, int end);
  void __postorder(Node *node , string &tree){
    if (node == nullptr){
      return;
    }
    else{
      __postorder(node->left, tree);
      __postorder(node->right, tree);
      tree += node->value;
      tree += " ";
    }
  }
  void _postorder(Node* node, int node_value, string& tree){
    if (node == nullptr){
      return;
    }
    if(node->value != char(node_value+48)){
      _postorder(node->left, node_value, tree);
      _postorder(node->right, node_value, tree);
    }
    else{
      __postorder(node, tree);
    }
  }

  void __preorder(Node *node , string &tree){
    if (node == nullptr){
      return;
    }
    else{
      tree += node->value;
      tree += " ";
      __preorder(node->left, tree);
      __preorder(node->right, tree);
    }
  }
  void _preorder(Node* node, int node_value, string& tree){
    if (node == nullptr){
      return;
    }
    if(node->value != char(node_value+48)){
      _preorder(node->left, node_value, tree);
      _preorder(node->right, node_value, tree);
    }
    else{
      __preorder(node, tree);
    }
  }

  void __inorder(Node *node , string &tree){
    if (node == nullptr){
      return;
    }
    else{
      __inorder(node->left, tree);
      tree += node->value;
      tree += " ";
      __inorder(node->right, tree);
    }
  }
  void _inorder(Node* node, int node_value, string& tree){
    if (node == nullptr){
      return;
    }
    if(node->value != char(node_value+48)){
      _inorder(node->left, node_value, tree);
      _inorder(node->right, node_value, tree);
    }
    else{
      __inorder(node, tree);
    }
  }

  int findDepth(Node* node, int val, int depth){
    int ld = 0, rd = 0;

    if(node == nullptr){
      return -1;
    }
    if (node->value == char(val+48)){
      return depth;
    }
    else{
      ld = findDepth(node->left, val, depth+1);
      rd = findDepth(node->right, val, depth+1);
      if (ld != -1){
        return ld;
      }
      else if(rd != -1){
        return rd;
      }
      else{
        return -1;
      }
    }
  }

  int _countnode(Node* node){
    if (node == nullptr){
      return 0;
    }

    return (1+_countnode(node->left) + _countnode(node->right));
  }

  int countnode(){
    return _countnode(_root);
  }
  
  
};

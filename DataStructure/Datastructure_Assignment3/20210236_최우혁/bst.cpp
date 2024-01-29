#include "tree.h"
#include "bst.h"
#include <iostream>
#include <string>

using namespace std;



int BinarySearchTree::insert(int key) {

    _root = _insert(_root, key);

    return 0;

}

Node* BinarySearchTree::_insert (Node* node, int key){
    if(node == NULL){
        return new Node(key);
    }

    if (key < node -> key){
        node -> left = _insert(node->left, key);
        node -> right = _insert(node->right, key);
    }
    else{
        node->count ++;
    }
    return node;
}

int BinarySearchTree::remove(int key) {

    Node* node = _remove(_root, key);
    if (node == nullptr){
        return 0;
    }
    else{
        return node->count;
    }

}

Node* BinarySearchTree::_remove(Node* node, int key){
    if (node == nullptr){
        return nullptr;
    }

    if (key < node->key){
        node->left = _remove(node->left , key);
    }
    else if (key > node->key){
        node->right = _remove(node->right , key);
    }
    else{
        if (node->count > 1){
            node->count --;
            return node;
        }
        if (node->left == NULL && node->right == NULL){
            delete node;
            node = nullptr;
        }
        else if (node -> left == nullptr){
            Node* temp = node;
            node = node->right;
            delete temp;
        }
        else if (node -> right == nullptr){
            Node* temp = node;
            node = node->left;
            delete temp;
        }
        else {
            Node* temp = _findMin(node->right);
            node->key = temp->key;
            node->count = temp->count;
            node->right = _remove(node->right , temp->key);
        }
    }
    return node;
}

Node* BinarySearchTree::_findMin (Node* node){
    while(node->left != nullptr){
        node = node->left;
    }
    return node;
}

#include "tree.h"
#include "bst.h"
#include "avl.h"
#include <iostream>
#include <string>

using namespace std;

int AVLTree::height(Node* node) {
    if (node == nullptr){
        return -1;
    }
    else{
        return node->height;
    }
}

int AVLTree::get_balance_factor(Node* node){
    int bf = height(node->left) - height(node->right);
    return bf;
}

Node* AVLTree::rebalance(Node* node){
    if(node == nullptr){
        return nullptr;
    }

    node->left = rebalance(node->left);
    node->right = rebalance(node->right);

    int balance_factor = get_balance_factor(node);

    if(-1 <= balance_factor && balance_factor <= 1){
        return node;
    }

    else if (balance_factor > 1){
        node = (get_balance_factor(node->left) > 0) ? LL(node) : LR(node);
        return node;
    }

    node = (get_balance_factor(node->right) < 0) ? RR(node) : RL(node);
    return node;
}

Node *AVLTree::LL(Node* node) {
    Node* parentnode = node;
    Node* childrennode = parentnode->left;
    parentnode->left = childrennode->right;
    childrennode->right = parentnode;
    return childrennode;
}

Node* AVLTree::LR(Node* node) {
    Node* parentnode = node;
    Node* childrennode = parentnode->left;
    parentnode->left = RR(childrennode);
    return LL(parentnode);
}


Node* AVLTree::RL(Node* node) {
    Node* parentnode = node;
    Node* childrennode = parentnode->right;
    parentnode->right = LL(childrennode);
    return RR(parentnode);
}

Node* AVLTree::RR(Node* node) {
    Node* parentnode = node;
    Node* childrennode = parentnode->right;
    parentnode -> right = childrennode->left;
    childrennode->left = parentnode;
    return childrennode;
}

int AVLTree::check_if_one(Node* cur) {
    if (cur->left == nullptr || cur->right == nullptr){
         return 1;
    }
    else {
       return 0;
    }
}


int AVLTree::checkleaf(Node* cur) {
    if (cur->left == nullptr && cur->right == nullptr) {
        return 1;
    }
    else {
        return 0;
    }
}

int AVLTree::getheight(Node* node) {

    int left_height;
    int right_height;

    if (node == nullptr){
        return -1;
    } 

    left_height = getheight(node->left);
    right_height = getheight(node->right);

    if (left_height > right_height) {
        node->height = left_height + 1;
        return node->height;
    }

    else {
        node->height = right_height + 1;
        return node->height;
    }
}


int AVLTree::insert(int key) {
    Node* newnode = new Node(key);
    Node* current = _root;
    Node* parent = _root;

    if (_root == nullptr){
        _root = newnode;
        getheight(_root);
        return 0;
    }

    else if (_root->key == key){
        return -1;
    }

    while (true){
        if (key < current->key){
            if (current->left == nullptr){
                current->left = newnode;

                break;
            }
            else{
                current = current->left;
            }
        }
        else if (key > current->key){
            if (current->right == nullptr){
                current->right = newnode;
                break;
            }
            else current = current->right;
        }
        else{
            return -1;
        }
    }

    getheight(_root);
    _root = rebalance(_root);
    getheight(_root);

    return 0;
}

int AVLTree::remove(int key) {

    if (_root == nullptr){
        return -1;
    }

    Node* current = _root;
    Node* parent = _root;
    bool left = false;
    bool right = false;

    while(true){
        if(key < current->key){
            if (current->left == nullptr){
                return -1;
            }
            else {
                parent = current;
                current = current->left;
                right = false;
                left = true;
            }
        }

        else if (key > current->key){
            if (current->right == nullptr){
                return -1;
            }
            else {
                parent = current;
                current = current->right;
                right = true;
                left = false;
            }
        }

        else {
            if (checkleaf(current)){
                if(right){
                    parent->right = nullptr;
                }
                else if (left){
                    parent->left = nullptr;
                }
                else {
                    _root = nullptr;
                }
                break;
            }

            else if (check_if_one(current)){
                if (current->left != nullptr){
                    current = current->left;
                    if (right){
                        parent->right = current;
                    }
                    else if (left){
                        parent->left = current;
                    }
                    break;
                }

                else if (current->right != nullptr){
                    current = current->right;
                    if (right){
                        parent->right = current;
                    }
                    else if (left){
                        parent->left = current;
                    }
                    break;
                }
            }
            
            else {
                Node* deletenode = current;
                parent = current;
                current = current->right;
                right = true;
                left = false;

                while(current->left != nullptr){
                    parent = current;
                    current = current->left;
                    right = false;
                    left = true;
                }

                int temp = deletenode->key;
                deletenode->key = current->key;
                current->key = temp;

                if (left){
                    parent->left = nullptr;
                }
                else if (right){
                    parent->right = nullptr;
                }
                else{
                    current = nullptr;
                }
                break;
            }
        }
    }

    getheight(_root);
    _root = rebalance(_root);
    getheight(_root);
    return 0;
}

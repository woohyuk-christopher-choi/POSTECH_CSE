#pragma once
#include <string>

using namespace std;

class MultiNode {
public:
    MultiNode() : key1(0), key2(0), height(0), left(NULL), middle(NULL), right(NULL) {}
    int key1;
    int key2;
    int height;
    MultiNode *left;
    MultiNode *middle;
    MultiNode *right;
    /* Add public members if required*/

    string print_key() {
    /////////////////////////////////////////////////////////
    //////////  TODO: Implement From Here      //////////////
    if (key1 == 0 && key2 == 0){
        return " ";
    }
    else if (key1 != 0 && key2 == 0){
        return to_string(key1);
    }
    else if (key1 == 0 && key2 != 0){
        return to_string(key2);
    }
    else{
        return to_string(key1) + " " + to_string(key2);
    }
    ///////////      End of Implementation      /////////////
    ///////////////////////////////////////////////////////
    };
};

class MultiWayTree {
public:
    MultiWayTree() { _root = NULL; };
    ~MultiWayTree() {
        delete[] _root;
        _root = NULL;
    };
    string preOrder();

protected:
    MultiNode *_root;

private:
    void _preOrder(string& output, MultiNode *cur);
};

class MultiWaySearchTree: public MultiWayTree {
public:
    MultiWaySearchTree() { };
    ~MultiWaySearchTree() { };

    int insert(int key);
    int remove(int key);

private:
    /////////////////////////////////////////////////////////
    //////  TODO: Add private members if required ///////////
    MultiNode* _insert(MultiNode* curr, int key);
    MultiNode* _remove(MultiNode* curr, MultiNode* par, int key);
    MultiNode* _findmin(MultiNode* cur);
    MultiNode* _findmax(MultiNode* cur);
    

    ///////////      End of Implementation      /////////////
    /////////////////////////////////////////////////////////
};
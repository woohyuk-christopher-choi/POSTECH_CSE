#ifndef NODE_HPP_
#define NODE_HPP_

#include <string>
#include "student.hpp"


class node{
public:
    student data;
    node *next;
    node(student data); 
}; // Considering 'bout Linked list..

#endif
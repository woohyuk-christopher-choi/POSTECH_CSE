#ifndef LIST_HPP_
#define LIST_HPP_

#include <string>
#include "node.hpp"
#include "student.hpp"

class list{
    public:
        int count, dept_cnt;
        std::string dept[9];
        node *head;
        list();
        void sort(std::string metric);//This is function that sorts each nodes.
        void addstudent();
        void deletestudent();
        void printstudent();
        void table();
        void pivotDept();
        void pivotGender();
        void pivotDeptGender();//I mainly declare all the important functions in the list class.
};

#endif
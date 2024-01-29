#ifndef STUDENT_HPP_
#define STUDENT_HPP_

#include <string>

const int MAX_DEPT_STUDENT = 10000;

class student // class declaration
{
private:
    std::string Dept;
    std::string Gender;
    std::string Name;
    int Age;

public:
    student(const std::string& Dept, const std::string& Gender, const std::string& Name, int Age)
    : Dept(Dept), Gender(Gender), Name(Name), Age(Age) {} // this initialisation solves some problems.
    std::string getDept(){return Dept;}
    std::string getGender(){return Gender;}
    std::string getName(){return Name;} 
    int getAge(){return Age;} // Since Dept, Gender, Name, Age is in private region, we should use getter function.
};

#endif
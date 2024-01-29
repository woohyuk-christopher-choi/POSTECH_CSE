#include <iostream>
#include <cmath>
#include <string>
#include "student.hpp"
#include "node.hpp"
#include "list.hpp"


node::node(student data) : data(data), next(nullptr){
    this->data = data;
    this->next = nullptr;
} // By initialiser, I solved error.

list::list(){
    count = 0;
    dept_cnt = 0;
    head = nullptr;
} // By initialiser, I solved error.

void list::addstudent(){
    std::string Dept, Gender, Name;
    int Age;
    int check = 0;

    if(dept_cnt > MAX_DEPT_STUDENT){
        std::cout << "Too many students in this dept!"<<std::endl;
        return;
    }


    std::cout << "Dept: ";
    std::cin >> Dept;
    std::cout << "Gender: ";
    std::cin >> Gender;
    std::cout << "Name: ";
    std::cin >> Name;
    std::cout << "Age: ";
    std::cin >> Age;
    
    for (int i = 0; i < Dept.size(); i++){
        if(islower(Dept[i])){
            check = 1;
            break;
        }
    }//If there's lower alphabet, display error.

    for (int i = 0; i< Dept.size() ; i++){
        if(Dept[i] == ' '){
            check = 1;
            break;
        }
    }//If there's space, display error.

    for (int i = 0; i< Gender.size() ; i++){
        if(Gender[i] == ' '){
            check = 1;
            break;
        }
    }//If there's space, display error.

    for (int i = 0; i< Name.size() ; i++){
        if(Name[i] == ' '){
            check = 1;
            break;
        }
    }//If there's space, display error.

    if(Gender != "M" && Gender != "F"){
        check = 1;
    }//If gender is not M or F, error.

    if(Age < 18 || Age > 30){
        check = 1;
    }// If Age is not in valid boundary, error.

    if (check == 1){
        std::cout << "Invalid Input. Try it again." << std::endl;
        return;
    }//Error display.

    bool existence = false;
    for (node* curr = head; curr != nullptr; curr = curr->next){
        if (curr->data.getDept() == Dept && curr->data.getGender() == Gender && 
        curr->data.getName() == Name && curr->data.getAge() == Age){
            existence = true;
            break;
        }
    }//If all the information is same, make the boolean variable, existence , to be  a True value.
    if (existence){
        std::cout << "The student already exists" << std::endl;
    }
    else{
        student Student(Dept, Gender, Name, Age);
        node* insert = new node(Student);
        insert->next = head;
        head = insert;
        count++;
        bool Deptexistence = false;
        for(int i=0 ; i < dept_cnt; ++i){
            if (dept[i] == Dept){
                Deptexistence = true;
                break;
            }
        }
        if (!Deptexistence){
            dept[dept_cnt++] = Dept;
        }
        std::cout << "A student is added in list!" << std::endl;
    }
}

void list::deletestudent(){
    std::string Dept, Name, Gender;
    int Age;

    std::cout << "Dept: ";
    std::cin >> Dept;
    std::cout << "Gender: ";
    std::cin >> Gender;
    std::cout << "Name: ";
    std::cin >> Name;
    std::cout << "Age: ";
    std::cin >> Age;

    bool existence = false;

    node* prev = nullptr;
    node* curr = head;

    while (curr != nullptr){
        if(curr->data.getDept() == Dept && curr->data.getGender() == Gender 
        && curr->data.getName() == Name && curr->data.getAge() == Age){
            existence = true;
            break;
        }//check if the student is in the list
        prev = curr;
        curr = curr->next; 
    }
    if (existence){
        if(prev == nullptr){
            head = curr->next;
        }
        else{
            prev->next = curr->next;
        }
        delete curr; // Release Dynamic allocation memory (this is important one for memory problem)
        count--;
        std::cout << "Deleted!" << std::endl;
    }
    else{
        std::cout << "Can't Delete it" << std::endl;
    }
}

void list::printstudent(){
    std::cout << "Dept\t";
    std::cout << "Gender\t";
    std::cout << "Name\t";
    std::cout << "Age" << std::endl;

    sort("Age");
    sort("Name");
    sort("Gender");
    sort("Dept"); // by using four sort function, sorting completed. 

    for (node* curr = head; curr != nullptr; curr = curr->next){
        std::cout << curr->data.getDept() << "\t" << curr->data.getGender() 
        << "\t" << curr->data.getName() << "\t" << curr->data.getAge() << std::endl;
    }
}

void list::table(){
    int SelectionNumber = 0;
    std::cout << "----------Category----------" << std::endl;
    std::cout << "1. Dept" << std::endl;
    std::cout << "2. Gender" << std::endl;
    std::cout << "3. Dept and Gender" << std::endl;
    std::cout << "----------------------------" << std::endl;
    std::cout << "Selection: ";
    std::cin  >> SelectionNumber;
    if (!std::cin) { 
            std::cout << "Invalid input. Please enter a valid selection." << std::endl;
            std::cin.clear();
            std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
        } // if input is not a integer, error.
    switch(SelectionNumber){
            case 1: pivotDept(); break;
            case 2: pivotGender(); break;
            case 3: pivotDeptGender(); break;
            default: std::cout << "That's the wrong approach. Try it again." << std::endl;
        }

}

void list::pivotDept(){
    int cnt[9] = {0};
    int sum[9] = {0};
    int max[9] = {0};
    int min[9] = {99,99,99,99,99,99,99,99,99};
    node* curr = head;

    int SelectionNumber = 0;
    std::cout << "----------Function----------" << std::endl;
    std::cout << "1. Average" << std::endl;
    std::cout << "2. Max" << std::endl;
    std::cout << "3. Min" << std::endl;
    std::cout << "----------------------------" << std::endl;
    std::cout << "Selection: ";
    std::cin  >> SelectionNumber;

    if (!std::cin) { 
            std::cout << "Invalid input. Please enter a valid selection." << std::endl;
            std::cin.clear();
            std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
        } // if input is not a integer, error.

    if (SelectionNumber == 1){

        while(curr != NULL){
            for(int i=0 ; i<9; i++){
                if (curr->data.getDept() == dept[i]){
                    cnt[i]++;
                    sum[i] += curr->data.getAge();
                }
            }
            curr = curr->next;
        }

        std::cout << "Dept" << "\t" << "Average" << std::endl;

        for (int i = 0 ; i < 9 ; i++){
            if (cnt[i] > 0){
                float average = (float)sum[i] / cnt[i];
                std::cout << dept[i] << "\t" << round(average*10)/10 << std::endl;
            }
        } // print average.
    }

    else if (SelectionNumber == 2){

        while(curr != NULL){
            for(int i=0 ; i<9; i++){
                if (curr->data.getDept() == dept[i]){
                    cnt[i]++;
                    if (max[i] < curr->data.getAge()){
                    max[i] = curr->data.getAge();}
                }
            }
            curr = curr->next;
        }

        std::cout << "Dept" << "\t" << "Max" << std::endl;

        for (int i = 0 ; i < 9 ; i++){
            if (cnt[i] > 0){
                
                std::cout << dept[i] << "\t" << max[i] << std::endl;
            }
        } // print maximum.
    }

    else if (SelectionNumber == 3){

        while(curr != NULL){
            for(int i=0 ; i<9; i++){
                if (curr->data.getDept() == dept[i]){
                    cnt[i]++;
                    if (min[i] > curr->data.getAge()){
                    min[i] = curr->data.getAge();}
                }
            }
            curr = curr->next;
        }

        std::cout << "Dept" << "\t" << "Min" << std::endl;

        for (int i = 0 ; i < 9 ; i++){
            if (cnt[i] > 0){
                std::cout << dept[i] << "\t" << min[i] << std::endl;
            }
        } // print minimum.
    }
    else {
        std::cout << "Invalid input. Please enter a valid selection." << std::endl;
    }

    
}

void list::pivotGender(){
    int Numberofmale = 0;
    int Sumageofmale = 0;
    int Numberoffemale = 0;
    int Sumageoffemale = 0;
    int maxmale = 0;
    int maxfemale = 0;
    int minmale = 99;
    int minfemale = 99;
    node* curr = head;

    int SelectionNumber = 0;
    std::cout << "----------Function----------" << std::endl;
    std::cout << "1. Average" << std::endl;
    std::cout << "2. Max" << std::endl;
    std::cout << "3. Min" << std::endl;
    std::cout << "----------------------------" << std::endl;
    std::cout << "Selection: ";
    std::cin  >> SelectionNumber;

    if (!std::cin) { 
            std::cout << "Invalid input. Please enter a valid selection." << std::endl;
            std::cin.clear();
            std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
        } // if input is not a integer, error.

    if (SelectionNumber == 1){
 
        while(curr != NULL){
            if (curr->data.getGender() == "M"){
                Numberofmale++;
                Sumageofmale += curr->data.getAge();
            }
            if (curr->data.getGender() == "F"){
                Numberoffemale++;
                Sumageoffemale += curr->data.getAge();
            }
            curr = curr->next;
        }

        std::cout << "Gender" << "\t" << "Average" << std::endl;
        if(Numberoffemale > 0){
            std::cout << "F" << "\t" << round(((float)Sumageoffemale / Numberoffemale)*10)/10 << std::endl;
        }

        if(Numberofmale > 0){
            std::cout << "M" << "\t" << round(((float)Sumageofmale / Numberofmale)*10)/10 << std::endl;
        }
    }

    else if(SelectionNumber == 2){

        while(curr != NULL){
            if (curr->data.getGender() == "M"){
                Numberofmale++;
                if (maxmale < curr->data.getAge()){
                maxmale = curr->data.getAge();}
            }
            if (curr->data.getGender() == "F"){
                Numberofmale++;
                if (maxfemale < curr->data.getAge()){
                maxfemale = curr->data.getAge();}
            }
            curr = curr->next;
        }

        std::cout << "Gender" << "\t" << "Max" << std::endl;
        if(Numberoffemale > 0){
            std::cout << "F" << "\t" << maxfemale << std::endl;
        }

        if(Numberofmale > 0){
            std::cout << "M" << "\t" << maxmale << std::endl;
        }
    }

    else if(SelectionNumber == 3){

        while(curr != NULL){
            if (curr->data.getGender() == "M"){
                Numberofmale++;
                if (minmale < curr->data.getAge()){
                minmale = curr->data.getAge();}
            }
            if (curr->data.getGender() == "F"){
                Numberofmale++;
                if (minfemale < curr->data.getAge()){
                minfemale = curr->data.getAge();}
            }
            curr = curr->next;
        }

        std::cout << "Gender" << "\t" << "Min" << std::endl;
        if(Numberoffemale > 0){
            std::cout << "F" << "\t" << minfemale << std::endl;
        }

        if(Numberofmale > 0){
            std::cout << "M" << "\t" << minmale << std::endl;
        }
    }

    else {
        std::cout << "Invalid input. Please enter a valid selection." << std::endl;
    }
}

void list::pivotDeptGender(){
    int deptstudent[9][2]={{0}};
    double AgesumofDeptGender[9][2] = {{0}};
    int maxDepGender[9][2] = {{0}};
    int minDepGender[9][2] = {{99,99},{99,99},{99,99},{99,99},{99,99},{99,99},{99,99},{99,99},{99,99}};
    node* curr = head;

    int SelectionNumber = 0;
    std::cout << "----------Function----------" << std::endl;
    std::cout << "1. Average" << std::endl;
    std::cout << "2. Max" << std::endl;
    std::cout << "3. Min" << std::endl;
    std::cout << "----------------------------" << std::endl;
    std::cout << "Selection: ";
    std::cin  >> SelectionNumber;

    if (!std::cin) { 
            std::cout << "Invalid input. Please enter a valid selection." << std::endl;
            std::cin.clear();
            std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
        } // if input is not a integer, error.

    if (SelectionNumber == 1){

        while(curr != NULL){
            int deptindex = -1;
            for (int i = 0; i < 9; i++){
                if (curr->data.getDept() == dept[i]){
                    deptindex = i;
                    break;
                }
            }
            if (deptindex != -1){
                if(curr->data.getGender() == "M"){
                    deptstudent[deptindex][1]++;
                    AgesumofDeptGender[deptindex][1] += curr->data.getAge(); 
                }
                else if(curr->data.getGender() == "F"){
                    deptstudent[deptindex][0]++;
                    AgesumofDeptGender[deptindex][0] += curr->data.getAge(); 
                }
            }
            curr = curr->next;
        }

        std::cout << "Dept" << "\t" << "Gender" << "\t" << "Average" << std::endl;

        for (int i = 0; i < 9 ; i++){
            if (deptstudent[i][0] > 0){
            std::cout << dept[i] << "\t" << "F" << "\t" << round(AgesumofDeptGender[i][0] / deptstudent[i][0] *10)/10 << std::endl;
            }
            if (deptstudent[i][1] > 0){
                std::cout << dept[i] << "\t" << "M" << "\t" << round(AgesumofDeptGender[i][1] / deptstudent[i][1] *10)/10 << std::endl;
            }
        }
    }

    else if (SelectionNumber == 2){

        while(curr != NULL){
            int deptindex = -1;
            for (int i = 0; i < 9; i++){
                if (curr->data.getDept() == dept[i]){
                    deptindex = i;
                    break;
                }
            }
            if (deptindex != -1){
                if(curr->data.getGender() == "M"){
                    deptstudent[deptindex][1]++;
                    if (maxDepGender[deptindex][1] < curr->data.getAge()){
                        maxDepGender[deptindex][1] = curr->data.getAge();}
                }
                else if(curr->data.getGender() == "F"){
                    deptstudent[deptindex][0]++;
                    if (maxDepGender[deptindex][0] < curr->data.getAge()){
                        maxDepGender[deptindex][0] = curr->data.getAge();}
                }
            }
            curr = curr->next;
        }

        std::cout << "Dept" << "\t" << "Gender" << "\t" << "Max" << std::endl;

        for (int i = 0; i < 9 ; i++){
            if (deptstudent[i][0] > 0){
            std::cout << dept[i] << "\t" << "F" << "\t" << maxDepGender[i][0]<< std::endl;
            }
            if (deptstudent[i][1] > 0){
                std::cout << dept[i] << "\t" << "M" << "\t" << maxDepGender[i][1] << std::endl;
            }
        }
    }

    else if (SelectionNumber == 3){

        while(curr != NULL){
            int deptindex = -1;
            for (int i = 0; i < 9; i++){
                if (curr->data.getDept() == dept[i]){
                    deptindex = i;
                    break;
                }
            }
            if (deptindex != -1){
                if(curr->data.getGender() == "M"){
                    deptstudent[deptindex][1]++;
                    if (minDepGender[deptindex][1] > curr->data.getAge()){
                        minDepGender[deptindex][1] = curr->data.getAge();}
                }
                else if(curr->data.getGender() == "F"){
                    deptstudent[deptindex][0]++;
                    if (minDepGender[deptindex][0] > curr->data.getAge()){
                        minDepGender[deptindex][0] = curr->data.getAge();}
                }
            }
            curr = curr->next;
        }

        std::cout << "Dept" << "\t" << "Gender" << "\t" << "Min" << std::endl;

        for (int i = 0; i < 9 ; i++){
            if (deptstudent[i][0] > 0){
            std::cout << dept[i] << "\t" << "F" << "\t" << minDepGender[i][0]<< std::endl;
            }
            if (deptstudent[i][1] > 0){
                std::cout << dept[i] << "\t" << "M" << "\t" << minDepGender[i][1] << std::endl;
            }
        }
    }
    else {
        std::cout << "Invalid input. Please enter a valid selection." << std::endl;
    }
}

void list::sort(std::string metric){
    if (head == nullptr || head->next == nullptr){
        return;
    }

    for (node* i = head; i->next != nullptr; i = i->next){
        for (node* j = i->next; j != nullptr; j = j->next){
            bool swap = false;

            if (metric == "Dept"){
                swap = i->data.getDept().compare(j->data.getDept()) > 0;
            }
            else if (metric == "Gender"){
                swap = i->data.getDept().compare(j->data.getDept()) > 0;
            }
            else if (metric == "Name"){
                swap = i->data.getName().compare(j->data.getName()) > 0;
            }
            else if (metric == "Age"){
                swap = i->data.getAge() > j->data.getAge();
            }

            if (swap){
                student temp = i->data;
                i->data = j->data;
                j->data = temp; // swap function implemented
            }
        }
    }
}




int main(){
    int Selection_number = 0 ;
    list studentlist;
    do {
        
        std::cout << "----------MENU----------" << std::endl;
        std::cout << "1. Add a student" << std::endl;
        std::cout << "2. Delete a student" << std::endl;
        std::cout << "3. Print the student's list" << std::endl;
        std::cout << "4. Pivot Table" << std::endl;
        std::cout << "5. Exit" << std::endl;
        std::cout << "------------------------" << std::endl;
        std::cout << "Selection: "; // basic output when it starts
        std::cin >> Selection_number;

        if (!std::cin) { 
            std::cout << "Invalid input. Please enter a valid selection." << std::endl;
            std::cin.clear();
            std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
            continue;
        } // if input is not a integer, error.

        switch(Selection_number){
            case 1: studentlist.addstudent(); break; // function that adding student in list
            case 2: studentlist.deletestudent(); break; // function that deleting student from list
            case 3: studentlist.printstudent(); break; // function that print the list
            case 4: studentlist.table(); break; // function that display new table for calculation
            case 5: std::cout << "Exit!" << std::endl; break;
            default: std::cout << "That's the wrong approach. Try it again." << std::endl; break;
        }
    } while (Selection_number != 5);
    return 0;
}


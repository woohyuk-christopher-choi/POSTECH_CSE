#include <iostream>
#include <cmath>

int main(){
    float x= 0 ,y = 0;
    double result = 0;
    char oper[10];


    std::cin >> oper; 
    if (std::strcmp(oper , "+") == 0 or std::strcmp(oper , "-") == 0 or std::strcmp(oper , "*") == 0 or std::strcmp(oper , "/") == 0){
        std::cin >> x >> y ;

        if (std::strcmp(oper , "+") == 0){
            result = x + y ;
        }
        else if (std::strcmp(oper , "-") == 0){
            result = x - y ;  
        }
        else if (std::strcmp(oper , "*") == 0){
            result = x * y ;
        }
        else if (std::strcmp(oper , "/") == 0){
            result = x / y ;
        }

        std::cout << round(result * 1000) / 1000 ;
    }

    else if (std::strcmp(oper , "sqrt") == 0 or std::strcmp(oper , "square") == 0){
        std::cin >> x;

        if (std::strcmp(oper , "sqrt") == 0){
            result = std::sqrt(x);
        }
        else if (std::strcmp(oper , "square") == 0){
            result = x * x ;
        }

        std::cout << round(result * 1000) / 1000 ;

    }




    return 0;
}
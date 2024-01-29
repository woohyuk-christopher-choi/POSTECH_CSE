#include <iostream>
#include <string>
#include <cmath>

int convert(std::string number){
    std::string neededstr;
    int needednum = 0;
    if(number[0] == '0' and number[1] == 'b'){
        int n = 2;
        neededstr = number.substr(2);
        for(int i = 0 ; i < neededstr.length(); i++){
            int k = pow(n,neededstr.length()-i-1);
            int n = neededstr[i] - 48;

        needednum += n * k;}
    }
    else if(number[0] == '0' and number [1] == 'X'){
        int n = 16;
        neededstr = number.substr(2);
        for(int i = 0 ; i < neededstr.length(); i++){
            int k = pow(n,neededstr.length()-i-1);
            int n = neededstr[i] - 48;
            if (n > 15){
                n-= 7;
            }
            
        needednum += n * k;
            
        }
        
    }
    else if(number[0] == '0' and number[1] != 'b' and number[1] != 'X'){
        int n = 8;
        neededstr = number.substr(1);
        for(int i = 0 ; i < neededstr.length(); i++){
            int k = pow(n,neededstr.length()-i-1);
            int n = neededstr[i] - 48;

        needednum += n * k;
        }
    }
    return needednum;
}
int main(){
    char oper;
    std::string num1, num2;
    double result;

    std::cin >> oper >> num1 >> num2;

    float convertednum1 = convert(num1);
    float convertednum2 = convert(num2);

    if (oper == '+'){
        result = convertednum1 + convertednum2 ;
    }
    else if (oper == '-'){
        result = convertednum1 - convertednum2 ;
    }
    else if (oper == '*'){
        result = convertednum1 * convertednum2 ;
    }
    else if (oper == '/'){
        result = convertednum1 / convertednum2 ;
    }

    std::cout << round(result * 1000) / 1000 ;
    
return 0;
}

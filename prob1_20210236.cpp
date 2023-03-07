#include <iostream>
int main(){
    int a = 0 ; // a is decimal number
    int b = 0 ; // b determines the converted number to be binary, octal, hexadecimal ...
    char convert[16] = {'0','1','2','3','4' ,'5','6','7','8',
    '9','A','B','C','D','E','F'}; // this character array is used to determine each digits.
    
    std::string convertednumber; // we treat this number as a string.
    
    std::cin >> a >> b; 
    
    while(a / b != 0){
        convertednumber = convert[a % b] + convertednumber;
        a = a/b;
    }
    
    convertednumber = convert[a % b] + convertednumber; // if a / b = 0 , do the same way with the loop except dividing with b.
    
    std::cout << convertednumber;
    
    return 0;
}
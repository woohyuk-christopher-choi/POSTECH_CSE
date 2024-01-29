#include "hash_function.h"
#include <iostream>
#include <fstream>
#include <string>
#include <cmath>

using namespace std;

int BinaryMidSquareHash::hashing(int key) {
    /////////////////////////////////////////////////////////
    //////////  TODO: Implement From Here      //////////////
    long long square = (long long) key * (long long) key;
    int shift_bits = key_size - index_size / 2;
    return (square >> shift_bits) & ((1 << index_size) - 1);

    ///////////      End of Implementation      /////////////
    /////////////////////////////////////////////////////////
}

int DigitFoldingHash::hashing(int key) {
    /////////////////////////////////////////////////////////
    //////////  TODO: Implement From Here      //////////////
    int sum = 0; 
    for (int i = 0; i < key_size; i++){
        sum += (key >> i) & 1;
    }
    return sum & ((1 << index_size) - 1);
    ///////////      End of Implementation      /////////////
    /////////////////////////////////////////////////////////
}

int MultiplicationHash::hashing(int key) {
    /////////////////////////////////////////////////////////
    //////////  TODO: Implement From Here      //////////////
    double fractional_part = key * A - int(key * A);
    return int(fractional_part * (1 << index_size));
    /*
    double fractional_part = key * A - (int)(key * A);
    return (int) (fractional_part * (1 << index_size));
    */
    ///////////      End of Implementation      /////////////
    /////////////////////////////////////////////////////////
}

/////////////////////////////////////////////////////////
//////////  TODO: Implement From Here      //////////////

/*  Write your codes if you have additional functions  */


///////////      End of Implementation      /////////////
/////////////////////////////////////////////////////////

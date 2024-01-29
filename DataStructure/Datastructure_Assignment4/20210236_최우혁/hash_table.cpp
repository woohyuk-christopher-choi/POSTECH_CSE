#include <iostream>
#include <fstream>
#include <string>
#include "hash_function.h"
#include "hash_table.h"

using namespace std;


BucketHashTable::BucketHashTable(int table_size, int bucket_size, BinaryMidSquareHash *hf) : table_size(table_size), bucket_size(bucket_size) {
    this->hf = hf;
    this->table = new int[this->table_size * this->bucket_size];
    this->overflow = new int[this->table_size];
    this->table_states = new TableState[this->table_size * this->bucket_size]{EMPTY};
    this->overflow_states = new TableState[this->table_size]{EMPTY};

    /////////////////////////////////////////////////////////
    //////////  TODO: Implement From Here      //////////////
    
    /*  Write your codes if you need  */
    for (int i = 0; i < this->table_size * this->bucket_size; i++) {
        this->table[i] = 0;
    }
    for (int i = 0; i < this->table_size; i++) {
        this->overflow[i] = 0;
    }
    ///////////      End of Implementation      /////////////
    /////////////////////////////////////////////////////////
}

BucketHashTable::~BucketHashTable() {
    /////////////////////////////////////////////////////////
    //////////  TODO: Implement From Here      //////////////
    
    /*  Write your codes if you need  */
    
    ///////////      End of Implementation      /////////////
    /////////////////////////////////////////////////////////

    delete[] this->table;
    delete[] this->overflow;
    delete[] this->table_states;
    delete[] this->overflow_states;
}

/* This is given function. DO NOT MODIFY THIS FUNCTION */
void BucketHashTable::print_table(ostream &out) {
    
    out << "Hash table" << endl;
    int state;
    for (int i=0; i < table_size; i++) {
        out << i << ": ";
        for (int j = 0; j < bucket_size; j++) {
            state = table_states[i * bucket_size + j];
            if (state == EMPTY)
                out << "empty";
            else if (state == DELETED)
                out << "deleted";
            else if (state == OCCUPIED)
                out << table[i * bucket_size + j];
            else
                out << "unknown state";
            if (j < bucket_size - 1)
                out << ",";
        }
        out << endl;
    }
    out << "----------" << endl << "Overflow" << endl;
    for (int i=0; i < table_size; i++) {
        out << i << ": ";
        state = overflow_states[i];
        if (state == EMPTY)
            out << "empty" << endl;
        else if (state == DELETED)
            out << "deleted" << endl;
        else if (state == OCCUPIED)
            out << overflow[i] << endl;
        else
            out << "unknown state" << endl;
    }
}

void BucketHashTable::insert(int key) {
    int index = hf->hashing(key);

    // Try to insert into the main table
    for (int i = 0; i < bucket_size; i++){
        int slot = index * bucket_size + i;
        if (table_states[slot] == TableState::EMPTY || table_states[slot] == TableState::DELETED) {
            table[slot] = key;
            table_states[slot] = TableState::OCCUPIED;
            return;
        }
    }

    int deletedSlot = -1;

    for (int i = 0; i < table_size; i++) {
        if (overflow_states[i] == TableState::EMPTY) {
            overflow[i] = key;
            overflow_states[i] = TableState::OCCUPIED;
            return;
        } 
        else if (overflow_states[i] == TableState::DELETED) {
            deletedSlot = i;
        }
    }
    
    if (deletedSlot != -1) {
        overflow[deletedSlot] = key;
        overflow_states[deletedSlot] = TableState::OCCUPIED;
    }
}


void BucketHashTable::erase(int key) {
    int index = hf->hashing(key);
    
    // Check the main hash table
    for (int i = 0; i < bucket_size; i++) {
        int slot = index * bucket_size + i;
        if (table_states[slot] == TableState::OCCUPIED && table[slot] == key) {
            table[slot] = 0;
            table_states[slot] = TableState::DELETED;
            return;
        }
    }
    
    // Check the overflow bucket
    for (int i = 0; i < table_size; i++) {
        if (overflow_states[i] == TableState::OCCUPIED && overflow[i] == key) {
            //overflow[i] = 0;
            overflow_states[i] = TableState::DELETED;
            return;
        }
    }
}


/////////////////////////////////////////////////////////
//////////  TODO: Implement From Here      //////////////

/*  Write your codes if you have additional functions  */

///////////      End of Implementation      /////////////
/////////////////////////////////////////////////////////

DoubleHashTable::DoubleHashTable(int table_size, MultiplicationHash *hf_1, DigitFoldingHash *hf_2) : table_size(table_size) {
    this->hf_1 = hf_1;
    this->hf_2 = hf_2;
    this->table = new int[this->table_size];
    this->states = new TableState[this->table_size]{EMPTY};

    /////////////////////////////////////////////////////////
    //////////  TODO: Implement From Here      //////////////
    
    /*  Write your codes if you need  */
    
    ///////////      End of Implementation      /////////////
    /////////////////////////////////////////////////////////
}

DoubleHashTable::~DoubleHashTable() {
    /////////////////////////////////////////////////////////
    //////////  TODO: Implement From Here      //////////////
    
    /*  Write your codes if you need  */
    
    ///////////      End of Implementation      /////////////
    /////////////////////////////////////////////////////////

    delete[] this->table;
    delete[] this->states;
}

/* This is given function. DO NOT MODIFY THIS FUNCTION */
void DoubleHashTable::print_table(ostream &out) {
    for (int i=0; i < this->table_size; i++) {
        out << i << ": ";
        int state = this->states[i];
        if (state == EMPTY)
            out << "empty" << endl;
        else if (state == DELETED)
            out << "deleted" << endl;
        else if (state == OCCUPIED)
            out << this->table[i] << endl;
        else
            out << "unknown state" << endl;
    }
}

void DoubleHashTable::insert(int key) {
    /////////////////////////////////////////////////////////
    //////////  TODO: Implement From Here      //////////////
    int hash1 = hf_1 -> hashing(key);
    int hash2 = hf_2-> hashing(key);

    for (int i = 0; i < table_size; i++){
        int idx = (hash1 + i * hash2) % table_size;
        if (states[idx] == TableState::EMPTY){
            table[idx] = key;
            states[idx] = TableState:: OCCUPIED;
            break;
        }
    }
    ///////////      End of Implementation      /////////////
    /////////////////////////////////////////////////////////
}

void DoubleHashTable::erase(int key) {
    /////////////////////////////////////////////////////////
    //////////  TODO: Implement From Here      //////////////
    int hash1 = hf_1->hashing(key);
    int hash2 = hf_2->hashing(key);

    for(int i = 0; i < table_size; i++){
        int idx = (hash1 + i * hash2) % table_size;
        if (states[idx] == TableState::OCCUPIED && table[idx] ==key){
            states[idx] = TableState::DELETED;
            break;
        }
    }

    ///////////      End of Implementation      /////////////
    /////////////////////////////////////////////////////////
}

/////////////////////////////////////////////////////////
//////////  TODO: Implement From Here      //////////////

/*  Write your codes if you have additional functions  */

///////////      End of Implementation      /////////////
/////////////////////////////////////////////////////////

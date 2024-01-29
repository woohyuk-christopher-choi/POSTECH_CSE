#ifndef PARSER_HPP_
#define PARSER_HPP_

#include <iostream>
#include <string>
#include <vector>

using namespace std;

class parser
{
    public:
        vector<int> load_image(const char*);
        vector<string> load_config(const char*);
        void write_result(const char* , const string&);

};


#endif





#ifndef DRAWER_HPP_
#define DRAWER_HPP_

#include <iostream>
#include <string>
#include <vector>
#include "artist.hpp"
#include "parser.hpp"

using namespace std;

class drawer
{
    protected:
    artist* ar;

    public:
        drawer(){}
        drawer(artist*);
        virtual ~drawer() {delete ar;};
        virtual string draw();
        

};

class downsample  : public drawer
{
    public:
        string draw();
        downsample(artist* ar) : drawer(ar){}

        

};

class upsample : public drawer
{
    public:
        string draw();
        upsample(artist* ar) : drawer(ar){}
        

};

class scale : public drawer
{
    private:
        int scale_x ;
        int scale_y ;
    public:
        scale(artist* ar, int scale_x, int scale_y) : drawer(ar), scale_x(scale_x) , scale_y(scale_y) {} // CONSTRUCTOR
        string draw();

};




#endif





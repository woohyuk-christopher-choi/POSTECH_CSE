#ifndef ARTIST_HPP_
#define ARTIST_HPP_

#include <iostream>
#include <string>
#include <vector>
#include "parser.hpp"

class artist
{
    protected:
        int width;
        int height;
        std::vector<int> pixel;

    public:
        artist(){}
        artist(int, int, const std::vector<int>&); // CONSTRUCTOR
        virtual char mapper(int,int) = 0; // NOT IMPLEMENTED IN ARTIST.CPP
        virtual ~artist() {};
        int get_width() const;
        int get_height() const;
        const vector<int>& get_pixel() const;

};//CLASS ARTIST

class classic : public artist
{
    public:
        char mapper(int,int);
        classic (int w, int h, const std::vector<int>& values) : artist(w,h,values){}
        ~classic(){}
};//CLASS CLASSIC

class iclassic : public artist
{
    public:
        char mapper(int,int);
        iclassic (int w, int h, const std::vector<int>& values) : artist(w,h,values){}
        ~iclassic(){}

};//CLASS ICLASSIC

class sobelx : public artist
{
    public:
        char mapper(int,int);
        sobelx (int w, int h, const std::vector<int>& values) : artist(w,h,values){}
        ~sobelx(){}

};//CLASS SOBELX

class sobely : public artist
{
    public:
        char mapper(int,int);
        sobely (int w, int h, const std::vector<int>& values) : artist(w,h,values){}
        ~sobely(){}

}; //CLASS SOBELY

class gradient : public artist
{
    public:
        char mapper(int,int);
        gradient (int w, int h, const std::vector<int>& values) : artist(w,h,values){}
        ~gradient(){}

};//CLASS GRADIENT

class my_style : public artist
{
    public:
        char mapper(int,int);
        my_style(int w, int h, const std::vector<int>& values) : artist(w,h,values) {}
        ~my_style(){}

};//CLASS

#endif





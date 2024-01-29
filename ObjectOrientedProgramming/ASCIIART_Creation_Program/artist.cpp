#include <iostream>
#include <string>
#include <cmath>
#include "artist.hpp"

artist::artist(int width, int height, const std::vector<int>& pixel){
    this->width = width;
    this->height = height;
    this->pixel = pixel;
}//CONSTRUCTOR


int artist::get_width() const{
    return width;
}//GETTER

int artist::get_height() const{
    return height;
}//GETTER

const vector<int>& artist::get_pixel() const{
    return pixel;
}//GETTER

char classic::mapper(int a , int b){
    int p = pixel[b * width + a]; // CHECK
    int i = p/17;
    if(i == 15){
        i = 14;
    }
    static const char ASCII[] = "@&%WXAHOT*^+-. ";
    return ASCII[i];
}// MAPPER FUNCTION OF CLASSIC

char iclassic::mapper(int a , int b){
    int p = pixel[b * width + a]; // CHECK
    int i = p/17;
    if(i == 15){
        i = 14;
    }
    static const char ASCII[] = " .-+^*TOHAXW%&@";
    return ASCII[i];
}// MAPPER FUNCTION OF ICLASSIC

char sobelx::mapper(int a , int b){
    int p = pixel[b * width + a]; // CHECK
    int rp = a + 1 < width ? pixel[a * width + b + 1] : pixel[a * width + b];
    if(abs(p-rp) >= 50){
        return '|';
    }
    else{
        return ' ';
    }
}// MAPPER FUNCTION OF SOBELX

char sobely::mapper(int a , int b){
    int p = pixel[b * width + a]; // CHECK
    int bp = b + 1 < height ? pixel[a * width + b + width] : pixel [a * width + b];
    if(abs(p-bp) >= 50){
        return '-';
    }
    else{
        return ' ';
    }
}// MAPPER FUNCTION OF SOBELY

char gradient::mapper(int a , int b){
    int p = pixel[a * width + b];
    int rp = a + 1 < width ? pixel[a * width + b + 1] : pixel[a * width + b];
    int bp = b + 1 < height ? pixel[a * width + b + width] : pixel [a * width + b];
    if(abs(p-rp) >= 50 && abs(p-bp) >= 50){
        return '+';
    }
    else if(abs(p-bp) >=  50 && abs(p-rp) < 50){
        return '-';
    }
    else if(abs(p-rp) >=  50 && abs(p-bp) < 50){
        return '|';
    }
    else{
        return ' ';
    }
}// MAPPER FUNCTION OF GRADIENT

char my_style::mapper(int a , int b){
        int p = pixel[b * width + a]; // CHECK
    int i = p/17;
    if(i == 15){
        i = 14;
    }
    static const char ASCII[] = ".......*@@@@@@@";
    return ASCII[i];
}// MAPPER FUNCTION OF MY_STYLE





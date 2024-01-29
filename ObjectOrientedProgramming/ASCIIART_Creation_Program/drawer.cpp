#include <iostream>
#include <string>
#include "drawer.hpp"

using namespace std;

drawer::drawer(artist* ar){
    this->ar = ar;
}


string drawer::draw(){
    if (ar == nullptr){
        return "";
    }

    string ASCII;
    int width = ar->get_width();
    int height = ar->get_height();

    for (int b = 0; b < height; b++){
        for (int a = 0; a < width; a++){
            ASCII += ar->mapper(a, b);
        }
        ASCII += '\n';
    }

    return ASCII; //RETURN WITH ONE STRING, ASCII.
}

string downsample::draw(){
    int width = ar->get_width();
    int height = ar->get_height();
    string downASCII;

    int width2 = (width + 1) / 2;
    int height2 = (height + 1) / 2;

    for (int b = 0; b < height2; b++){
        for (int a = 0; a < width2; a++){
            downASCII += ar->mapper(2*a , 2*b); // 넘어가면 오류?
        }
        downASCII += '\n';
    }

    return downASCII; // RETURN WITH ONE STRING, downASCII.
}

string upsample::draw(){
    int width = ar->get_width();
    int height = ar->get_height();
    string upASCII;


    for (int b = 0; b < height; b++){
        for (int a = 0; a < width; a++){
            upASCII += ar->mapper(a, b);
            upASCII += ar->mapper(a, b); 
        }
        upASCII += '\n';
        for (int a = 0; a < width; a++){
            upASCII += ar->mapper(a, b);
            upASCII += ar->mapper(a, b); 
        }
        upASCII += '\n';
    }

    return upASCII; // RETURN WITH ONE STRING, upASCII.
}


string scale::draw(){
    int width = ar->get_width();
    int height = ar->get_height();
    string scaledASCII;

    if (scale_x == 0 || scale_y == 0){
        return "ERROR, scale value 0";
    }

    float scale_x_new = scale_x > 0 ? scale_x : -1.0f / scale_x;
    float scale_y_new = scale_y > 0 ? scale_y : -1.0f / scale_y;

    int width2 = (int)(width * scale_x_new + 0.5f);
    int height2 = (int)(height * scale_y_new + 0.5f);

    for(int y = 0 ; y < height2 ; y++){
        for (int x = 0 ; x < width2 ; x++){
            int new_x = (int)(x / scale_x_new + 0.5f);
            int new_y = (int)(y / scale_y_new + 0.5f);
            scaledASCII += ar->mapper(new_x, new_y); 
        }
        scaledASCII += '\n';
    }

    return scaledASCII;  // RETURN WITH ONE STRING, scaledASCII.
}




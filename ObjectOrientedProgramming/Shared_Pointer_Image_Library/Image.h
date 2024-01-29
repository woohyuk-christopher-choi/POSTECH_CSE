#ifndef IMAGE_H
#define IMAGE_H

#include <iostream>
#include <cstdint>
#include <cassert>
#include "SharedPtr.h"

///////////////////////////////////////////////////////////////////////////
// RGB pixel type
//    Usage:
//      - RGB<float> rgb(0.5f, 0.1f, 0.3f);
//        rgb[0] = 0.2f; // or equivalently, rgb.r = 0.2f;
template<typename ValType>
struct RGB
{
    union {
        ValType data[3];
        struct {
            ValType r, g, b;
        };
    };

    RGB() {}
    RGB(ValType r_, ValType g_, ValType b_) : r(r_), g(g_), b(b_) {}

    ValType operator[](int idx) const { return data[idx]; }
    ValType& operator[](int idx) { return data[idx]; }
};

typedef RGB<uint8_t>   RGB8b;
typedef RGB<float>      RGBf;


///////////////////////////////////////////////////////////////////////////
// Image class template
//
template<typename PixelType>
class Image
{
private:
    // ======= ADD CODE HERE IF NEEDED =========
    int m_width;
    int m_height;
    SharedArray<PixelType> m_buff;

public:
    ////////////////////////////////////////////
    // constructors & destructor
    ////////////////////////////////////////////

    // ======= ADD CODE HERE IF NEEDED =========
    Image() : m_width(0), m_height(0){}
    Image(size_t width, size_t height) : m_width(width), m_height(height), m_buff(new PixelType[width * height]) {}
    Image(size_t width, size_t height, const PixelType& val) : m_width(width), m_height(height), m_buff(new PixelType[width * height]) {
        for (size_t i = 0; i < width * height; ++i) {
            m_buff[i] = val;
        }
    }
    Image(const Image<PixelType>& img) : m_width(img.m_width), m_height(img.m_height), m_buff(new PixelType[img.m_width * img.m_height]) {
        for (size_t i = 0; i < m_width * m_height; ++i) {
            m_buff[i] = img.m_buff[i];
        }
    }
    ~Image(){};
    ////////////////////////////////////////////
    // assignment operator
    ////////////////////////////////////////////

    // ======= ADD CODE HERE IF NEEDED =========
    Image<PixelType>& operator=(const Image<PixelType>& img)
    {
        if (this != &img){ 

        m_width = img.m_width;
        m_height = img.m_height;
        m_buff = SharedArray<PixelType>(new PixelType[img.m_width * img.m_height]);
        std::copy(img.m_buff.get(), img.m_buff.get() + img.m_width * img.m_height, m_buff.get());
        }
        
        return *this;
    }
    ////////////////////////////////////////////
    // element access operators
    ////////////////////////////////////////////
    PixelType* operator[](int y) { return &m_buff[y * m_width]; }
    const PixelType* operator[](int y) const { return &m_buff[y * m_width]; }

    ////////////////////////////////////////////
    // other methods
    ////////////////////////////////////////////
    //   - width(), height()
    size_t width() const { return m_width; }
    size_t height() const { return m_height; }
    // ======= ADD CODE HERE IF NEEDED =========
};

// ======= ADD CODE HERE IF NEEDED =========

// Miscellaneous functions
void convert_pixel_type(const Image<RGB8b>&, Image<RGBf>&);
void convert_pixel_type(const Image<RGBf>&, Image<RGB8b>&);
bool load_bmp(const char*, Image<RGB8b>&);
bool save_bmp(const char*, const Image<RGB8b>&);

#endif





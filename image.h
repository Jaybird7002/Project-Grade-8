//
// Created by Matthew Beers on 8/7/21.
//

#ifndef IMAGE_H
#define IMAGE_H

#include "color.h"

class Image {
private:
    int width;
    int height;
    Color *pixels;

public:
    Image(int w, int h);
    ~Image();

    void set_pixel(int x, int y, Color pixel);

    void save(const std::string& filename);
    void save_ppm(const std::string& filename);
};

#endif //IMAGE_H

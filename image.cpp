//
// Created by Matthew Beers on 8/7/21.
//

#include <string>
#include "image.h"
#include <FreeImagePlus.h>
#include <iostream>
#include <fstream>
#include <cmath>

const int DEFAULT_BPP = 8;
const double BPP_MAX = (double) (1 << DEFAULT_BPP) - 0.0001;

Image::Image(int w, int h) : width(w), height(h) {
    pixels = new Color[width * height];
    std::cout << "bits per pixel: " << DEFAULT_BPP << ", offset: " << BPP_MAX << "\n";
}

Image::~Image() {
    delete[] pixels;
}

/**
 * Set the color of a specific pixel in the output image
 *
 * @param x The column, where 0 is the left column
 * @param y The row, where 0 is the bottom row
 * @param pixel the Color for the pixel
 */
void Image::set_pixel(const int x, const int y, const Color pixel) {
    if (x >= 0 && x < width && y >= 0 && y < height) {
        pixels[y * width + x] = pixel;
    }
}

/**
 * Output the current pixels into a file with the given name
 *
 * @param filename The filename to save the image into
 */
void Image::save(const std::string &filename) {
    auto output = fipImage(FIT_BITMAP, width, height, DEFAULT_BPP * 3);

    RGBQUAD savePixel;

    for (int i = 0; i < width; i++) {
        for (int j = 0; j < height; j++) {
            Color pixel = pixels[j * width + i];

            savePixel.rgbRed = static_cast<BYTE>(sqrt(pixel.red) * BPP_MAX);
            savePixel.rgbGreen = static_cast<BYTE>(sqrt(pixel.green) * BPP_MAX);
            savePixel.rgbBlue = static_cast<BYTE>(sqrt(pixel.blue) * BPP_MAX);
//            savePixel.rgbRed = static_cast<BYTE>(pixel.red * BPP_MAX);
//            savePixel.rgbGreen = static_cast<BYTE>(pixel.green * BPP_MAX);
//            savePixel.rgbBlue = static_cast<BYTE>(pixel.blue * BPP_MAX);

            output.setPixelColor(i, j, &savePixel);
        }
    }

    output.save(filename.c_str());
}

/**
 * Output the current pixels into a file with the given name. Regardless of
 * file extension, this will write out a P3 type PPM file
 *
 * @param filename The filename to save the image into
 */
void Image::save_ppm(const std::string &filename) {
    using namespace std;

    ofstream output = ofstream(filename);
    output << "P3 " << width << " " << height << " " << (1 << DEFAULT_BPP) << endl;

    for (int j = height - 1; j >= 0; j--) {
        for (int i = 0; i < width; i++) {
            Color pixel = pixels[j * width + i];

            output << static_cast<int>(pixel.red * BPP_MAX) << " "
                   << static_cast<int>(pixel.green * BPP_MAX) << " "
                   << static_cast<int>(pixel.blue * BPP_MAX) << " " << endl;
        }
    }

    output.close();
}

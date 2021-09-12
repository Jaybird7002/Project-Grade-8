#include <iostream>
#include "shapes.h"
#include "color.h"
#include "image.h"
#include "scene.h"

Color gradiant(int x_, int y_, int width, int height) {
    return Color{ (double)y_ / height, (double)y_ / height, .75};
};

std::ostream & operator<<(std::ostream& out, point3d point)
{
    out << "(" << point.x_ << ", " << point.y_ << ", " << point.z_ << ")";
    return out;
}

int main()
{
    point3d pointA = {1, 1, 0};

    //test point b for line
    point3d pointB = {5, 1, 0};

    //test point c for triangle
    point3d pointC = {1, 4, 0};

    //test line
    line3d lineA = { pointA, pointB };
    lineA.length();

    //test triangle
    triangle3d triangleA = triangle3d { pointA, pointB, pointC };

    //output
    std::cout << "point A: " << pointA << std::endl;
    std::cout << "point B: " << pointB << std::endl;

    std::cout << "line A length: " << lineA.length() << std::endl;

    std::cout << "triangle info: A: " << triangleA.va_ << ", B: " << triangleA.vb_ << ", C: " << triangleA.vc_ << std::endl;
    std::cout << triangleA.normal().b_ << std::endl;

    int width = 1280;
    int height = 960;
    Image image = Image(width, height);

    for (int i = 0.0; i < width; i++) {
        for (int j = 0.0; j < height; j++) {
            image.set_pixel(i,j, gradiant(i, j, width, height));
        }
    }

    image.save("raytrace.png");
}

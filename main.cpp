#include <iostream>
#include "shapes.h"
#include "color.h"
#include "image.h"
#include "scene.h"
#include "ray.h"

Color gradiant(int x_, int y_, int width, int height) {
    return Color{ (double)y_ / height, (double)x_ / width, (double)y_ / -height};
};

Color ray_color(const ray& r) {
    vec3 unit_direction = r.direction().unit_vector();
    auto t = 0.5*(unit_direction.y + 1.0);
    return (1.0-t) * Color{1.0, 1.0, 1.0} + t*Color{0, 0.7, 0.1};
}

std::ostream & operator<<(std::ostream& out, point3d point)
{
    out << "(" << point.x_ << ", " << point.y_ << ", " << point.z_ << ")";
    return out;
}

const auto aspect_ratio = 16.0 / 9.0;
const int image_width = 400;
const int image_height = static_cast<int>(image_width / aspect_ratio);

// Camera

auto viewport_height = 2.0;
auto viewport_width = aspect_ratio * viewport_height;
auto focal_length = 1.0;

auto origin = point3d{0, 0, 0};
auto horizontal = vec3(viewport_width, 0, 0);
auto vertical = vec3(0, viewport_height, 0);
auto lower_left_corner = origin - horizontal/2 - vertical/2 - vec3(0, 0, focal_length);

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
            auto u = double(i) / (image_width-1);
            auto v = double(j) / (image_height-1);
            ray r(origin, lower_left_corner + u*horizontal + v*vertical - origin);
            Color pixel_color = ray_color(r);
        }
    }

    image.save("raytrace1.png");
}

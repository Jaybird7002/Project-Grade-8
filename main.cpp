#include <iostream>
#include <random>
#include "vector_point.h"
#include "color.h"
#include "image.h"
#include "scene.h"
#include "ray.h"
#include "shapes.h"

Color gradiant(int x_, int y_, int width, int height) {
    return Color{ (double)y_ / -height, (double)y_ / -height, (double)y_ / height};
}

const auto aspect_ratio = 4.0 / 3.0 ;//16.0 / 9.0;
const int image_width = 300;
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

    std::cout << "triangle info: A: " << triangleA.va_ << ", B: " << triangleA.vb_ << ", C: "
        << triangleA.vc_<< std::endl;
    std::cout << triangleA.normal().b_ << std::endl;


    Scene the_scene = Scene{};
    the_scene.add_thing(Sphere { point3d{0.0, 0.0, -1.0}, 0.5});
    the_scene.add_thing(Sphere { point3d{0.7, 0.5, -1.5}, 0.5});
    the_scene.add_thing(Sphere { point3d{-0.7, 0.5, -1.5}, 0.5});
    the_scene.add_thing(Sphere { point3d{0,-100.5,-1}, 100});

    std::cout << "Camera: " << the_scene.viewPoint;
    std::cout << "image: " << image_width << "x" << image_height << "\n";

//    int image_width = 300;
//    int image_height = 200;
    Image image = Image(image_width, image_height);

    for (int i = 0.0; i < image_width; i++) {
        for (int j = 0.0; j < image_height; j++) {
            auto u = double(i) / (image_width-1);
            auto v = double(j) / (image_height-1);
            const vec3 &dp_horiz = u * horizontal;
            const vec3 &dp_vert = v * vertical;
            const point3d &d = lower_left_corner + dp_horiz;
            const point3d &e = d + dp_vert;
            point3d dest_point = e - origin;
            //std::cout << "dest (" << u << ", " << v << "): " << dest_point << "\n";
            ray r(origin, dest_point.to_vec3());
            //std::cout << "ray (" << i << ", " << j << "): " << r << "\n";
            Color pixel_color = the_scene.ray_color(r, gradiant(i, j, image_width, image_height));
            image.set_pixel(i,j, pixel_color);
        }
    }

    image.save("raytrace.png");
}
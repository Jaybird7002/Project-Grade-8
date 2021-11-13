#include <iostream>
#include <random>
#include "vector_point.h"
#include "color.h"
#include "image.h"
#include "scene.h"
#include "ray.h"
#include "shapes.h"
#include "Camera.h"


Color gradiant(int x_, int y_, int width, int height) {
    //return Color{ 0 , 0 , 1};
    return Color{ 0.25, 0, (double)(height - y_) / height};
}

inline double random_double() {
    static std::uniform_real_distribution<double> distribution(0.0, 1.0);
    static std::mt19937 generator;
    return distribution(generator);
}

#define HQ 1

//const auto aspect_ratio = 4.0 / 3.0 ;
const auto aspect_ratio = 16.0 / 9.0;

#ifdef HQ
const int image_width = 960;
const int samples_per_pixel = 100;
const int default_depth = 10;
#else
const int image_width = 300;
const int samples_per_pixel = 10;
const int default_depth = 10;
#endif

const int image_height = static_cast<int>(image_width / aspect_ratio);
auto focal_length = 1.0;
auto viewport_height = 2.0;

int main()
{
    Camera cam = Camera(aspect_ratio, focal_length, viewport_height);

    Scene the_scene = Scene{};
    the_scene.add_thing(Sphere { point3d{0.0, 0.0, -1.0}, 0.5});
    the_scene.add_thing(Sphere { point3d{0,-100.5,-1}, 100});

    std::cout << "Camera: " << the_scene.viewPoint;
    std::cout << "image: " << image_width << "x" << image_height << "\n";

    Image image = Image(image_width, image_height);

    for (int i = 0.0; i < image_width; i++) {
        for (int j = 0.0; j < image_height; j++) {
            Color pixel_color;
            const Color &default_bg = gradiant(i, j, image_width, image_height);
            for (int s = 0; s < samples_per_pixel; ++s) {
                auto u = (double(i) + random_double()) / (image_width - 1);
                auto v = (double(j) + random_double()) / (image_height - 1);
                ray r = cam.get_ray(u, v);
                pixel_color = pixel_color + the_scene.ray_color(r, default_bg, default_depth);
            }
            pixel_color = pixel_color / samples_per_pixel;
            image.set_pixel(i,j, pixel_color);
        }
        if (i > 0 && i % 80 == 0) std::cout << " " << i << "\n";
        std::cout << ".";
        std::cout.flush();
    }
    std::cout << " " << image_width << "\n";
    image.save("raytrace.png");
}
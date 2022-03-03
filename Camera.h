//
// Created by James Beers on 10/31/21.
//

#ifndef PROJECT_GRADE_8_CAMERA_H
#define PROJECT_GRADE_8_CAMERA_H

#include "ray.h"
#include "vector_point.h"

class Camera {
private:
    double aspect_ratio;
    double focal_length ;
    double viewport_height;
    double viewport_width;

    point3d origin = point3d{0, 0, 0};
    vec3 horizontal;
    vec3 vertical;
    point3d lower_left_corner = point3d{0, 0, 0};

public:
    Camera(double ar, double fl, double vh) {
        this->aspect_ratio = ar;
        this->focal_length = fl;
        this->viewport_height = vh;
        viewport_width = aspect_ratio * viewport_height;
        horizontal = vec3(viewport_width, 0, 0);
        vertical = vec3(0, viewport_height, 0);
        lower_left_corner = origin - horizontal/2 - vertical/2 - vec3(0, 0, focal_length);
    }

    ray get_ray(double u, double v)
    {
        const vec3 &dp_horiz = u * horizontal;
        const vec3 &dp_vert = v * vertical;
        const point3d &d = lower_left_corner + dp_horiz;
        const point3d &e = d + dp_vert;
        point3d dest_point = e - origin;
        return ray (origin, dest_point.to_vec3());
    }
};
#endif //PROJECT_GRADE_8_CAMERA_H

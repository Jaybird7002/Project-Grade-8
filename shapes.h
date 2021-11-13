//
// Created by James Beers on 10/23/21.
//

#ifndef PROJECT_GRADE_8_SHAPES_H
#define PROJECT_GRADE_8_SHAPES_H

#import "vector_point.h"
#include "ray.h"
#include <random>

class Sphere {
public:
    point3d center;
    double radius;

    double hit(const ray &r, double t_min, double t_max) {
        point3d oc = r.origin() - center;
        auto a = r.direction().dot(r.direction());
        auto b = 2.0 * oc.dot(r.direction());
        auto c = oc.dot(oc) - radius*radius;
        auto discriminant = b*b - 4*a*c;
        if (discriminant < 0) {
            return -1.0;
        } else {
            return (-b - sqrt(discriminant) ) / (2.0*a);
        }
    }

    const Color color_at(const point3d p) {
        vec3 N = (p - center).to_vec3().unit_vector();
        return 0.5*Color{N.x+1, N.y+1, N.z+1};
    }
};

#endif //PROJECT_GRADE_8_SHAPES_H

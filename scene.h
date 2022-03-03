//
// Created by James Beers on 8/20/21.
//

#ifndef PROJECT_GRADE_8_SCENE_H
#define PROJECT_GRADE_8_SCENE_H

#include "shapes.h"
#include "ray.h"
#include "vector_point.h"
#include "Materials.h"

#include <vector>

class Scene
{
    materials material;
    std::vector<Sphere> things;

public:
    Color ray_color(const ray &r, const Color &default_color, int depth)
    {
        if (depth <= 0) {
            return Color{0, 0, 0};
        }
        double min_t = -1;
        int in_front = -1;
        for (int i=0; i < things.size(); i++) {
            Sphere s = things[i];
            auto t = s.hit(r, 0.0001, 111110);
            if (t > 0.0 && (min_t < 0.0 || t < min_t)) {
                min_t = t;
                in_front = i;
            }

        }

        if (min_t > 0.0) {
            Sphere &hit = things[in_front];
            auto p = r.at(min_t);
            auto normal = p - hit.center;
//            return 0.5 * ray_color(ray(p, normal.to_vec3()), default_color, depth-1);
            point3d target = p + normal + vec3::random_in_unit_sphere();
            return hit.material.reflectivity * (
                   ray_color(ray(p, (target - p).to_vec3()), hit.material.color, depth-1));
        }

        return default_color;
    }


    point3d lightSource{
            point3d(12, 12, 12)
    };

    point3d viewPoint{
            point3d(0, 0, 0)
    };

public:

    void add_thing(const Sphere &sphere)
    {
        things.push_back(sphere);
    }

};

#endif //PROJECT_GRADE_8_SCENE_H
//
// Created by James Beers on 8/20/21.
//

#ifndef PROJECT_GRADE_8_SCENE_H
#define PROJECT_GRADE_8_SCENE_H

#include "shapes.h"
#include "ray.h"
#include "scene.h"

#include <vector>

class Scene
{

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
//            point3d target = rec.p + rec.normal + random_in_unit_sphere();
//            return 0.5 * ray_color(ray(rec.p, target - rec.p), world);

        }
        if (min_t > 0.0) {
            //1. need the point that intersected the sphere (rec.p)
            //2. need the normal from the point (rec.normal)
            //3. return 0.5 * ray_color(ray(...), default_color, depth-1);
            Sphere &hit = things[in_front];
            auto p = r.at(min_t);
            auto normal = p - hit.center;// + vec3::random_in_unit_sphere();
            return 0.5 * ray_color(ray(p, normal.to_vec3()), default_color, depth-1);
            //return things[in_front].color_at(r.at(min_t));
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

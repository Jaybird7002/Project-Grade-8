//
// Created by James Beers on 8/20/21.
//

#ifndef PROJECT_GRADE_8_SCENE_H
#define PROJECT_GRADE_8_SCENE_H

#include "shapes.h"
#include "ray.h"

#include <vector>

class Scene
{

    std::vector<Sphere> things;

public:
    Color ray_color(const ray &r, const Color &default_color)
    {
        double min_t = -1;
        int in_front = -1;
        for (int i=0; i < things.size(); i++) {
            Sphere s = things[i];
            auto t = s.hit(r);
            if (t > 0.0 && (min_t < 0.0 || t < min_t)) {
                min_t = t;
                in_front = i;
            }
        }
        //do something
        if (min_t > 0.0) {
            return things[in_front].color_at(r.at(min_t));
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

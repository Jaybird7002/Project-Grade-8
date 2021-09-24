//
// Created by James Beers on 9/16/21.
//

#ifndef PROJECT_GRADE_8_RAY_H
#define PROJECT_GRADE_8_RAY_H

class ray {
public:
    ray(point3d orig) : orig(orig)
    {}
    ray(const point3d& origin, const vec3& direction)
    : orig(origin), dir(direction)
    {}

    point3d origin() const  { return orig; }
    vec3 direction() const { return dir; }

    point3d at(double t) const {
        return orig + t*dir;
    }

public:
    point3d orig;
    vec3 dir;
};


#endif //PROJECT_GRADE_8_RAY_H

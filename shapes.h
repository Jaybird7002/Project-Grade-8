//
// Created by James Beers on 8/4/21.
//

#ifndef PROJECT_GRADE_8_SHAPES_H
#define PROJECT_GRADE_8_SHAPES_H

#include <iostream>
#include <cmath>
#include <vector>


struct point3d
{
    point3d(int x, int y, int z)
    {

    }

    int x_ = 0;
    int y_ = 0;
    int z_ = 0;
};

struct line3d
{
    point3d a_;
    point3d b_;

    double length() const noexcept
    {
        int x = b_.x_ - a_.x_;
        int y = b_.y_ - a_.y_;
        int z = b_.z_ - a_.z_;
        return sqrt(x * x + y * y + z * z);
    };
};

struct triangle3d
{
    point3d va_;
    point3d vb_;
    point3d vc_;

    line3d a_to_b() const noexcept
    { return line3d{va_, vb_}; }

    line3d b_to_c() const noexcept
    { return line3d{vb_, vc_}; }

    line3d a_to_c() const noexcept
    { return line3d{va_, vc_}; }

    line3d normal() const noexcept
    {
        //calculate cross product here
        int n_Cross1 = va_.y_ * vb_.z_ - va_.z_ * vb_.y_;
        int n_Cross2 = va_.z_ * vb_.x_ - va_.x_ * vb_.z_;
        int n_Cross3 = va_.x_ * vb_.y_ - va_.y_ * vb_.x_;

        //calculate normal here
        return line3d{va_, point3d{n_Cross1, n_Cross2, n_Cross3}};
    }
};

#endif //PROJECT_GRADE_8_SHAPES_H

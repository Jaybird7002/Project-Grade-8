//
// Created by James Beers on 8/4/21.
//

#ifndef PROJECT_GRADE_8_VECTOR_POINT_H
#define PROJECT_GRADE_8_VECTOR_POINT_H

#include <iostream>
#include <cmath>
#include <vector>

class vec3
{
public:
    double x, y, z;

public:
    vec3() : x(0), y(0), z(0)
    {}

    vec3(double x_, double y_, double z_) : x(x_), y(y_), z(z_)
    {}

    vec3 operator-() const
    { return {-x, -y, -z}; }

    vec3 &operator+=(const vec3 &v)
    {
        x += v.x;
        y += v.y;
        z += v.z;
        return *this;
    }

    vec3 &operator*=(const double t)
    {
        x *= t;
        y *= t;
        z *= t;
        return *this;
    }

    vec3 &operator/=(const double t)
    {
        return *this *= 1 / t;
    }

    double length() const
    {
        return sqrt(length_squared());
    }

    double length_squared() const
    {
        return x * x + y * y + z * z;
    }

    inline double dot(const vec3 &v)
    {
        return this->x * v.x
               + this->y * v.y
               + this->z * v.z;
    }

    inline vec3 cross(const vec3 &v)
    {
        return {this->y * v.z - this->z * v.y,
                this->z * v.x - this->x * v.z,
                this->x * v.y - this->y * v.x};
    }

    inline vec3 unit_vector()
    {
        return scale(1 / this->length());
    }

    inline vec3 scale(const double t) const {
        return vec3(t * this->x, t * this->y, t * this->z);
    }

    inline static double random_double(double d, double d1)
    {
        static std::uniform_real_distribution<double> distribution(0.0, 1.0);
        static std::mt19937 generator;
        return distribution(generator);
    }

    //inline vec3 random() {
    //    return vec3(random_double(), random_double(), random_double());
    //}

    inline static vec3 random(double min, double max) {
        return vec3(random_double(min, max), random_double(min, max), random_double(min, max));
    }

    inline static vec3 random_in_unit_sphere() {
        while (true) {
            auto p = vec3::random(-1,1);
            if (p.length_squared() >= 1) continue;
            return p;
        }
    }

    vec3 random_unit_vector() {
        return (random_in_unit_sphere()).unit_vector();
    }

};
struct point3d
{
    point3d(double x, double y, double z): x_(x), y_(y), z_(z)
    {

    }

    double x_ = 0;
    double y_ = 0;
    double z_ = 0;

    inline double dot(const point3d &v)
    {
        return this->x_ * v.x_
               + this->y_ * v.y_
               + this->z_ * v.z_;
    }

    inline double dot(const vec3 &v)
    {
        return this->x_ * v.x
               + this->y_ * v.y
               + this->z_ * v.z;
    }

    inline vec3 to_vec3(){

        return vec3{x_,y_, z_};
    }
};

struct line3d
{
    point3d a_;
    point3d b_;

    double length() const noexcept
    {
        double x = b_.x_ - a_.x_;
        double y = b_.y_ - a_.y_;
        double z = b_.z_ - a_.z_;
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
        double n_Cross1 = va_.y_ * vb_.z_ - va_.z_ * vb_.y_;
        double n_Cross2 = va_.z_ * vb_.x_ - va_.x_ * vb_.z_;
        double n_Cross3 = va_.x_ * vb_.y_ - va_.y_ * vb_.x_;

        //calculate normal here
        return line3d{va_, point3d{n_Cross1, n_Cross2, n_Cross3}};
    }
};

std::ostream & operator<<(std::ostream& out, point3d point)
{
    out << "(" << point.x_ << ", " << point.y_ << ", " << point.z_ << ")";
    return out;
}

inline std::ostream &operator<<(std::ostream &out, const vec3 &v)
{
    return out << v.x << ' ' << v.y << ' ' << v.z;
}

inline vec3 operator+(const vec3 &u, const vec3 &v)
{
    return vec3(u.x + v.x, u.y + v.y, u.z + v.z);
}

inline vec3 operator-(const vec3 &u, const vec3 &v)
{
    return vec3(u.x - v.x, u.y - v.y, u.z - v.z);
}

inline vec3 operator*(const vec3 &u, const vec3 &v)
{
    return vec3(u.x * v.x, u.y * v.y, u.z * v.z);
}

inline vec3 operator*(double t, const vec3 &v)
{
    return v.scale(t);
}

inline vec3 operator*(const vec3 &v, double t)
{
    return t * v;
}

inline vec3 operator/(vec3 v, double t)
{
    return v.scale(1 / t);
}

inline point3d operator+(const point3d &p, const vec3 &v)
{
    return point3d{ p.x_ + v.x, p.y_ + v.y, p.z_ + v.z};
}

inline point3d operator-(const point3d &p, const vec3 &v)
{
    return point3d{ p.x_ - v.x, p.y_ - v.y, p.z_ - v.z};
}

inline point3d operator+(const point3d &a, const point3d &b)
{
    return point3d{a.x_ + b.x_, a.y_ + b.y_, a.z_ + b.z_};
}

inline point3d operator-(const point3d &a, const point3d &b)
{
    return point3d{a.x_ - b.x_, a.y_ - b.y_, a.z_ - b.z_};
}

#endif //PROJECT_GRADE_8_VECTOR_POINT_H

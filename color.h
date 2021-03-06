//
// Created by James Beers on 8/6/21.
//

#ifndef PROJECT_GRADE_8_COLOR_H
#define PROJECT_GRADE_8_COLOR_H

#include <iostream>

struct Color
{
    double red = 0;
    double green = 0;
    double blue = 0;
};

inline Color operator*(double t, Color c)
{
    return Color{c.red * t, c.green * t, c.blue * t};
}

inline Color operator/(Color c, int t)
{
    return Color{c.red / t, c.green / t, c.blue / t};
}
inline Color operator+(Color a, Color b)
{
    return Color{a.red + b.red, a.green + b.green, a.blue + b.blue};
}

inline std::ostream &operator<<(std::ostream &out, const Color &c)
{
    return out << "rgb(" << c.red << ", " << c.green << ", " << c.blue << ")";

}

#endif //PROJECT_GRADE_8_COLOR_H

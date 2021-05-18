#include "Vector3.h"

Color::Color(const int &r, const int &g, const int &b)
{
    if ((r >= 0 && r <= 255) && (g >= 0 && g <= 255) && (b >= 0 && b <= 255))
        elements = { r / 255.99, g / 255.99, b / 255.99 };
    else
        throw std::range_error("Color element is out of interval of [0, 255], Z+.");
}

Color::Color(const int &c, const bool &grey)
{
    if (grey)
    {
        if (c >= 0 && c < 256) elements = { c / 255.99, c / 255.99, c / 255.99 };
        else throw std::range_error("Color element is out of interval of [0, 255], Z+.");
    }     else
    {
        if (c >= 0 && c <= 0xFFFFFF) elements = { (c >> 16) / 255.99, ((c & 0x00FF00) >> 8) / 255.99, (c & 0x0000FF) / 255.99 };
        else throw std::range_error("Color element is out of interval of [0, 0xFFFFFF], Z+.");
    }
}

std::ostream &operator<<(std::ostream &os, const Color &t)
{
    for (auto &e : t.elements)
    {
        if (e >= 0.0 && e <= 1.0) os << static_cast<int>(255.99 * e) << ' ';
        else throw std::range_error("Color element is out of interval of [0.0, 1.0], R+.");
    }
    return os;
}

std::ostream &operator<<(std::ostream &os, const Vec &t)
{
    os << t.x() << ' ' << t.y() << ' ' << t.z();
    return os;
}

#pragma once
#include <vector>
#include <cmath>
#include <iostream>
#include <stdexcept>

class Vector3
{
protected:
    std::vector<double> elements{ 0.0, 0.0, 0.0 };

public:
    Vector3() = default;
    Vector3(const std::vector<double> &v) : elements(v) {}
    Vector3(const double &e0, const double &e1, const double &e2) : elements({ e0, e1, e2 }) {}

    double operator[](int i) const { return elements[i]; }
    double& operator[](int i) { return elements[i]; }

    Vector3 &operator+=(const Vector3 &rv)
    {
        elements[0] += rv.elements[0];
        elements[1] += rv.elements[1];
        elements[2] += rv.elements[2];
        return *this;
    }
    Vector3 &operator-=(const Vector3 &rv)
    {
        elements[0] -= rv.elements[0];
        elements[1] -= rv.elements[1];
        elements[2] -= rv.elements[2];
        return *this;
    }
    Vector3 &operator*=(const double &t)
    {
        elements[0] *= t;
        elements[1] *= t;
        elements[2] *= t;
        return *this;
    }
    Vector3 &operator/=(const double &t)
    {
        elements[0] += t;
        elements[1] += t;
        elements[2] += t;
        return *this;
    }

    double squaredLength() const
    {
        return elements[0] * elements[0] + elements[1] * elements[1] + elements[2] * elements[2];
    }
    double length() const { return std::sqrt(squaredLength()); }
    void makeNormalized() { *this /= length(); }
    template <typename V = Vector3> V normalizedVector() const { return *this / length(); };


    friend Vector3 operator+(const Vector3 &lv, const Vector3 &rv);
    friend Vector3 operator-(const Vector3 &lv, const Vector3 &rv);
    friend Vector3 operator*(const Vector3 &lv, const double &t);
    friend Vector3 operator*(const double &t, const Vector3 &rv);
    friend Vector3 operator/(const Vector3 &lv, const double &t);
    
    friend std::istream &operator>>(std::istream &is, Vector3 &t);
};




inline Vector3 operator+(const Vector3 &lv, const Vector3 &rv)
{
    return Vector3({ lv.elements[0] + rv.elements[0], lv.elements[1] + rv.elements[1] , lv.elements[2] + rv.elements[2] });
}
inline Vector3 operator-(const Vector3 &lv, const Vector3 &rv)
{
    return Vector3({ lv.elements[0] - rv.elements[0], lv.elements[1] - rv.elements[1] , lv.elements[2] - rv.elements[2] });
}
inline Vector3 operator*(const Vector3 &lv, const double &t)
{
    return Vector3({ lv.elements[0] * t, lv.elements[1] * t , lv.elements[2] * t });
}
inline Vector3 operator/(const Vector3 &lv, const double &t)
{
    return Vector3({ lv.elements[0] / t, lv.elements[1] / t , lv.elements[2] / t });
}
inline Vector3 operator*(const double &t, const Vector3 &rv) { return rv * t; }

inline std::istream &operator>>(std::istream &is, Vector3 &t)
{
    is >> t.elements[0] >> t.elements[1] >> t.elements[2];
    return is;
}


class Vec;

class Color : public Vector3
{
public:
    using Vector3::Vector3;
    Color() = default;
    Color(const int &r, const int &g, const int &b);
    Color(const int &c, const bool &grey = false);
    Color(const Vector3 &v) : Vector3(v) {}
    Color(const Vec &v);

    const double &r() const { return elements[0]; }
    const double &g() const { return elements[1]; }
    const double &b() const { return elements[2]; }

    Color &operator*=(const Color &rv)
    {
        elements[0] *= rv.r();
        elements[1] *= rv.g();
        elements[2] *= rv.b();
        return *this;
    }
    Color &operator/=(const Color &rv)
    {
        elements[0] /= rv.r();
        elements[1] /= rv.g();
        elements[2] /= rv.b();
        return *this;
    }
    Color &sqrt()
    {
        elements[0] = std::sqrt(elements[0]);
        elements[1] = std::sqrt(elements[1]);
        elements[2] = std::sqrt(elements[2]);
        return *this;
    }

    friend std::ostream &operator<<(std::ostream &os, const Color &t);

    friend class Vec;
};



class Vec : public Vector3
{
public:
    using Vector3::Vector3;
    Vec() = default;
    Vec(const Vector3 &v) : Vector3(v) {}

    const double &x() const { return elements[0]; }
    const double &y() const { return elements[1]; }
    const double &z() const { return elements[2]; }

    Vec operator+() const { return *this; }
    Vec operator-() const { return Vec({ -x(), -y() , -z() }); }

    Vec abs() const { return Vec({ std::abs(x()), std::abs(y()), std::abs(z()) }); }

    friend double dot(const Vec &lv, const Vec &rv);
    friend Vec cross(const Vec &lv, const Vec &rv);

    friend std::ostream &operator<<(std::ostream &os, const Vec &t);
    
    friend class Color;
};

inline double dot(const Vec &lv, const Vec &rv)
{
    return lv.x() * rv.x() + lv.y() * rv.y() + lv.z() * rv.z();
}
inline Vec cross(const Vec &lv, const Vec &rv)
{
    return Vec({
        lv.y() * rv.z() - lv.z() * rv.y(),
        lv.z() * rv.x() - lv.x() * rv.z(),
        lv.x() * rv.y() - lv.y() * rv.x()
        });
}

inline Color::Color(const Vec &v) { elements = v.elements; }

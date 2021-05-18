#pragma once

#include "Ray.h"
#include "Hitable.h"

class Sphere : public Hitable
{ 
    bool recordArchiving(const double &t, HitRecord &rec, const Ray &r) const override;
public:
    Vec center;
    double radius;
    Color color;

    Sphere() = default;
    Sphere(Vec c, double r, Color cl = Color(0x000000)) : center(c), radius(r), color(cl) {};

    bool hit(const Ray &r, HitRecord &rec, const double &t_min = 1.0, const double &t_max = 10000.0) const override;
};

inline bool Sphere::recordArchiving(const double &t, HitRecord &rec, const Ray &r) const
{
    rec.t = t;
    rec.p = r.pointAtParameter(t);
    rec.normal = (rec.p - center) / radius;
    return true;
}

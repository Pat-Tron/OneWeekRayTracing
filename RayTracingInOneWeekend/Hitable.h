#pragma once
#include "Ray.h"

struct HitRecord
{
    // point(t) = Ray.origin + t * Ray.direction
    double t;
    Vec p;  // point
    Vec normal;  // normal vector of this point
};

class Hitable
{
protected:
    virtual bool recordArchiving(const double &t, HitRecord &rec, const Ray &r) const = 0;
public:
    virtual bool hit(const Ray &r, HitRecord &rec, const double &t_min = 1.0, const double &t_max = 10000.0) const = 0;
};

class HitableList : public Hitable
{
public:
    std::vector<Hitable*> list;

    HitableList() = default;
    HitableList(std::vector<Hitable*> l) : list(l) {}

    bool hit(const Ray &r, HitRecord &rec, const double &t_min = 1.0, const double &t_max = 10000.0) const override;
};


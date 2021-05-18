#pragma once

#include "Vector3.h"

class Ray
{
public:
    // p(t) = A + tB; A: origin, B: direction
    Vec origin;
    Vec direction;

    Ray() = default;
    Ray(const Vec &o, const Vec &d) : origin(o), direction(d) {}
    Vec pointAtParameter(double t) const { return origin + t * direction; }
    
};
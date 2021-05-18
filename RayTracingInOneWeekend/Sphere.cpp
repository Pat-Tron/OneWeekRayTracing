#include "Sphere.h"

bool Sphere::hit(const Ray &r, HitRecord &rec, const double &t_min, const double &t_max) const
{
    // For any vec(x,y,z) satisfing this equation is on the sphere and otherwise it is not.
    // (x-Cx)^2 + (y-Cy)^2 + (z-Cz)^2 = R^2 (Sphere center: (Cx, Cy, Cz))
    // dot((r - C), (r - C)) = R * R, r:Ray, C: center Vec
    // dot((O + tD - C), (O + tD - C)) = R * R, O: origin, D: direction
    // t*t*dot(D,D) + 2*t*dot(D,O-C) + dot(O-C,O-C)-R*R=0
    Vec oc{ r.origin - center };
    double a{ dot(r.direction, r.direction) };
    double b{ dot(oc, r.direction) };
    double c{ dot(oc, oc) - radius * radius };
    double discriminant{ b * b - a * c };

    if (discriminant >= 0)
    {
        double root{ (-b - sqrt(discriminant)) / a };
        if (root < t_max && root > t_min) return recordArchiving(root, rec, r);
        root = (-b + sqrt(discriminant)) / a;
        if (root < t_max && root > t_min) return recordArchiving(root, rec, r);
        return false;
    }
    else return false;
}
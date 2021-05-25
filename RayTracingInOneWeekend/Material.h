#pragma once
#include "Ray.h"
#include "Hitable.h"

class Material
{
public:
    virtual bool scatter(const Ray &incidentRay, const HitRecord &rec, Vec &attenuation, Ray &scattered) const = 0;
};

class Lambertian : public Material
{

};
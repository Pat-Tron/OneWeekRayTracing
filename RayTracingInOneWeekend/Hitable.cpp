#include "Hitable.h"

bool HitableList::hit(const Ray &r, HitRecord &rec, const double &t_min, const double &t_max) const
{
    double closestSoFar{ t_max };
    bool hitAnything{ false };
    HitRecord tempRec;

    for (auto obj : list)
    {
        if (obj->hit(r, tempRec, t_min, closestSoFar))
        {
            hitAnything = true;
            closestSoFar = tempRec.t;
        }
    }
    rec = tempRec;
    return hitAnything;
}

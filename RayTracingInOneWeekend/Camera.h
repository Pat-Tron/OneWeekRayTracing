#pragma once

#include "Ray.h"
#include <iostream>
class Camera
{
    double pixelHeight;
    double pixelWidth;
public:
    // Right hand coordinate: x: right, y: up, z: back
    // image resolution
    int rx;
    int ry;
    // Place camara(eye) at the origin.
    Vec cameraPosition;

    double focal;
    Vec imageCenter;

    double imageHeight;
    double imageWidth;
    Vec lowerLeftCorner;

    bool antialiasingFlag{ false };
    int antialiasingPrecision{ 100 };

    Camera(
        const int &rx = 200,
        const int &ry = 200,
        const Vec &cameraPosition = Vec(0.0, 0.0, 0.0),
        const double &focal = 100,
        const double &imageHeight = 100
    );

    template<typename T = int> Ray getRay(const T &u, const T &v)
    {
        //std::cout << u << ' ' << v << std::endl;
        return Ray(cameraPosition, lowerLeftCorner + Vec(u * pixelWidth, v * pixelHeight, 0) - cameraPosition);
    }
};


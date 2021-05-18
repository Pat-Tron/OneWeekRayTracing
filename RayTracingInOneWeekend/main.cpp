#include <iostream>
#include <fstream>

#include "Vector3.h"
#include "Ray.h"
#include "Sphere.h"

#include "Colors.h"

Color backgroudColor(const Ray &r);
Color colorCalculator(const Ray &r, HitRecord &rec, const Sphere &s);

int main()
{
    // Right hand coordinate: x: right, y: up, z: back
    // image resolution
    int rx{ 20 };
    int ry{ 20 };
    // Place camara(eye) at the origin.
    Vec camaraPosition(0, 0, 0);

    double focal{ 100 };
    Vec imageCenter{ camaraPosition + Vec(0, 0, -focal) };
    
    double imageHeight{ 100 };
    double imageWidth{ static_cast<double>(rx) / static_cast<double>(ry) * imageHeight };
    Vec lowerLeftCorner{ imageCenter - Vec(imageWidth / 2, imageHeight / 2, 0) };
    double pixelHeight{ imageHeight / ry };
    double pixelWidth{ imageWidth / rx };




    // Volumes
    Sphere ball_1(imageCenter - Vec(0, 0, 20), 40.0, red);





    // Write image data.
    std::ofstream out;
    out.open("../../test.ppm");
    out << "P3\n" << rx << " " << ry << "\n255\n";
    HitRecord tmpRecord;

    for (int j{ ry - 1 }; j >= 0; j--)
    {
        for (int i{ 0 }; i < rx; i++)
        {
            double u{ i * pixelWidth };
            double v{ j * pixelHeight };
            Ray r(camaraPosition, lowerLeftCorner + Vec(u, v, 0));
            out << colorCalculator(r, tmpRecord, ball_1) << std::endl;
        }
        std::cout << j << '\n';
    }

    out.close();
    return 0;
}


Color backgroudColor(const Ray &r)
{
    double t{ 0.5 * (r.direction.normalizedVector<Vec>().y() + 1.0) };
    return (1.0 - t) * purple + t * blue;
}

Color colorCalculator(const Ray &r, HitRecord &rec, const Sphere &s)
{
    if (s.hit(r, rec)) return (rec.normal + Vec(1.0, 1.0, 1.0)) / 2.0;
    else return backgroudColor(r);
}
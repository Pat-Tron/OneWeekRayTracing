#include <iostream>
#include <fstream>
#include <random>

#include "Vector3.h"
#include "Ray.h"
#include "Sphere.h"
#include "Camera.h"

#include "Colors.h"

Color backgroudColor(const Ray &r);
Color colorCalculator(const int &i, const int &j, HitRecord &rec, const Sphere &s);

Camera cam(2000, 1000);
//Camera cam(100, 100);

int main()
{
    cam.antialiasingFlag = true;
    cam.antialiasingPrecision = 100;

    // Volumes
    Sphere ball_1(cam.imageCenter - Vec(0, 0, 100), 70.0, red);



    // Write image data.
    std::ofstream out;
    out.open("../../test.ppm");
    out << "P3\n" << cam.rx << " " << cam.ry << "\n255\n";


    HitRecord tmpRecord;
    for (int j{ cam.ry - 1 }; j >= 0; j--)
    {
        for (int i{ 0 }; i < cam.rx; i++)
        {
            out << colorCalculator(i, j, tmpRecord, ball_1) << std::endl;
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

Color colorCalculator(const int &i, const int &j, HitRecord &rec, const Sphere &s)
{
    if (cam.antialiasingFlag)
    {
        Vector3 tmp(0.0, 0.0, 0.0);  // temperary color
        // Random double between [0, 1)
        //static std::uniform_real_distribution<double> distribution(-0.1, 0.1);
        //static std::default_random_engine engine;

        //for (int a{ 0 }; a < cam.antialiasingPrecision; a++)
        //{
        //    const Ray &&r{ cam.getRay(i + distribution(engine), j + distribution(engine)) };
        //    if (s.hit(r, rec)) tmp += (rec.normal + Vec(1.0, 1.0, 1.0)) / 2.0;
        //    else tmp += backgroudColor(r);
        //}
        // return tmp / cam.antialiasingPrecision;

        const int precision1{ 4 };
        const double precision2{ 10.0 };
        const double precision3{ ((precision1 * 2) + 1) * ((precision1 * 2) + 1) };

        for (int x{ -precision1 }; x <= precision1; x++)
        {
            for (int y{ -precision1 }; y <= precision1; y++)
            {
                const Ray &&r{ cam.getRay(i + x / precision2, j + y / precision2) };
                if (s.hit(r, rec)) tmp += (rec.normal + Vec(1.0, 1.0, 1.0)) / 2.0;
                else tmp += backgroudColor(r);
            }
        }
        return tmp / precision3;
        

    } else
    {
        const Ray &&r{ cam.getRay(i, j) };
        if (s.hit(r, rec)) return (rec.normal + Vec(1.0, 1.0, 1.0)) / 2.0;
        else return backgroudColor(r);
    }
    



}
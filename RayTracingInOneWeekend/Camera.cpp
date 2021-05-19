#include "Camera.h"

Camera::Camera(
    const int &rx,
    const int &ry,
    const Vec &camaraPosition,
    const double &focal,
    const double &imageHeight
) : rx(rx), ry(ry), cameraPosition(camaraPosition), focal(focal), imageHeight(imageHeight)
{
    imageCenter = camaraPosition + Vec(0, 0, -focal);
    imageWidth = static_cast<double>(rx) / static_cast<double>(ry) * imageHeight;
    lowerLeftCorner = imageCenter - Vec(imageWidth / 2, imageHeight / 2, 0);
    pixelHeight = imageHeight / ry;
    pixelWidth = imageWidth / rx;
}
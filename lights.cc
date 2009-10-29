#include "lights.hh"

void Light::ray(const Point &point, Vec3 &dir) const {
    dir = location - point;
    dir.normalize();
}

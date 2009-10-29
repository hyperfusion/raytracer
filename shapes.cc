#include "shapes.hh"

// intersection algorithms from various common proofs from the Internet
bool Sphere::intersect(const Ray &ray, Point &intersection) const {
    double a = ray.dir.dotproduct(ray.dir);
    Vec3 origintocenter = ray.origin - center;
    double b = 2. * ray.dir.dotproduct(origintocenter);
    double c = origintocenter.dotproduct(origintocenter) - _radius2;

    double dis = b*b - 4.*a*c;
    if (dis < 0)
        return false;

    double t = (-b + sqrt(dis)) / (2.*a),
          t1 = (-b - sqrt(dis)) / (2.*a);

    // use the closest intersection point
    if (t1 < t)
        t = t1;

    intersection.x = ray.origin.x + ray.dir.x * t;
    intersection.y = ray.origin.y + ray.dir.y * t;
    intersection.z = ray.origin.z + ray.dir.z * t;

    return true;
}

/*bool Sphere::intersect(const Ray &ray, Vec3 &intersection) {
    Vec3 raytocenter = center;
    raytocenter.subtract(ray.origin);
    double len = raytocenter.dotproduct(raytocenter);
    double closestapproach = raytocenter.dotproduct(ray.dir);
    if (closestapproach < 0) // intersection behind the ray
        return false;
    double halfcord = radius*radius - len + closestapproach*closestapproach;
    return halfcord >= 0;
}*/

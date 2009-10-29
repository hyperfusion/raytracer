#include "scene.hh"

#include "lights.hh"

#include <iostream>
using namespace std;

const Shape *Scene::_get_closest_intersection(const Ray &ray, Vec3 &intersection, double &distance) const {
    const Shape *closest = NULL;
    distance = 0.;
    for (list<const Shape *>::const_iterator s = _shapes.begin(), e = _shapes.end(); s != e; ++s) {
        if ((*s)->intersect(ray, intersection)) {
            double dist = ray.origin.distance(intersection);
            if (dist < distance || closest == NULL) {
                distance = dist;
                closest = *s;
            }
        }
    }
    return closest;
}

void Scene::_get_color(const Shape &shape, const Vec3 &point, Color &color) const {
    Vec3 normal, lightray;
    for (list<const Light *>::const_iterator light = _lights.begin(), e = _lights.end(); light != e; ++light) {
        // get the normal vector of the surface at the intersection point
        shape.normal(point, normal);
        normal.normalize();

        // get the vector from the intersection point to the light
        (*light)->ray(point, lightray);

        // set the color intensity
        double factor = normal.dotproduct(lightray);
        if (factor > 0)
            color += shape.material.color * (*light)->color * factor;
    }
}

void Scene::render(BMPImage &image) const {
    // this is the ray that's fired toward the direction vectors
    Ray ray(_camera);

    // for every ray...
    for (int y = 0; y < _height; ++y) {
        for (int x = 0; x < _width; ++x) {
            // the ray goes from the camera location to the current point on the table/grid
            // we need to generate the vector that represents the grid point
            ray.dir = Vec3(x - _width/2., _height/2. - y, _fov);
            ray.dir.normalize();

            // find the closest object that the ray intersects
            double distance;
            Vec3 intersection;
            const Shape *closest = _get_closest_intersection(ray, intersection, distance);

            if (closest) {
                // now, we've found the closest object that the ray from the camera's origin
                // to (x, y) on the grid intersects
                // now, render the color at (x, y) in the image
                Color color(0, 0, 0);
                _get_color(*closest, intersection, color);
                image.add(color);
            }
            else
                image.add(0, 0, 0);
        }
    }
}

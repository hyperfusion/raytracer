#ifndef __SCENE_H__
#define __SCENE_H__

#include <list>
using std::list;

#include "shapes.hh"
#include "lights.hh"

#include "bmpimage.hh"

class Scene {
private:
    list<const Shape *> _shapes;
    list<const Light *> _lights;

    const Vec3 _camera;
    double _fov;
    const unsigned int _width, _height;

    const Shape *_get_closest_intersection(const Ray &ray, Vec3 &intersection, double &distance) const;
    void _get_color(const Shape &shape, const Vec3 &point, Color &color) const;

public:
    Scene(unsigned int width, unsigned int height, const Vec3 &camera, double fov) : _width(width), _height(height), _camera(camera), _fov(fov) { }

    void add(const Shape &s) { _shapes.push_back(&s); }
    void add(const Light &l) { _lights.push_back(&l); }

    void render(BMPImage &image) const;
};

#endif // __SCENE_H__

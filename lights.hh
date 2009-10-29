#ifndef __LIGHTS_HH__
#define __LIGHTS_HH__

#include "util.hh"
#include "shapes.hh"

struct Light {
    Point location;
    Color color;

    Light(const Point &location_, const Color &color_) : location(location_), color(color_) { }

    /**
     * Sets dir to the vector from the point to this light
     */
    void ray(const Point &point, Vec3 &dir) const;
};

#endif // __LIGHTS_HH__

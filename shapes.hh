#ifndef __SHAPES_HH__
#define __SHAPES_HH__

#include <string>
#include <cmath>
#include <ostream>

/**
 * A vector of three elements
 */
struct Vec3 {
    double x, y, z;

    Vec3() { }
    Vec3(double x_, double y_, double z_) : x(x_), y(y_), z(z_) { }

    /**
     * Returns the distance from this vector to v
     */
    double distance(const Vec3 &v) const {
        return std::sqrt((x - v.x) * (x - v.x) +
                         (y - v.y) * (y - v.y) +
                         (z - v.z) * (z - v.z));
    }

    /**
     * Returns the length/norm of the vector
     */
    double length() const {
        return std::sqrt(x*x + y*y + z*z);
    }

    /**
     * Reduces x, y, z so that length = 1
     */
    void normalize() {
        double n = length();
        x /= n; y /= n; z /= n;
    }

    /**
     * Returns the dot product of this vector and v
     */
    double dotproduct(const Vec3 &v) const { return x*v.x + y*v.y + z*v.z; }

    /**
     * Adds this vector and a
     */
    void add(const Vec3 &a) { x += a.x; y += a.y; z += a.z; }
    void operator +=(const Vec3 &a) { add(a); }
    friend Vec3 operator +(const Vec3 &a, const Vec3 &b) { Vec3 tmp = a; tmp.add(b); return tmp; }

    void add(double a) { x += a; y += a; z += a; }
    void operator +=(double a) { add(a); }
    friend Vec3 operator +(const Vec3 &a, double b) { Vec3 tmp = a; tmp.add(b); return tmp; }

    /**
     * Subtracts a from this vector
     */
    void subtract(const Vec3 &a) { x -= a.x; y -= a.y; z -= a.z; }
    void operator -=(const Vec3 &a) { subtract(a); }
    friend Vec3 operator -(const Vec3 &a, const Vec3 &b) { Vec3 tmp = a; tmp.subtract(b); return tmp; }

    void subtract(double a) { x -= a; y -= a; z -= a; }
    void operator -=(double a) { subtract(a); }
    friend Vec3 operator -(const Vec3 &a, double b) { Vec3 tmp = a; tmp.subtract(b); return tmp; }


    void multiply(const Vec3 &a) { x *= a.x; y *= a.y; z *= a.z; }
    void operator *=(const Vec3 &a) { multiply(a); }
    friend Vec3 operator *(const Vec3 &a, const Vec3 &b) { Vec3 tmp = a; tmp.multiply(b); return tmp; }

    void multiply(double a) { x *= a; y *= a; z *= a; }
    void operator *=(double a) { multiply(a); }
    friend Vec3 operator *(const Vec3 &a, double b) { Vec3 tmp = a; tmp.multiply(b); return tmp; }

    void divide(const Vec3 &a) { x /= a.x; y /= a.y; z /= a.z; }
    void operator /=(const Vec3 &a) { divide(a); }
    friend Vec3 operator /(const Vec3 &a, const Vec3 &b) { Vec3 tmp = a; tmp.divide(b); return tmp; }

    void divide(double a) { x /= a; y /= a; z /= a; }
    void operator /=(double a) { divide(a); }
    friend Vec3 operator /(const Vec3 &a, double b) { Vec3 tmp = a; tmp.divide(b); return tmp; }

    /**
     * For debugging: represents this vector as "(x, y, z)"
     */
    friend std::ostream &operator <<(std::ostream &os, const Vec3 &m) { return os << '(' << m.x << ", " << m.y << ", " << m.z << ')' << std::endl; }
};

typedef Vec3 Point;

// yeah... i'll change this later
/*
 * A color, with each channel represented as a number from 0.0 to 1.0
 */
typedef Vec3 Color;

/**
 * An RGB triplet; each channel is represented as a number from 0 to 255
 */
struct RGB {
    unsigned char r, g, b;

    RGB() { }
    RGB(unsigned char r_, unsigned char g_, unsigned char b_) : r(r_), g(g_), b(b_) { }
    RGB(const Color &color) {
        r = (unsigned char) (std::min(color.x * 255., 255.));
        g = (unsigned char) (std::min(color.y * 255., 255.));
        b = (unsigned char) (std::min(color.z * 255., 255.));
    }
};


/**
 * A ray from the origin vector, in a particular direction
 */
struct Ray {
    Point origin;
    Vec3 dir;

    Ray(const Point &origin_, const Vec3 &dir_) : origin(origin_), dir(dir_) { }
    Ray(const Point &origin_) : origin(origin_) { }
};


struct Material {
    Color color;

    // TODO: add more attributes

    Material() { }
};

struct Shape {
    std::string name;
    Material material;

    Shape() { }

    /*
     * Returns whether the given ray intersects the Shape. If there is an intersection,
     * that point is stored in intersection.
     */
    virtual bool intersect(const Ray &ray, Point &intersection) const = 0;

    virtual void normal(const Point &point, Vec3 &normal) const = 0;
};

struct Plane : public Shape {
};

struct Sphere : public Shape {
    Point center;
    double radius;

    Sphere() { }
    Sphere(const Vec3 &center_, double radius_) : center(center_), radius(radius_), _radius2(radius_ * radius_) { }

    bool intersect(const Ray &ray, Point &intersection) const;
    void normal(const Point &point, Vec3 &normal) const { normal = (point - center) / radius; }

private:
    double _radius2;
};

#endif // __SHAPES_HH__

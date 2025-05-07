#ifndef SPHERE_H
#define SPERE_H

#include "vec3.h"
#include "ray.h"

class Sphere{
    public:
        // big 3
        Sphere();
        Sphere(const Sphere &in);
        Sphere operator= (const Sphere &in);

        // other constructor
        Sphere(Vec3 c, float r);
        Sphere(Vec3 c, float r, float in_w_r);
        Sphere(Vec3 c, float r, float in_w_r, float in_w_t);

        float hit_sphere(const Ray &ray, float min_t, float max_t);

        // getters
        Vec3 get_center() const;
        float get_w_r() const;
        float get_w_t() const;
    private:
        Vec3 center;
        float radius;

        float w_r;
        float w_t;
};

#endif
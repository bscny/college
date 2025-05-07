#ifndef SPHERE_H
#define SPERE_H

#include "vec3.h"
#include "ray.h"

class Sphere{
    public:
        // big 3
        Sphere();
        Sphere(Vec3 c, float r);
        Sphere(const Sphere &in);
        Sphere operator= (const Sphere &in);

        float hit_sphere(const Ray &ray, float min_t, float max_t);

        // getters
        Vec3 get_center() const;
    private:
        Vec3 center;
        float radius;
};

#endif
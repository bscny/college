#ifndef RAYH
#define RAYH

#include "vec3.h"

class Ray
{
public:
    Vec3 O;   // the origing point
    Vec3 Dir; // direction unit vector

    Ray()
    {
        O = Vec3(0, 0, 0);
        Dir = Vec3(0, 0, 0);
    }

    Ray(const Ray &r);

    Ray(const Vec3 origin, const Vec3 dir);

    // member funcs
    Ray &operator=(const Ray &r);

    inline Vec3 origin() const { return O; }

    inline Vec3 direction() const { return Dir; }

    inline Vec3 point_at_parameter(float t) const;
};

Ray::Ray(const Ray &r){
    O = r.O;
    Dir = r.Dir;
}

Ray::Ray(const Vec3 origin, const Vec3 dir){
    O = origin;
    Dir = unit_vector(dir);
}

Ray &Ray::operator=(const Ray &r){
    O = r.O;
    Dir = r.Dir;

    return *this;
}

Vec3 Ray::point_at_parameter(float t) const{
    return Vec3(O.e[0] + t * Dir.e[0], O.e[1] + t * Dir.e[1], O.e[2] + t * Dir.e[2]);
}

#endif
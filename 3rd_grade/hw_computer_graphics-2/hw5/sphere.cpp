#include "sphere.h"
#include <cmath>

// the big 3
Sphere::Sphere(){
    center = Vec3(0, 0, 0);
    radius = 1;

    w_r = 0;
}

Sphere::Sphere(const Sphere &in){
    center = in.center;
    radius = in.radius;
    w_r = in.w_r;
}

Sphere Sphere::operator= (const Sphere &in){
    center = in.center;
    radius = in.radius;
    w_r = in.w_r;

    return *this;
}

// other constructor
Sphere::Sphere(Vec3 c, float r){
    center = c;
    radius = r;

    w_r = 0;
}

Sphere::Sphere(Vec3 c, float r, float in_w_r){
    center = c;
    radius = r;

    w_r = in_w_r;
}

// get the t value for the given ray, if t < max_t, return the t
float Sphere::hit_sphere(const Ray &ray, float min_t, float max_t){
    // O is origin of the ray, D is direction vector, C is sphere center. They are all vectors
    // || O + tD - C || = r
	// (O dot O) + 2t(O dot D) - 2(O dot C) + t^2(D dot D) - 2t(D dot C) + C dot C = r^2
	// t^2 + [2(O dot D) - 2(D dot C)]*t + [(O dot O) - 2(O dot C) + (C dot C) - r^2] = 0
	float a = 1;
	float b = 2 * (dot(ray.origin(), ray.direction()) - dot(ray.direction(), center));
	float c = dot(ray.origin(), ray.origin()) - 2 * dot(ray.origin(), center) + dot(center, center) - radius*radius;
	float b_sqr = pow(b, 2);
	
	if(b_sqr >= 4 * a * c){
		// Hit!!
		// since we want to "look at" the surface, we use subtraction
		float t = (-b - sqrt(b_sqr - 4 * a * c)) / (2 * a);

        if(t < max_t && t > min_t){
            // update the recorded index
            return t;
        }else{
            return -1;
        }
	}else{
		return -1;
	}
}

// getters
Vec3 Sphere::get_center() const {
    return center;
}
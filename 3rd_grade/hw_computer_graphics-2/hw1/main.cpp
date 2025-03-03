#include <iostream>
#include <fstream>
#include "vec3.h"
#include "ray.h"

using namespace std;

float hit_sphere(const Vec3 sphere_center, const float r, const Ray &ray){
	// || O + tD - C || = r
	// (O dot O) + 2t(O dot D) - 2(O dot C) + t^2(D dot D) - 2t(D dot C) + C dot C = r^2
	// t^2 + [2(O dot D) - 2(D dot C)]*t + [(O dot O) - 2(O dot C) + (C dot C) - r^2] = 0
	float a = 1;
	float b = 2 * (dot(ray.origin(), ray.direction()) - dot(ray.direction(), sphere_center));
	float c = dot(ray.origin(), ray.origin()) - 2 * dot(ray.origin(), sphere_center) + dot(sphere_center, sphere_center) - r*r;
	float b_sqr = pow(b, 2);
	
	if(b_sqr >= 4 * a * c){
		// Hit!!
		// since we want to "look at" the surface, we use subtraction
		return (-b - sqrt(b_sqr - 4 * a * c)) / (2 * a);
	}else{
		return -1;
	}
}

float hit_spheres(const Vec3 (&sphere_centers)[], const float (&rs)[], const Ray &ray, int &hit_index){
	// check every spheres
	for(int i = 0; i < 3; i ++){
		float a = 1;
		float b = 2 * (dot(ray.origin(), ray.direction()) - dot(ray.direction(), sphere_centers[i]));
		float c = dot(ray.origin(), ray.origin()) - 2 * dot(ray.origin(), sphere_centers[i]) + dot(sphere_centers[i], sphere_centers[i]) - rs[i]*rs[i];
		float b_sqr = pow(b, 2);
		
		if(b_sqr >= 4 * a * c){
			// Hit!!
			// since we want to "look at" the surface, we use subtraction
			hit_index = i;

			return (-b - sqrt(b_sqr - 4 * a * c)) / (2 * a);
		}
	}

	return -1;
}

// only works for normal vector that is (0, 0, z)
float hit_cube(const Vec3 &center_point, const float len, const Ray &ray){
	// we have z = k as the equation, and k satisfy the center point
	// find the point P that the ray and plane intersect
	// origin.z + t*direction.z = k
	// now, we check if P and center point's distance in x and y is less than len/2
	float k = center_point.z();

	if(ray.direction().x() == 0 && ray.direction().y() == 0){
		return -1;
	}

	float t = (k - ray.origin().z()) / ray.direction().z();

	if(t < 0){
		return -1;
	}

	Vec3 P(ray.point_at_parameter(t));

	// check x
	if(pow(P.x() - center_point.x(), 2) > pow(len / 2, 2)){
		return -1;
	}

	// check y
	if(pow(P.y() - center_point.y(), 2) > pow(len / 2, 2)){
		return -1;
	}

	return t;
}

Vec3 color(const Ray &r){
	// predefined objs' posotion
	// Vec3 sphere_center(0, 0, -1);
	Vec3 sphere_centers[3];
	float rs[3];

	// Vec3 cube_center(0, 0, -2);

	Vec3 light_source(0, 0, 0);
	// Vec3 light_sources[3];

	Vec3 light_intensity(1, 1, 1);
	// Vec3 light_intensities[3];
	
	/*light_sources[0] = Vec3(-1, -1, 0);
	light_sources[1] = Vec3(0, 0, 0);
	light_sources[2] = Vec3(1, 1, 0);

	light_intensities[0] = Vec3(1, 0, 0);
	light_intensities[1] = Vec3(0, 1, 0);
	light_intensities[2] = Vec3(0, 0, 1);*/

	sphere_centers[0] = Vec3(0, 0, -1);
	sphere_centers[1] = Vec3(-2, -1, -2);
	sphere_centers[2] = Vec3(2, 0, -2);

	rs[0] = 0.5;
	rs[1] = 0.5;
	rs[2] = 0.5;

	int hit_index = -1;

	// float t = hit_sphere(sphere_center, 0.5, r);
	float t = hit_spheres(sphere_centers, rs, r, hit_index);
	// float t = hit_cube(cube_center, 2, r);
	
	// red sphere
	/*if(t > 0){
		return Vec3(1, 0, 0);
	}*/

	// normal
	/*if(t > 0){
		Vec3 N(unit_vector(r.point_at_parameter(t) - sphere_center));

		return 0.5 * Vec3(N.x() + 1, N.y() + 1, N.z() + 1);
	}*/

	// shading
	/*if(t > 0){
		Vec3 N(unit_vector(r.point_at_parameter(t) - sphere_center));
		Vec3 L(unit_vector(light_source - r.point_at_parameter(t)));

		if(dot(N, L) < 0){
			return Vec3(0, 0, 0);
		}

		return dot(N, L) * light_intensity;
	}*/

	// bonus:
	// Multiple lightsource and colorful intensity
	/*if(t > 0){
		Vec3 N(unit_vector(r.point_at_parameter(t) - sphere_center));
		Vec3 final_intensity;

		for(int i = 0; i < 3; i ++){
			Vec3 L(unit_vector(light_sources[i] - r.point_at_parameter(t)));

			if(dot(N, L) >= 0){
				final_intensity += (dot(N, L) * light_intensities[i]);
			}
		}

		return final_intensity;
	}*/

	// Multiple sphere
	if(t > 0){
		Vec3 N(unit_vector(r.point_at_parameter(t) - sphere_centers[hit_index]));
		Vec3 L(unit_vector(light_source - r.point_at_parameter(t)));

		if(dot(N, L) < 0){
			return Vec3(0, 0, 0);
		}

		return dot(N, L) * light_intensity;
	}

	// Ray - plane intersection
	/*if(t > 0){
		Vec3 N(0, 0, 1);
		Vec3 L(unit_vector(light_source - r.point_at_parameter(t)));

		if(dot(N, L) < 0){
			return Vec3(0, 0, 0);
		}

		return dot(N, L) * light_intensity;
	}*/

	// skybox BG
	t = 0.5 * (r.direction().y() + 1);

	return (1.0 - t) * Vec3(1, 0.2, 0) + t * Vec3(1, 0.8, 0.5);
}

int main()
{
	int width = 200;
	int height = 100;

	Vec3 lower_left_corner(-2, -1, -1);
	Vec3 origin(0, 0, 0);
	Vec3 horizontal(4, 0, 0);
	Vec3 vertical(0, 2, 0);

	/*fstream file;
	file.open("default.ppm", ios::out);

	file << "P3\n" << width << " " << height << "\n255\n";
	for (int j = height - 1; j >= 0; j--) {
		for (int i = 0; i < width; i++) {
			float r = float(i) / float(width);
			float g = float(j) / float(height);
			float b = 0.2;

			file << int(r * 255) << " " << int(g * 255) << " " << int(b * 255) << "\n";
		}
	}*/

	fstream file;
	// file.open("../images/skybox.ppm", ios::out);
	// file.open("../images/red_sphere.ppm", ios::out);
	// file.open("../images/normal.ppm", ios::out);
	// file.open("../images/shading.ppm", ios::out);
	// file.open("../images/multi_light_color.ppm", ios::out);
	file.open("../images/multi_sphere.ppm", ios::out);
	// file.open("../images/cube.ppm", ios::out);


	file << "P3\n" << width << " " << height << "\n255\n";
	for (int j = height - 1; j >= 0; j--) {
		for (int i = 0; i < width; i++) {
			float ratio_h = float(i) / float(width);
			float ratio_v = float(j) / float(height);
			Vec3 target_point = lower_left_corner + ratio_h * horizontal + ratio_v * vertical;

			Ray r(origin, target_point - origin);

			Vec3 c = color(r);

			file << int(c[0] * 255) << " " << int(c[1] * 255) << " " << int(c[2] * 255) << "\n";
		}
	}

	return 0;
}
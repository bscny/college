#include <iostream>
#include <fstream>
#include <vector>
#include <cmath>
#include <cstdlib>

// custom
#include "vec3.h"
#include "ray.h"
#include "sphere.h"

using namespace std;

#define   INF   4294967296

// out put size
int width = 1000;
int height = 500;

// camera params
Vec3 lower_left_corner(-2, -1, -1);
Vec3 origin(0, 0, 1);
Vec3 horizontal(4, 0, 0);
Vec3 vertical(0, 2, 0);

// light params
Vec3 light_pos(-10, 10, 0);
Vec3 light_intensity(1, 1, 1);

// scene object params
vector<Sphere> obj_list;

// for each ray, see the interaction with every scene objs
Vec3 color(const Ray &r, int bounce){
	if(bounce < 0){
		return Vec3(0, 0, 0);
	}

	int record_index = -1;
	float t = INF;
	for(int obj_index = 0; obj_index < (int)obj_list.size(); obj_index ++){
		float ans = obj_list[obj_index].hit_sphere(r, 0.01, t);

		if(ans > 0){
			// find intersact that is close enough!
			t = ans;
			record_index = obj_index;
		}
	}

	if(record_index == -1){
		// nothing hit! return default skybox BG
		t = 0.5 * (r.direction().y() + 1);

		return (1.0 - t) * Vec3(1, 1, 1) + t * Vec3(0.5, 0.7, 1);
	}

	// apply shading result
	Vec3 N(unit_vector(r.point_at_parameter(t) - obj_list[record_index].get_center()));
	Vec3 L(unit_vector(light_pos - r.point_at_parameter(t)));
	Vec3 In(-r.Dir);

	// the reflection ray
	// R = In + 2 * cos * N
	Ray R(r.point_at_parameter(t), (2 * N * dot(N, In)) - In);

	// the refraction ray
	// see detailed in https://en.wikipedia.org/wiki/Snell%27s_law
	// and https://physics.stackexchange.com/questions/435512/snells-law-in-vector-form
	float eta = 1 / 1.458; // for glass
	float cos2 = sqrt(1 - pow(eta, 2) * (1 - pow(dot(N, r.Dir), 2)) );
	Ray T(r.point_at_parameter(t), eta * r.Dir + (eta * dot(N, r.Dir) - cos2) * N );
	// Ray T(r.point_at_parameter(t), eta * (r.Dir - dot(N, r.Dir) * N) - sqrt(1 - eta * (1 - pow(dot(N, r.Dir), 2) ) ) * N);

	Vec3 local_color;

	if(dot(N, L) < 0){
		local_color = Vec3(0, 0, 0);
	}else{
		local_color = dot(N, L) * light_intensity;
	}

	Vec3 reflected_color = color(R, bounce - 1);
	Vec3 refracted_color = color(T, bounce - 1);

	// return (1 - obj_list[record_index].get_w_r()) * local_color + obj_list[record_index].get_w_r() * reflected_color;
	return (1 - obj_list[record_index].get_w_t()) * 
		   ( (1 - obj_list[record_index].get_w_r()) * local_color + obj_list[record_index].get_w_r() * reflected_color) +
		   obj_list[record_index].get_w_t() * refracted_color;
}

int main()
{
	obj_list.push_back(Sphere(Vec3(0, -100.5, -2), 100));
	obj_list.push_back(Sphere(Vec3(0, 0, -2), 0.5, 0, 0.9));
	obj_list.push_back(Sphere(Vec3(1, 0, -1.75), 0.5, 1));
	obj_list.push_back(Sphere(Vec3(-1, 0, -2.25), 0.5));

	srand(1234);
	for (int i = 0; i < 48; i++) {
		float xr = ((float)rand() / (float)(RAND_MAX)) * 6.0f - 3.0f;
		float zr = ((float)rand() / (float)(RAND_MAX)) * 3.0f - 1.5f;
		obj_list.push_back(Sphere(Vec3(xr, -0.45, zr-2), 0.05));
	}

	fstream file;
	// file.open("../images/default.ppm", ios::out);
	// file.open("../images/reflection.ppm", ios::out);
	file.open("../images/refraction.ppm", ios::out);

	file << "P3\n" << width << " " << height << "\n255\n";
	for (int j = height - 1; j >= 0; j--) {
		for (int i = 0; i < width; i++) {
			float ratio_h = float(i) / float(width);
			float ratio_v = float(j) / float(height);
			Vec3 target_point = lower_left_corner + ratio_h * horizontal + ratio_v * vertical;

			Ray r(origin, target_point - origin);

			// for each ray, see the final color it contributes to the screen
			Vec3 c = color(r, 5);

			file << int(c[0] * 255) << " " << int(c[1] * 255) << " " << int(c[2] * 255) << "\n";
		}
	}

	return 0;
}
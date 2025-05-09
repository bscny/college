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
int WIDTH = 1000;
int HEIGHT = 500;
int SAMPLES_PER_PIXAL = 25;
bool ANTI_ALIASING = true;

// camera params
Vec3 LOWER_LEFT_CONER(-2, -1, -1);
Vec3 ORIGIN(0, 0, 1);
Vec3 HORIZONTAL(4, 0, 0);
Vec3 VERTICAL(0, 2, 0);

// light params
Vec3 LIGHT_POS(-10, 10, 0);
Vec3 LIGHT_INTENSITY(1, 1, 1);

// scene object params
vector<Sphere> OBJ_LIST;

float trace_shadow_ray(const Ray &r, float distance2light){
	// since ray.Dir is unit vector, t == distance
	float t;
	for(int obj_index = 0; obj_index < (int)OBJ_LIST.size(); obj_index ++){
		t = OBJ_LIST[obj_index].hit_sphere(r, 0.01, distance2light);

		if(t > 0){
			// find intersact that is close enough!
			return 0;
		}
	}

	// nothing block the light
	return 1;
}

// for each ray, see the interaction with every scene objs
Vec3 color(const Ray &r, int bounce){
	if(bounce < 0){
		return Vec3(0, 0, 0);
	}

	int record_index = -1;
	float t = INF;
	for(int obj_index = 0; obj_index < (int)OBJ_LIST.size(); obj_index ++){
		float ans = OBJ_LIST[obj_index].hit_sphere(r, 0.01, t);

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
	Vec3 P(r.point_at_parameter(t));
	Vec3 N(unit_vector(P - OBJ_LIST[record_index].get_center()));
	Vec3 L(unit_vector(LIGHT_POS - P));
	Vec3 In(-r.Dir);

	// the reflection ray
	// R = In + 2 * cos * N
	Ray R(P, (2 * N * dot(N, In)) - In);

	// the refraction ray
	// see detailed in https://en.wikipedia.org/wiki/Snell%27s_law
	// and https://physics.stackexchange.com/questions/435512/snells-law-in-vector-form
	float eta = 1 / 1.458; // for glass
	float cos2 = sqrt(1 - pow(eta, 2) * (1 - pow(dot(N, r.Dir), 2)) );
	Ray T(P, eta * r.Dir + (eta * dot(N, r.Dir) - cos2) * N );

	Vec3 local_color;
	float occlude_lv = 0;

	if(dot(N, L) < 0){
		local_color = Vec3(0, 0, 0);
	}else{
		occlude_lv = trace_shadow_ray(Ray(P, L), sqrt(dot(LIGHT_POS - P, LIGHT_POS - P)) );
		local_color = occlude_lv * dot(N, L) * LIGHT_INTENSITY;
	}

	Vec3 reflected_color = color(R, bounce - 1);
	Vec3 refracted_color = color(T, bounce - 1);

	// return (1 - OBJ_LIST[record_index].get_w_r()) * local_color + OBJ_LIST[record_index].get_w_r() * reflected_color;
	return (1 - OBJ_LIST[record_index].get_w_t()) * 
		   ( (1 - OBJ_LIST[record_index].get_w_r()) * local_color + OBJ_LIST[record_index].get_w_r() * reflected_color) +
		   OBJ_LIST[record_index].get_w_t() * refracted_color;
}

int main()
{
	OBJ_LIST.push_back(Sphere(Vec3(0, -100.5, -2), 100));
	OBJ_LIST.push_back(Sphere(Vec3(0, 0, -2), 0.5, 0, 0.9));
	OBJ_LIST.push_back(Sphere(Vec3(1, 0, -1.75), 0.5, 1));
	OBJ_LIST.push_back(Sphere(Vec3(-1, 0, -2.25), 0.5));

	srand(1234);
	for (int i = 0; i < 48; i++) {
		float xr = ((float)rand() / (float)(RAND_MAX)) * 6.0f - 3.0f;
		float zr = ((float)rand() / (float)(RAND_MAX)) * 3.0f - 1.5f;
		OBJ_LIST.push_back(Sphere(Vec3(xr, -0.45, zr-2), 0.05));
	}

	fstream file;
	// file.open("../images/default.ppm", ios::out);
	// file.open("../images/reflection.ppm", ios::out);
	// file.open("../images/refraction.ppm", ios::out);
	// file.open("../images/default_shadow.ppm", ios::out);
	// file.open("../images/shadow.ppm", ios::out);
	file.open("../images/plane.ppm", ios::out);

	file << "P3\n" << WIDTH << " " << HEIGHT << "\n255\n";
	for (int j = HEIGHT - 1; j >= 0; j--) {
		for (int i = 0; i < WIDTH; i++) {
			Vec3 c(0, 0, 0);

			if(ANTI_ALIASING){
				for (int s = 0; s < SAMPLES_PER_PIXAL; s++) {
					float u = ((float)i + static_cast<float>(rand()) / RAND_MAX) / WIDTH;
					float v = ((float)j + static_cast<float>(rand()) / RAND_MAX) / HEIGHT;

					Vec3 target_point = LOWER_LEFT_CONER + u * HORIZONTAL + v * VERTICAL;
					Ray r(ORIGIN, target_point - ORIGIN);

					c += color(r, 5);
				}

				c /= float(SAMPLES_PER_PIXAL);
			}else{
				float ratio_h = float(i) / float(WIDTH);
				float ratio_v = float(j) / float(HEIGHT);
				Vec3 target_point = LOWER_LEFT_CONER + ratio_h * HORIZONTAL + ratio_v * VERTICAL;
	
				Ray r(ORIGIN, target_point - ORIGIN);
	
				// for each ray, see the final color it contributes to the screen
				Vec3 c = color(r, 5);
			}

			file << int(c[0] * 255) << " " << int(c[1] * 255) << " " << int(c[2] * 255) << "\n";
		}
	}

	return 0;
}
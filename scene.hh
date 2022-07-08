#ifndef SCENE_H
#define SCENE_H

#include <vector>
#include "math.hh"
#include "object.hh"

namespace scene {

	struct camera_t {
		math::vec3_t pos;
		double x_rot, y_rot;
	};

	struct point_light_t {
		math::vec3_t pos;
		math::vec3_t color;
		double intensity;
	};

	struct scene_t {
		camera_t camera;
		std::vector<object::sphere_t> spheres;
		std::vector<object::plane_t> planes;
		std::vector<point_light_t> point_lights;
		math::vec3_t ambient_light_color;
		double ambient_light_factor;
	};

	

	bool load_scene(scene_t & scene, const char* path);

};

#endif
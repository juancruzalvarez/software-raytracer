#ifndef RAYTRACER_H
#define RAYTRACER_H

#include "scene.hh"
namespace raytracer {

	

	struct config_t {
		scene::scene_t scene;
		int img_width, img_height;
		double FOV;
	};

	math::vec3_t calculate_pixel(const config_t &config, int pixel_x, int pixel_y);

};


#endif
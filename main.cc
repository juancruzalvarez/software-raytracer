// software-raytracer.cpp : Este archivo contiene la función "main". La ejecución del programa comienza y termina ahí.
//

#include <iostream>

#define STB_IMAGE_IMPLEMENTATION
#include "stb_image.h"

#define STBI_MSC_SECURE_CRT
#define __STDC_LIB_EXT1__
#define STB_IMAGE_WRITE_IMPLEMENTATION
#include "stb_image_write.h"

#include "scene.hh"
#include "raytracer.hh"
const char* scene_path = "scene.scn";
const char* image_out_path = "img.jpg";
const double FOV = 90.0;
const uint32_t img_width = 1200, img_height = 600;

int main() {
	scene::scene_t scene;
	if (!scene::load_scene(scene, scene_path)) {
		std::cout << "Unable to load scene. Exiting program.";
		return -1;
	}
	scene.camera = scene::camera_t{ math::vec3_t{0,0,0}, 0, 0 };
	scene.spheres.push_back({ {0,0,-5}, {0.3,0.5,1}, 0.51 });
	scene.spheres.push_back({ {2,1,-4}, {0.7,0.2,0.141}, 0.81 });
	scene.point_lights.push_back({ { 0,-5,0 }, {0.91,0.61,0.1},0.8 });
	scene.point_lights.push_back({ { 4,1,-3 }, {0.51,0.921,0.71},1.48 });

	raytracer::config_t config{scene, img_width, img_height, FOV};

	uint8_t* pixels = new uint8_t[img_width * img_height * 3];

	int index = 0;
	for (int j = img_height - 1; j >= 0; --j)
	{
		for (int i = 0; i < img_width; ++i)
		{
			math::vec3_t color = raytracer::calculate_pixel(config, i, j);
			int ir = int(255.99 * color.x);
			int ig = int(255.99 * color.y);
			int ib = int(255.99 * color.z);

			pixels[index++] = ir;
			pixels[index++] = ig;
			pixels[index++] = ib;
		}
	}


	stbi_write_jpg(image_out_path, img_width, img_height, 3, pixels, 100);
	

}


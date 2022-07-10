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
	//up is +y
	//forwards its -z
	//right is +x
	//x_rot + -> camera looks up
	object::material_t diffuse_mat{
		1,0,0,0,{1,0,0}
	};
	object::material_t diffuse_and_specular_mat{
		0.5,0.5,200,0,{0,1,0}
	};
	object::material_t very_specular_mat{
		0.2,0.8,2000.5,0,{0,1,1}
	};
	object::material_t reflective_mat{
		0.8,0,0,1,{1,0,1}
	};


	scene.camera = scene::camera_t{ math::vec3_t{0,3,0}, -0.3, 0 };
	scene.spheres.push_back({ {0,1,-5}, reflective_mat, 1 });
	scene.spheres.push_back({ {3,2,-7}, diffuse_mat, 1.5 });
	scene.spheres.push_back({ {-3,1,-4}, very_specular_mat, 0.7 });
	scene.spheres.push_back({ {4,3,-4}, diffuse_and_specular_mat, 1.7 });
	scene.planes.push_back({{0,0,0},{0,1,0},{0.8, 0.2, 1.2, 0, {0,0.78,1.0}}});
	scene.planes.push_back({{0,0,-15},{0,0,1},{0.8, 0.2, 1.2, 0, {0,0.780,1.0}}});
	scene.point_lights.push_back({ { -20,20, 20 }, {0.81,0.79,0.98},1.8 });
	scene.point_lights.push_back({ { 0,10, 10 }, {1,1,1},0.48 });
	scene.ambient_light_color = {1,1,1};
	scene.ambient_light_factor = 0.2;
	raytracer::config_t config{scene, img_width, img_height, FOV};

	uint8_t* pixels = new uint8_t[img_width * img_height * 3];

	int index = 0;
	for (int j = 0; j < img_height; ++j)
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


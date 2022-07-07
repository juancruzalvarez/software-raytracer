#include "raytracer.hh"
#include "object.hh"
#include <iostream>
namespace raytracer {

	namespace {

		math::ray_t get_ray(const config_t& config, int pixel_x, int pixel_y) {
			double aspect_ratio = config.img_width / config.img_height;
			double tan_res = tan(config.FOV / 2 * math::PI / 180.0);
			double pixel_pos_x = (2 * ((pixel_x + 0.5) / config.img_width) - 1) * tan_res * aspect_ratio;
			double pixel_pos_y = 1 - 2 * ((pixel_y + 0.5) / config.img_height) * tan_res;
			math::vec3_t ray_dir = { pixel_pos_x, pixel_pos_y, -1 };
			//rotate ray in the camera direction.
			double cos_b = cos(config.scene.camera.y_rot);
			double sin_b = sin(config.scene.camera.y_rot);
			double cos_y = cos(config.scene.camera.x_rot);
			double sin_y = sin(config.scene.camera.x_rot);
			ray_dir = {
				ray_dir.x * cos_b + ray_dir.y * sin_b * sin_y + ray_dir.z * sin_b * cos_y,
				ray_dir.y * cos_y - ray_dir.z * sin_y,
			   -ray_dir.x * sin_b + ray_dir.y * cos_b * sin_y + ray_dir.z * cos_b * cos_y
			};
			ray_dir = math::normalized(ray_dir);
			return math::ray_t{ config.scene.camera.pos, ray_dir };
		}

	};

	math::vec3_t calculate_pixel(const config_t& config, int pixel_x, int pixel_y) {
		math::ray_t ray = get_ray(config, pixel_x, pixel_y);
		//std::cout << "Ray_dir:" << ray.direction.x << " " << ray.direction.y << " " << ray.direction.z<<"\n";
		object::hit_info_t closest_hit{ false, 10000000000000, {0, 0, 0} };
		for (const auto& sphere : config.scene.spheres) {
			auto current_hit = object::sphere_intersect(ray, sphere);
			if (current_hit.hit && current_hit.t < closest_hit.t) {
				closest_hit = current_hit;
			}
		}

		if (!closest_hit.hit) {
			return closest_hit.obj_color; //bg color
		}

		math::vec3_t light_recived{0.0,0.0,0.0};
		math::vec3_t hit_point = ray.origin + ray.direction * closest_hit.t;
		for (const auto& light : config.scene.point_lights) {
			double diffuse = std::max(math::dot_product(closest_hit.normal, normalized(light.pos-hit_point)), 0.0);
			light_recived = light_recived + light.color * light.intensity * diffuse;
		}
		return math::clamp(closest_hit.obj_color * light_recived, 1.0);
	}

	

};
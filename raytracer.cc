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

		object::hit_info_t trace_ray(const scene::scene_t &scene, const math::ray_t &ray){
			object::hit_info_t closest_hit{ false, 10000000000000, {0, 0, 0} };
			for (const auto& sphere : scene.spheres) {
				auto current_hit = object::sphere_intersect(ray, sphere);
				if (current_hit.hit && current_hit.t < closest_hit.t) {
					closest_hit = current_hit;
				}
			}
			for (const auto& plane : scene.planes) {
				auto current_hit = object::plane_intersect(ray, plane);
				if (current_hit.hit && current_hit.t < closest_hit.t) {
					closest_hit = current_hit;
				}
			}
			return closest_hit;
		}

		math::vec3_t trace(const scene::scene_t& scene, math::ray_t ray, int depth) {
			object::hit_info_t closest_hit = trace_ray(scene, ray);
			if (!closest_hit.hit) {
				return { 0.0, 0.0, 0.0 };	//bg color
			}
			math::vec3_t light_recived = scene.ambient_light_color * scene.ambient_light_factor;
			math::vec3_t reflection = {0,0,0};
			math::vec3_t hit_point = ray.origin + ray.direction * closest_hit.t;
			for (const auto& light : scene.point_lights) {
				math::vec3_t dir_to_light = math::normalized(light.pos - hit_point);
				math::ray_t shadow_ray{ hit_point + closest_hit.normal * math::EPSILON, dir_to_light };
				bool visible = !trace_ray(scene, shadow_ray).hit;
				if (visible) {

					math::vec3_t reflection_dir = ray.direction - closest_hit.normal*2*(math::dot(ray.direction, closest_hit.normal));
					double diffuse = std::max(math::dot(closest_hit.normal, dir_to_light), 0.0);
					double specular = std::max(math::dot(ray.direction, reflection_dir), 0.0);
					specular = pow(specular, closest_hit.material.specular_power);
					light_recived += light.color * light.intensity * diffuse * closest_hit.material.difuse_factor;
					light_recived += light.color * light.intensity * specular * closest_hit.material.specular_factor;
					if (closest_hit.material.reflective_factor > 0 && depth < MAX_RECURSION_DEPTH) {
						reflection = trace(scene, math::ray_t{hit_point + closest_hit.normal * math::EPSILON, reflection_dir }, depth+1);
					}
				}
			}
			return math::clamp(reflection*closest_hit.material.reflective_factor +(closest_hit.material.albedo_color * light_recived), 1.0);
		}


	};

	math::vec3_t calculate_pixel(const config_t& config, int pixel_x, int pixel_y) {
		math::ray_t ray = get_ray(config, pixel_x, pixel_y);
		return trace(config.scene, ray, 0);
	}

	

};
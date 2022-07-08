#ifndef OBJECT_H
#define OBJECT_H

#include "math.hh"


namespace object {

	struct material_t {
		double difuse_factor;
		double specular_factor;
		double specular_power;
		double reflective_factor;
		math::vec3_t albedo_color;
	};
	struct hit_info_t {
		bool hit;
		double t;
		material_t material;
		math::vec3_t normal;
	};

	struct sphere_t {
		math::vec3_t pos;
		material_t material;
		double radius;
	};

	struct plane_t {
		math::vec3_t pos;
		math::vec3_t normal;
		material_t material;
	};

	hit_info_t sphere_intersect(const math::ray_t& ray, const sphere_t& sphere);
	hit_info_t plane_intersect(const math::ray_t& ray, const plane_t& plane);
};

#endif
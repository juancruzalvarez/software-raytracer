#ifndef OBJECT_H
#define OBJECT_H

#include "math.hh"


namespace object {

	struct hit_info_t {
		bool hit;
		double t;
		math::vec3_t obj_color;
		math::vec3_t normal;
	};

	struct sphere_t {
		math::vec3_t pos;
		math::vec3_t color;
		double radius;
	};

	struct plane_t {
		math::vec3_t pos;
		math::vec3_t normal;
	};

	hit_info_t sphere_intersect(const math::ray_t& ray, const sphere_t& sphere);
	hit_info_t plane_intersect(const math::ray_t& ray, const plane_t& plane);
};

#endif
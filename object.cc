#include "object.hh"
#include <memory>

namespace object {

	hit_info_t sphere_intersect(const math::ray_t& ray, const sphere_t& sphere) {

		hit_info_t hit_info;

		math::vec3_t side_distances = ray.origin - sphere.pos;
		double B = 2 * math::dot_product(side_distances, ray.direction);
		double C = math::dot_product(side_distances, side_distances) - sphere.radius * sphere.radius;
		double disc = B * B - 4 * C;
		double t0, t1;
		if (disc < 0) {
			return hit_info_t{ false, -1, math::vec3_t{0, 0, 0} };
		}
		else {

			t0 = -B + sqrt(disc);
			t1 = -B - sqrt(disc);
			if (t0 > t1) {
				std::swap(t0, t1);
			}
			if (t0 < 0) {
				t0 = t1;
				if (t0 < 0) {
					return hit_info_t{ false, -1, math::vec3_t{0, 0, 0} };
				}
			}
			hit_info.hit = true;
			hit_info.t = t0 / 2.0;
		}
		hit_info.obj_color = sphere.color;
		math::vec3_t hit_point = ray.origin + ray.direction * hit_info.t;
		hit_info.normal = math::normalized(hit_point - sphere.pos);
		return hit_info;
	};

	hit_info_t plane_intersect_fn(const math::ray_t& ray, const plane_t& plane) {
		return { false, 100000, {0, 0, 0} };
	};

};
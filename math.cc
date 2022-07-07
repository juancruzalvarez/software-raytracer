#include "math.hh"
#include <utility>

namespace math {

	double lenght(const vec3_t& v) {
		return sqrt(v.x * v.x + v.y * v.y + v.z * v.z);
	}

	vec3_t normalized(const vec3_t& v) {
		return v / lenght(v);
	}

	vec3_t clamp(const vec3_t& v, double max_val) {
		return { std::min(v.x, max_val), std::min(v.y, max_val), std::min(v.z, max_val) };
	}

	double distance(const vec3_t& a, const vec3_t& b) {
		return fabs(lenght(b - a));
	}

	double dot_product(const vec3_t& a, const vec3_t& b) {
		return a.x * b.x + a.y * b.y + a.z * b.z;
	}

};
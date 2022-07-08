#ifndef MATH_H
#define MATH_H
#include <math.h>
namespace math {

	const double PI = 3.14159265359;
	const double EPSILON = 1e-5;

	struct vec3_t {
		double x, y, z;

		vec3_t operator+(const vec3_t &b) const{
			return vec3_t{x+b.x, y+b.y, z+b.z};
		}

		vec3_t& operator+=(const vec3_t& b) {
			(*this).x += b.x;
			(*this).y += b.y;
			(*this).z += b.z;
        	return *this; 
    	}	

		vec3_t operator-(const vec3_t &b) const{
			return vec3_t{x-b.x, y-b.y, z-b.z};
		}

		vec3_t operator-() const{
			return vec3_t{-x, -y, -z};
		};

		vec3_t operator*(const vec3_t &b) const {
			return vec3_t{ x * b.x, y * b.y, z * b.z };
		}

		vec3_t operator*(double b) const{
			return vec3_t{x*b, y*b, z*b};
		}

		
		vec3_t operator/(double b) const{
			return vec3_t{ x / b, y / b, z / b };
		}


		bool operator==(const vec3_t &b) const{
			return x == b.x && y == b.y && z == b.z;
		}
	};

	
	double lenght(const vec3_t& v);
	vec3_t normalized(const vec3_t& v);
	vec3_t clamp(const vec3_t &v, double max_val);
	double distance(const vec3_t& a, const vec3_t& b);
	double dot(const vec3_t& a, const vec3_t& b);

	struct ray_t {
		vec3_t origin;
		vec3_t direction;
	};



};

#endif
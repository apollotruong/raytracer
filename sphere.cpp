#include "sphere.h"
#include "ray.h"

#include <cmath>
// Determine if the ray intersects with the sphere
Hit Sphere::Intersection(const Ray& ray, int part) const
{
		double a = dot(ray.direction, ray.direction);
		double b = 2 * dot( (ray.endpoint - this->center), ray.direction);
		double c = dot( (ray.endpoint - this->center), (ray.endpoint - this->center));
	    c -= this->radius * this->radius;
		double discriminant = (b * b) - (4 * a * c);

		if(discriminant < 0){
			return {NULL, 0.0, 0};
		}

		b = (-1) * b;
		double soln = b + pow(discriminant, 0.5);
		soln /= 2*a;
		if(soln >= small_t){
				return {this, soln, part};
		}
		else if(soln < small_t){
				return {this, soln, part};
		}
		else{
				return {NULL,0,0};
		}
}

vec3 Sphere::Normal(const vec3& point, int part) const
{
    vec3 normal;
    // TODO; // compute the normal direction
    // added checkpoint 1
    normal = (point - center).normalized();
    return normal;
}

Box Sphere::Bounding_Box(int part) const
{
    Box box;
    TODO; // calculate bounding box
    return box;
}

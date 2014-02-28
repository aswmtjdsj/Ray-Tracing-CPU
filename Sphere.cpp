#include "Sphere.h"
#include "Constants.h"
#include "Vector.h"
#include "Ray.h"
#include "ShadeRec.h"

const RTdouble Sphere::kEpsilon = RT_EPSILON;

Sphere::Sphere(): GeometryObject(), c(), r(RT_ZERO) {
}

Sphere::Sphere(const Point &point, const RTdouble &radius): GeometryObject(), c(point), r(radius) {
}

void Sphere::setCenter(const RTdouble &cor) {
	c = Point(cor);
}

void Sphere::setCenter(const Point &p) {
	c = p;
}

void Sphere::setRadius(const RTdouble &len) {
	r = (RTdouble)len;
}

bool Sphere::hit(const Ray &ray, double &min_t, ShadeRec &sr) const {
	// (p - c) * (p - c) - r^2 = 0
	// p = o + t * d
	// (d * d)t^2 + [2(o-c)*d]t + (o-c)(o-c) - r^2 = 0
	// A = d * d
	// B = 2 * (o-c) * d
	// C = (o-c)^2 - r^2
	// delta = B^2 - 4*A*C
	// t_1 = (-B + sqrt(delta)) / (2 * a)
	// t_2 = (-B - sqrt(delta)) / (2 * a)

	//ray.print("ray");
	//(*this).print("sphere");

	RTdouble t;
	Vector co = ray.o - c;
	RTdouble A = ray.d * ray.d,
		B = (RTdouble)2. * co * ray.d,
		C = co * co - r * r,
		delta = B * B - (RTdouble)4. * A * C;
	
	if( delta < RT_ZERO) {
		return false;
	}
	else {
		RTdouble root = sqrt(delta);

		t = (-B - root) / ((RTdouble)2. * A); // smaller solution
		if( t > kEpsilon) { // ray hits the sphere in [0,+inf)
			min_t = t;
			sr.normal = (co + t * ray.d) / r;
			sr.local_hit_point = ray.o + t * ray.d;

			return true;
		}
		
		t = (-B + root) / ((RTdouble)2. * A); // greater solution
		// obvious farther than the smaller one
		if( t > kEpsilon) { // ray hits the sphere in [0,+inf)
			min_t = t;
			sr.normal = (co + t * ray.d) / r;
			sr.local_hit_point = ray.o + t * ray.d;
			return true;
		}
	}

	return false; // both t < 0
}

bool Sphere::shadowHit(const Ray &ray, RTdouble &min_t) const {
	if(!shadows) {
		return false;
	}

	RTdouble t;
	Vector co = ray.o - c;
	RTdouble A = ray.d * ray.d,
		B = (RTdouble)2. * co * ray.d,
		C = co * co - r * r,
		delta = B * B - (RTdouble)4. * A * C;
	
	if( delta < RT_ZERO) {
		return false;
	}
	else {
		RTdouble root = sqrt(delta);

		t = (-B - root) / ((RTdouble)2. * A); // smaller solution
		if( t > kEpsilon) { // ray hits the sphere in [0,+inf)
			min_t = t;
			return true;
		}
		
		t = (-B + root) / ((RTdouble)2. * A); // greater solution
		// obvious farther than the smaller one
		if( t > kEpsilon) { // ray hits the sphere in [0,+inf)
			min_t = t;
			return true;
		}
	}

	return false;
}

void Sphere::print(const string &prompt) const {
	printf("Info of Sphere %s>\n", prompt.c_str());
	c.print("center of Sphere " + prompt);
	printf("radius of Sphere %s is %.2lf\n", prompt.c_str(), r);
}

RGBColor Sphere::getColor() const {
	return color;
}

void Sphere::setColor(const RGBColor &t_color) {
	color = t_color;
}

Material * Sphere::getMaterial() const {
	return material;
}

void Sphere::setMaterial(Material * mat) {
	material = mat;
}

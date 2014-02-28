#include "Vector.h"
#include "Plane.h"

const RTdouble Plane::kEpsilon = RT_EPSILON;

Plane::Plane(): GeometryObject(), p(), n() {
}

Plane::Plane(const Point &point, const Normal &normal): GeometryObject(), p(point), n(normal) {
}

bool Plane::hit(const Ray &ray, double &min_t, ShadeRec &sr) const {

	// ( p - a ) * n = 0
	// p = o + t * d

	double t = (p - ray.o) * n / (ray.d * n);

	if(t > kEpsilon) {
		min_t = t;
		sr.normal = n;
		sr.local_hit_point = ray.o + t * ray.d;

		return true;
	}
	else {
		return false;
	}
}

bool Plane::shadowHit(const Ray &ray, RTdouble &min_t) const {
	if(!shadows) {
		return false;
	}

	RTdouble t = (p - ray.o) * n / (ray.d * n);
	if( t > kEpsilon) {
		min_t = t;
		return true;
	}
	else {
		return false;
	}
}

void Plane::print(const string &prompt) const {
	printf("Info of Plane %s>\n", prompt.c_str());
	p.print("point on Plane " + prompt);
	n.print("normal of Plane " + prompt);
}

RGBColor Plane::getColor() const {
	return color;
}

void Plane::setColor(const RGBColor &t_color) {
	color = t_color;
}

Material * Plane::getMaterial() const {
	return material;
}

void Plane::setMaterial(Material * mat) {
	material = mat;
}

#include "Ray.h"

// constructor
Ray::Ray(): o(), d() {
}

Ray::Ray(const Point &origin, const Vector &dir):
	o(origin), d(dir) {
}

// Copy Constructor
Ray::Ray(const Ray &ray){
	*this=ray;
}

// destructor
Ray::~Ray() {
}

// = operator
Ray & Ray::operator =(const Ray &ray) {
	o = ray.o;
	d = ray.d;
	return *this;
}

void Ray::print(const string &prompt) const {
	printf("Details of %s>\n", prompt.c_str());
	o.print(prompt+" origin");
	d.print(prompt+" direction");
}
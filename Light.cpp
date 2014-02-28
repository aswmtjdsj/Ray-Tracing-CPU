#include "Constants.h"
#include "ShadeRec.h"
#include "Light.h"
#include "World.h"

Light::Light():shadows(true) {
}

bool Light::castShadows() const {
	return shadows;
}

// Ambient
Ambient::Ambient():
	Light(),
	ls(RT_ONE),
	color(COLOR_WHITE){ 
	}

Vector Ambient::getDirection(ShadeRec &sr) {
	return Vector(RT_ZERO);
}

RGBColor Ambient::L(ShadeRec &sr) {
	return ls * color;
}

void Ambient::scaleRadience(const RTdouble &_ls) {
	ls = _ls;
}

bool Ambient::inShadow(const Ray &ray, const ShadeRec &sr) const {
	return false; // fake
}

// Point Light
PointLight::PointLight(): 
	Light(),
	ls(RT_ONE),
	color(COLOR_WHITE),
	location(Point(RT_ZERO)){ 
	}

Vector PointLight::getDirection(ShadeRec &sr) {

	return (location - sr.hit_point).unit();
}

RGBColor PointLight::L(ShadeRec &sr) {
	//return ls * color;
	RTdouble r = location.distance(sr.hit_point);
	if( r < 1) {
		return COLOR_BLACK;
	}
	return ls * color / (r * r * coeff);
}

Point PointLight::getLocation() const {
	return location;
}

void PointLight::setLocation(const Point &p) {
	location = p;
}

void PointLight::setCoeff(const RTdouble &c) {
	coeff = c;
}

void PointLight::setColor(const RGBColor &c) {
	color = c;
}

void PointLight::scaleRadience(const RTdouble &_ls) {
	ls = _ls;
}

// shadow ray
bool PointLight::inShadow(const Ray &ray, const ShadeRec &sr) const {
	RTdouble t;
	int numObjects = sr.w.objects.size();
	RTdouble d = location.distance(ray.o);

	for(int j = 0; j < numObjects; j++) {
		if(sr.w.objects[j]->shadowHit(ray, t) && t < d) {
			return true;
		}
	}
	return false;
}

// Directional
Directional::Directional():
	Light(),
	ls(RT_ONE),
	color(COLOR_WHITE),
	dir(Vector(RT_ZERO)){ 
	}

Vector Directional::getDirection(ShadeRec &sr) {
	return dir;
}

RGBColor Directional::L(ShadeRec &sr) {
	return ls * color;
}

void Directional::setDir(const Vector &d) {
	dir = d;
}

bool Directional::inShadow(const Ray &ray, const ShadeRec &sr) const {
	return false; // fake
}

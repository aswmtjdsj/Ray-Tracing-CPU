#include "AreaLighting.h"
#include "Constants.h"
#include "ShadeRec.h"
#include "World.h"

AreaLighting::AreaLighting():Tracer() {
}

AreaLighting::AreaLighting(World *ptr):Tracer(ptr) {
}

RGBColor AreaLighting::traceRay(const Ray &ray) const {
	return COLOR_BLACK;
}

RGBColor AreaLighting::traceRay(const Ray &ray, const int &depth) const {
	ShadeRec sr(world_ptr->hitOjbects(ray));

	if( sr.hit_an_object) {
		sr.ray = ray;

		return sr.material_ptr->areaLightShade(sr);
	}
	else {
		return world_ptr->bg_color;
	}
}

RGBColor AreaLighting::traceRay(const Ray &ray, RTdouble &min_t, const int &depth) const {
	ShadeRec sr(world_ptr->hitOjbects(ray));

	if( sr.hit_an_object) {
		sr.ray = ray;
		return sr.material_ptr->areaLightShade(sr);
	}
	else {
		return world_ptr->bg_color;
	}
}
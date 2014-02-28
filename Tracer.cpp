#include "Tracer.h"
#include "Constants.h"
#include "ShadeRec.h"
#include "World.h"

Tracer::Tracer():world_ptr(NULL) {
}

Tracer::Tracer(World * w_ptr):world_ptr(w_ptr) {
}

RGBColor Tracer::traceRay(const Ray &ray) const {
	return COLOR_BLACK;
}

RGBColor Tracer::traceRay(const Ray &ray, const int &depth) const {
	ShadeRec sr(world_ptr->hitOjbects(ray));

	if( sr.hit_an_object) {
		sr.ray = ray;
		return sr.material_ptr->shade(sr);
	}
	else {
		return world_ptr->bg_color;
	}
}

RGBColor Tracer::traceRay(const Ray &ray, RTdouble &min_t, const int &depth) const {
	ShadeRec sr(world_ptr->hitOjbects(ray));

	if( sr.hit_an_object) {
		sr.ray = ray;
		return sr.material_ptr->shade(sr);
	}
	else {
		return world_ptr->bg_color;
	}
}
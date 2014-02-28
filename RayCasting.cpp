#include "RayCasting.h"
#include "Constants.h"
#include "ShadeRec.h"
#include "World.h"

RayCasting::RayCasting():Tracer() {
}

RayCasting::RayCasting(World *ptr):Tracer(ptr) {
}

RGBColor RayCasting::traceRay(const Ray &ray) const {
	return COLOR_BLACK;
}

RGBColor RayCasting::traceRay(const Ray &ray, const int &depth) const {
	ShadeRec sr(world_ptr->hitOjbects(ray));

	if( sr.hit_an_object) {
		sr.ray = ray;

		return sr.material_ptr->shade(sr);
	}
	else {
		return world_ptr->bg_color;
	}
}

RGBColor RayCasting::traceRay(const Ray &ray, RTdouble &min_t, const int &depth) const {
	ShadeRec sr(world_ptr->hitOjbects(ray));

	if( sr.hit_an_object) {
		sr.ray = ray;
		return sr.material_ptr->shade(sr);
	}
	else {
		return world_ptr->bg_color;
	}
}
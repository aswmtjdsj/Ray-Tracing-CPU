#include "SingleSphere.h"
#include "Constants.h"
#include "ShadeRec.h"
#include "World.h"

SingleSphere::SingleSphere():Tracer() {
}

SingleSphere::SingleSphere(World * w_ptr):Tracer(w_ptr) {
}

RGBColor SingleSphere::traceRay(const Ray &ray) const {
	ShadeRec sr(*world_ptr); // not used here
	RTdouble t; // not used here

	if(world_ptr->sphere.hit(ray, t, sr)) {
		return COLOR_RED;
	}
	else {
		return COLOR_WHITE;
	}
}
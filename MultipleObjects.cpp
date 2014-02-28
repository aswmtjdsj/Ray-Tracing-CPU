#include "MultipleObjects.h"
#include "Constants.h"
#include "ShadeRec.h"
#include "World.h"

MultipleObjects::MultipleObjects():Tracer() {
}

MultipleObjects::MultipleObjects(World * w_ptr):Tracer(w_ptr) {
}

RGBColor MultipleObjects::traceRay(const Ray &ray) const {
	ShadeRec sr(world_ptr->hitBareBonesOjbects(ray)); 

	if( sr.hit_an_object) {
		return sr.color;
	}
	else {
		return world_ptr->bg_color;
	}
}
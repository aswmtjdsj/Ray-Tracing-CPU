#include "ShadeRec.h"
#include "Constants.h"

ShadeRec::ShadeRec(World &wr)
	: hit_an_object(false),
	material_ptr(NULL),
	hit_point(), local_hit_point(), normal(),
	//color(COLOR_BLACK),
	ray(), depth(0), dir(),
	w(wr),
	t(RT_INFINITY){

}

ShadeRec::ShadeRec(const ShadeRec &sr):
	hit_an_object(sr.hit_an_object),
	material_ptr(sr.material_ptr),
	hit_point(sr.hit_point), local_hit_point(sr.local_hit_point),
	normal(sr.normal),
	ray(sr.ray), depth(sr.depth), dir(sr.dir),
	//color(sr.color),
	w(sr.w),
	t(RT_INFINITY){ // i don't know
}

ShadeRec::~ShadeRec() {
}

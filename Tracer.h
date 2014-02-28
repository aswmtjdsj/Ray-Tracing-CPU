#ifndef TRACER_H
#define TRACER_H

#include "RGBColor.h"
#include "Ray.h"

class World; // fake

class Tracer {
public:
	Tracer();
	Tracer(World *);

	virtual RGBColor traceRay(const Ray &) const;
	virtual RGBColor traceRay(const Ray &, const int &) const;
	virtual RGBColor traceRay(const Ray &, RTdouble &, const int &) const;

protected:
	World * world_ptr;
};

#endif
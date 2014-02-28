#ifndef AREA_LIGHTING_H
#define AREA_LIGHTING_H

#include "common.h"
#include "Tracer.h"

class AreaLighting: public Tracer {
public:
	AreaLighting();
	AreaLighting(World *);

	virtual RGBColor traceRay(const Ray &) const;
	virtual RGBColor traceRay(const Ray &, const int &) const;
	virtual RGBColor traceRay(const Ray &, RTdouble &, const int &) const;
};

#endif
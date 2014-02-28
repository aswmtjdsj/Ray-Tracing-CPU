#ifndef RAYCASTING_H
#define RAYCASTING_H

// define objects
// define materials for objects
// define define light sources
// define a window whose surface of pixels --- view plane

// for each pixel
//		shoot a ray towards objects from the center of the pixel
//		compute the nearest hit point of the ray with objects (if any)
//		
//		if ray hits an object
//			use the material of the object and the lights to compute the color of the pixel
//		else
//			set the color of pixel to black 

#include "Tracer.h"

class RayCasting: public Tracer {
public:
	RayCasting();
	RayCasting(World *);

	virtual RGBColor traceRay(const Ray &) const;
	virtual RGBColor traceRay(const Ray &, const int &) const;
	virtual RGBColor traceRay(const Ray &, RTdouble &, const int &) const;
};

#endif
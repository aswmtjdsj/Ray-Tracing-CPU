#ifndef MULTIPLEOBJECTS_H 
#define MULTIPLEOBJECTS_H 

#include "Tracer.h"

class MultipleObjects: public Tracer {
public:
	MultipleObjects();
	MultipleObjects(World *);

	RGBColor traceRay(const Ray &) const;
};

#endif
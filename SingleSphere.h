#ifndef SINGLESPHERE_H
#define SINGLESPHERE_H

#include "Tracer.h"

class SingleSphere: public Tracer {
public:
	SingleSphere();
	SingleSphere(World *);

	RGBColor traceRay(const Ray &) const;
};

#endif
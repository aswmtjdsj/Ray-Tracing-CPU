#ifndef BRDF_H
#define BRDF_H

#include "RGBColor.h"
#include "Vector.h"
#include "ShadeRec.h"

class Sampler;
class BRDF {
public:
	virtual RGBColor f(const ShadeRec &, const Vector &, const Vector &) const = 0;
	virtual RGBColor fSample(const ShadeRec &, Vector &, const Vector &) const = 0;
	virtual RGBColor rho(const ShadeRec &, const Vector &) const = 0;

protected:
	Sampler * sampler_ptr;
};
#endif
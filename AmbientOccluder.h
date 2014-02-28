#ifndef AMBIENT_OCCLUDER_H
#define AMBIENT_OCCLUDER_H

#include "common.h"
#include "Light.h"

class Sampler;

class AmbientOccluder: public Light {
public:
	AmbientOccluder();

	void setSampler(Sampler *);
	void scaleRadience(const RTdouble &);
	void setMinAmount(const RTdouble &);
	void setColor(const RGBColor &);

	Sampler * getSamplerPtr();

	virtual Vector getDirection(ShadeRec &);
	virtual bool inShadow(const Ray &, const ShadeRec &) const;
	virtual RGBColor L(ShadeRec &);
	
protected:
	RTdouble ls;
	RGBColor color;

	Vector u, v, w;
	Sampler * sampler_ptr;
	RGBColor minAmount;
};

#endif
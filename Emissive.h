#ifndef EMISSIVE_H
#define EMISSIVE_H

#include "common.h"
#include "RGBColor.h"
#include "Material.h"

class Emissive: public Material {
public:
	void scaleRaiance(const RTdouble &);
	void set_ce(const RGBColor &);

	virtual RGBColor get_Le(ShadeRec &) const;
	virtual RGBColor shade(ShadeRec &);
	virtual RGBColor areaLightShade(ShadeRec &);

private:
	RTdouble ls;
	RGBColor ce;
};

#endif
#ifndef MATERIAL_H
#define MATERIAL_H

#include "ShadeRec.h"

class Material {
public:
	virtual RGBColor shade(ShadeRec &);
	virtual RGBColor areaLightShade(ShadeRec &);
	virtual RGBColor shadePath(ShadeRec &);
	virtual RGBColor get_Le(ShadeRec &) const;

};

#endif

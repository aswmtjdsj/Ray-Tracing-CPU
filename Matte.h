#ifndef MATTE_H
#define MATTE_H

#include "Material.h"
#include "Lambertian.h"

class Matte: public Material {

public:
	Matte();
	~Matte();
	void set_ka(const RTdouble &);
	void set_kd(const RTdouble &);
	void set_cd(const RGBColor &);

	virtual RGBColor shade(ShadeRec &);
	virtual RGBColor areaLightShade(ShadeRec &);

private:
	Lambertian * ambientBRDF;
	Lambertian * diffuseBRDF;
};

#endif

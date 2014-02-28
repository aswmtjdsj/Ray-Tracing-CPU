#ifndef PHONG_H
#define PHONG_H

#include "Material.h"
#include "Lambertian.h"
#include "GlossySpecular.h"

class Phong: public Material {

public:
	Phong();
	~Phong();

	void set_ka(const RTdouble &);
	void set_kd(const RTdouble &);
	void set_ks(const RTdouble &);
	void set_exp(const RTdouble &);
	void set_cd(const RGBColor &);
	void set_cs(const RGBColor &);

	virtual RGBColor shade(ShadeRec &);

private:
	Lambertian * ambientBRDF;
	Lambertian * diffuseBRDF;
	GlossySpecular * specularBRDF;
};

#endif

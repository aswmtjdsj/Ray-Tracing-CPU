#ifndef LAMBERTIAN_H 
#define LAMBERTIAN_H 

#include "BRDF.h"

class Lambertian: public BRDF{
public:
	virtual RGBColor f(const ShadeRec &, const Vector &, const Vector &) const;
	virtual RGBColor fSample(const ShadeRec &, Vector &, const Vector &) const;
	virtual RGBColor rho(const ShadeRec &, const Vector &) const;

	void set_kd(const RTdouble &);
	void set_cd(const RGBColor &);

private:
	RTdouble kd;
	RGBColor cd; // rho = kd * cd;

};
#endif
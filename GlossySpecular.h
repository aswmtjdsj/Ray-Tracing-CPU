#ifndef GLOSSYSPECULAR_H 
#define GLOSSYSPECULAR_H 

#include "BRDF.h"

class GlossySpecular: public BRDF{
public:
	virtual RGBColor f(const ShadeRec &, const Vector &, const Vector &) const;
	virtual RGBColor fSample(const ShadeRec &, Vector &, const Vector &) const;
	virtual RGBColor rho(const ShadeRec &, const Vector &) const;

	void set_ks(const RTdouble &);
	void set_exp(const RTdouble &);
	void set_cs(const RGBColor &);

private:
	RTdouble ks;
	RTdouble exp; // e 
	RGBColor cs; // color specular

};
#endif

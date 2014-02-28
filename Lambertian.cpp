#include "Lambertian.h"
#include "Constants.h"

RGBColor Lambertian::f(const ShadeRec &sr, const Vector &wi, const Vector &wo) const {
	return kd * cd * RT_INVPI;
}

RGBColor Lambertian::fSample(const ShadeRec &sr, Vector &wi, const Vector &wo) const {
	return kd * cd * RT_INVPI;
}

RGBColor Lambertian::rho(const ShadeRec &sr, const Vector &wo) const {
	return kd * cd;
}

void Lambertian::set_kd(const RTdouble &_kd) {
	kd = _kd;
}

void Lambertian::set_cd(const RGBColor &_cd) {
	cd = _cd;
}
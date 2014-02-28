#include "GlossySpecular.h"
#include "Constants.h"

RGBColor GlossySpecular::f(const ShadeRec &sr, const Vector &wi, const Vector &wo) const {
	// wo = a * wi + b * normal, wo is reflected ray, wi is incident ray and a, b are coeffs
	// so wo * normal = a * wi * normal + b * normal * normal
	// which means (1-a)wi * normal = b, cauz wi * normal == wo * normal
	// and wo * normal_prep = a * wi * normal_prep + b * normal * normal_prep
	// so wo * normal_prep = a * wi * normal_prep + 0, and the two dot products are value-equal, symbol composite
	// so a = -1
	// wo = -wi + 2 * (wi * normal) * normal

	RGBColor L;
	RTdouble n_dot_wi = sr.normal * wi;
	Vector r(-wi + 2.0 * sr.normal * n_dot_wi);
	RTdouble r_dot_wo = r * wo;

	if(r_dot_wo > RT_ZERO) {
		L = ks * pow(r_dot_wo, exp);
	}

	return L;
}

RGBColor GlossySpecular::fSample(const ShadeRec &sr, Vector &wi, const Vector &wo) const {
	return f(sr, wi, wo); // temp 
}

RGBColor GlossySpecular::rho(const ShadeRec &sr, const Vector &wo) const {
	return COLOR_BLACK;
}

void GlossySpecular::set_exp(const RTdouble &_exp) {
	exp = _exp;
}

void GlossySpecular::set_ks(const RTdouble &_ks) {
	ks = _ks;
}

void GlossySpecular::set_cs(const RGBColor &_cs) {
	cs = _cs;
}

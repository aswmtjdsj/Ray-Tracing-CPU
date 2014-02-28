#include "Constants.h"
#include "Matte.h"
#include "Light.h"
#include "ShadeRec.h"
#include "World.h"

Matte::Matte():
	Material(),
	ambientBRDF(new Lambertian),
	diffuseBRDF(new Lambertian){
}

Matte::~Matte() {
	if(ambientBRDF != NULL) {
		delete ambientBRDF;
		ambientBRDF = NULL;
	}
	if(diffuseBRDF != NULL) {
		delete diffuseBRDF;
		diffuseBRDF = NULL;
	}
}

void Matte::set_ka(const RTdouble &ka) {
	ambientBRDF->set_kd(ka);
}

void Matte::set_kd(const RTdouble &kd) {
	diffuseBRDF->set_kd(kd);
}

void Matte::set_cd(const RGBColor &cd) {
	ambientBRDF->set_cd(cd);
	diffuseBRDF->set_cd(cd);
}

RGBColor Matte::shade(ShadeRec &sr) {
	Vector wo = -sr.ray.d;

	RGBColor L = ambientBRDF->rho(sr, wo) * sr.w.ambient->L(sr);

	int num_lights = sr.w.lights.size();

	for(int j = 0; j < num_lights; j++) {
		Vector wi = sr.w.lights[j]->getDirection(sr);
		RTdouble n_dot_wi = sr.normal * wi;
		if(n_dot_wi > RT_ZERO) {
			L += diffuseBRDF->f(sr, wo, wi) * sr.w.lights[j]->L(sr) * n_dot_wi;
		}
	}

	return L;
}

RGBColor Matte::areaLightShade(ShadeRec &sr) {
	Vector wo = -sr.ray.d;

	RGBColor L = ambientBRDF->rho(sr, wo) * sr.w.ambient->L(sr);

	int num_lights = sr.w.lights.size();

	for(int j = 0; j < num_lights; j++) {
		Vector wi = sr.w.lights[j]->getDirection(sr);
		RTdouble n_dot_wi = sr.normal * wi;
		if(n_dot_wi > RT_ZERO) {
			bool inShadow = false;
			if(sr.w.lights[j]->castShadows()) {
				Ray shadowRay(sr.hit_point, wi);
				inShadow = sr.w.lights[j]->inShadow(shadowRay, sr);
			}
			if(inShadow) {
				L += diffuseBRDF->f(sr, wo, wi) * sr.w.lights[j]->L(sr) * n_dot_wi; // G? pdf?
			}
		}
	}

	return L;
}
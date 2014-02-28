#include "Constants.h"
#include "Phong.h"
#include "ShadeRec.h"
#include "World.h"

Phong::Phong(): ambientBRDF(new Lambertian), diffuseBRDF(new Lambertian), specularBRDF(new GlossySpecular) {
}

Phong::~Phong() {
	if(ambientBRDF != NULL) {
		delete ambientBRDF;
		ambientBRDF = NULL;
	}
	if(diffuseBRDF != NULL) {
		delete diffuseBRDF;
		diffuseBRDF = NULL;
	}
	if(specularBRDF != NULL) {
		delete specularBRDF;
		specularBRDF = NULL;
	}
}

void Phong::set_ka(const RTdouble &ka) {
	ambientBRDF->set_kd(ka);
}

void Phong::set_kd(const RTdouble &kd) {
	diffuseBRDF->set_kd(kd);
}

void Phong::set_ks(const RTdouble &ks) {
	specularBRDF->set_ks(ks);
}

void Phong::set_exp(const RTdouble &exp) {
	specularBRDF->set_exp(exp);
}

void Phong::set_cd(const RGBColor &cd) {
	ambientBRDF->set_cd(cd);
	diffuseBRDF->set_cd(cd);
}

void Phong::set_cs(const RGBColor &cs) {
	specularBRDF->set_cs(cs);
}

RGBColor Phong::shade(ShadeRec &sr) {
	// add shadow ray
	Vector wo = -sr.ray.d;

	RGBColor L = ambientBRDF->rho(sr, wo) * sr.w.ambient->L(sr);

	int num_lights = sr.w.lights.size();
	for(int j = 0; j < num_lights; j++) {
		Vector wi = sr.w.lights[j]->getDirection(sr);
		RTdouble n_dot_wi = sr.normal * wi;

		// we must make sure the angle between normal and wi is less than pi / 2
		if( n_dot_wi < RT_ZERO) {
			n_dot_wi = (-sr.normal) * wi;
		}

		if(n_dot_wi > RT_ZERO) {
			bool inShadow = false;

			if(sr.w.lights[j]->castShadows()) {
				Ray shadowRay(sr.hit_point, wi);
				inShadow = sr.w.lights[j]->inShadow(shadowRay, sr);
			}

			if(!inShadow) {
				L += (diffuseBRDF->f(sr, wo, wi) + specularBRDF->f(sr, wo, wi)) * sr.w.lights[j]->L(sr) * n_dot_wi;
			}
		}
	}
	return L;
}

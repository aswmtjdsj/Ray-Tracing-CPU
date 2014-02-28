#include "Plastic.h"

Plastic::Plastic():
	ambientBRDF(NULL),
	diffuseBRDF(NULL),
	specularBRDF(NULL) {
	}

Plastic::~Plastic() {
}

void Plastic::setAmbientBRDF(BRDF * ambient) {
	ambientBRDF = ambient;
}

void Plastic::setDiffuseBRDF(BRDF * diffuse) {
	diffuseBRDF = diffuse;
}

void Plastic::setSpecularBRDF(BRDF * specular) {
	specularBRDF = specular;
}

RGBColor Plastic::shade(ShadeRec &sr) {
	Vector wo = -sr.ray.d;
	RGBColor L = COLOR_BLACK;

	if(ambientBRDF != NULL) {
		L += ambientBRDF->rho(sr, wo) * sr.w.ambient->L(sr);
	}

	int num_lights = sr.w.lights.size();
	for(int j = 0; j < num_lights; j++) {
		Vector wi = sr.w.lights[j]->getDirection(sr);
		RTdouble n_dot_wi = sr.normal * wi;
		if(n_dot_wi > RT_ZERO) {
			if(diffuseBRDF != NULL) {
				L += diffuseBRDF->f(sr, wo, wi);
			}

			if(specularBRDF != NULL) {
				L += specularBRDF->f(sr, wo, wi) * sr.w.lights[j]->L(sr) * n_dot_wi;
			}
		}
	}
	return L;
}

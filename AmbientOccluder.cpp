#include "AmbientOccluder.h"
#include "Constants.h"

#include "Sampler.h"

#include "ShadeRec.h"
#include "Ray.h"

#include "World.h"

AmbientOccluder::AmbientOccluder(): sampler_ptr(NULL), 
	color(COLOR_WHITE),
	minAmount(COLOR_BLACK){
}

void AmbientOccluder::setSampler(Sampler * ptr) {
	if(sampler_ptr) {
		delete sampler_ptr;
		sampler_ptr = NULL;
	}

	sampler_ptr = ptr;
}

void AmbientOccluder::scaleRadience(const RTdouble &_ls) {
	ls = _ls;
}

void AmbientOccluder::setMinAmount(const RTdouble &m_a) {
	minAmount = m_a;
}

void AmbientOccluder::setColor(const RGBColor &c) {
	color = c;
}

Sampler * AmbientOccluder::getSamplerPtr() { 
	return sampler_ptr;
}

Vector AmbientOccluder::getDirection(ShadeRec &sr) {
	// sr is nonsense, only for derived class of abstract base

	Point sp = sampler_ptr->sampleHemisphere();
	return (sp.getX() * u + sp.getY() * v + sp.getZ() * w);
}

RGBColor AmbientOccluder::L(ShadeRec &sr) {
	w = sr.normal;

	// jittered to prevent boundary occasions
	v = (w ^ Vector(0.0071, 1., 0.0035)).unit();
	u = v ^ w;

	RGBColor _L = COLOR_BLACK;

	int numSamples = sampler_ptr->getNumSamples();
	for(int j = 0; j < numSamples; j++) {
		Ray shadowRay;
		shadowRay.o = sr.hit_point;
		shadowRay.d = getDirection(sr);

		/*if(sr.hit_point.getY() > 1e-1) {
			infoPrint("hit point: " + sr.hit_point.to_rep());
			infoPrint("base: " + u.to_rep() + v.to_rep() + w.to_rep());
			infoPrint("dir: " + shadowRay.d.to_rep());
			//system("pause");
		}*/

		if(inShadow(shadowRay, sr)) {
			_L += minAmount * ls * color;
		}
		else {
			_L += ls * color;
		}
	}

	return _L / numSamples;

}

bool AmbientOccluder::inShadow(const Ray &ray, const ShadeRec &sr) const {
	RTdouble t;
	int numObjects = sr.w.objects.size();
	for(int j = 0; j < numObjects; j++) {
		if(sr.w.objects[j]->shadowHit(ray, t)) {
			return true;
		}
	}
	return false;
}
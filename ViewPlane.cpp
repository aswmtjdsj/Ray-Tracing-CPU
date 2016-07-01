#include "ViewPlane.h"
#include "Sampler.h"

ViewPlane::ViewPlane() : sampler_ptr(NULL) {
}

ViewPlane::ViewPlane(const ViewPlane &vp):
hRes(vp.hRes), vRes(vp.vRes),
s(vp.s), num_samples(vp.num_samples),
sampler_ptr(vp.sampler_ptr){ // copy this!!! do not forget!!
	setGamma(vp.gamma);
}

void ViewPlane::setResH(const int &h) {
	hRes = h;
}

void ViewPlane::setResV(const int &v) {
	vRes = v;
}

void ViewPlane::setPixelSize(const RTdouble &ps) {
	s = ps;
}

void ViewPlane::setGamma(const RTdouble &g) {
	gamma = g;
	inv_gamma = (RTdouble) 1. / gamma;
}

void ViewPlane::setSampleNumber(const int& num) {
	num_samples = num;
}

void ViewPlane::setSampler(Sampler * sampler) {
	if(sampler_ptr) {
		delete sampler_ptr;
		sampler_ptr = NULL;
	}
	setSampleNumber(sampler->getNumSamples());
	sampler_ptr = sampler;
}

void ViewPlane::setSamples(const int &n) {
	setSampleNumber(n);

	if(sampler_ptr) {
		delete sampler_ptr;
		sampler_ptr = NULL;
	}

	if(num_samples > 1) {
		sampler_ptr = new MultiJittered(num_samples);
	}
	else {
		sampler_ptr = new Regular(1);
	}
}

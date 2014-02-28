#ifndef VIEWPLANE_H
#define VIEWPLANE_H

#include "common.h"

class Sampler;

class ViewPlane {
	/*
	the ViewPlane is perpendicular to the z_w - axis
	the coordinate (x_w, y_w) of the middle of the ViewPlane is (0, 0)
	x_w = s(c - h_res/2 + 0.5), x cor of center of some pixel grid
	y_w = s(r - v_res/2 + 0.5), y cor of center of some pixel grid
	*/
public:

	ViewPlane();
	ViewPlane(const ViewPlane &);

	int hRes; // horizontal Resolution
	int vRes; // vertical Resolution
	RTdouble s; // pixel size
	RTdouble gamma; // monitor gamma factor
	RTdouble inv_gamma; // 1 / gamma

	int num_samples;
	Sampler * sampler_ptr;

	void setResH(const int&);
	void setResV(const int&);
	void setPixelSize(const RTdouble &);
	void setGamma(const RTdouble &);
	void setSampleNumber(const int&);
	void setSampler(Sampler *);
	void setSamples(const int &);
};

#endif 

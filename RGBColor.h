#ifndef RGBCOLOR_H 
#define RGBCOLOR_H 

#include "common.h"

class RGBColor {
public:

	// constructor
	RGBColor();
	RGBColor(const RTdouble&);
	RGBColor(const RTdouble&, const RTdouble&, const RTdouble&);
	RGBColor(const RTdouble []); 

	// copy constructor
	RGBColor(const RGBColor &);

	// =
	RGBColor & operator=(const RGBColor &);

	// add
	RGBColor operator +(const RGBColor &) const;
	RGBColor & operator +=(const RGBColor &);

	// subtract
	RGBColor operator -(const RGBColor &) const;
	RGBColor & operator -=(const RGBColor &);

	// multiply (scale)
	RGBColor operator *(const RTdouble &) const;
	friend RGBColor operator *(const RTdouble &, const RGBColor &);
	RGBColor & operator *=(const RTdouble &);

	// multiply (mixing)
	RGBColor operator *(const RGBColor &) const;

	// divide (scale)
	RGBColor operator /(const RTdouble &) const;
	RGBColor & operator /=(const RTdouble &);

	// power
	RGBColor operator ^(const RTdouble &) const;

	//int A() const;
	RTdouble R() const;
	RTdouble G() const;
	RTdouble B() const;

	void print(const string &) const;
	string to_rep() const;

private:
	RTdouble val[3]; // RGB, scale in [0, 1]
	static const int RGB_len = 3;
};

#endif
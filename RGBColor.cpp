#include "RGBColor.h"

// there should be range checker to confirm value in range [0, 255]

RGBColor::RGBColor() {
	for( int i = 0; i < RGB_len; i++) {
		val[i] = 0;
	}
}

RGBColor::RGBColor(const RTdouble &c) {
	for( int i = 0; i < RGB_len; i++) {
		val[i] = c;
	}
}

RGBColor::RGBColor(const RTdouble &r, const RTdouble &g, const RTdouble &b) {
	//val[0] = a;
	val[0] = r;
	val[1] = g;
	val[2] = b;
}

RGBColor::RGBColor(const RTdouble color[]) {
	// assert( sizeof(color) / sizeof(int) != 4);
	// cout << sizeof(color) / sizeof(int) << endl;
	for( int i = 0; i < RGB_len; i++) {
		val[i] = color[i];
	}
}

RGBColor & RGBColor::operator =(const RGBColor &color) {
	for(int i = 0; i < RGB_len; i++) {
		val[i] = color.val[i];
	}
	return *this;
}

RGBColor::RGBColor(const RGBColor &color) {
	*this = color;
}

RGBColor RGBColor::operator +(const RGBColor&color) const {
	return RGBColor(*this) += color;
}

RGBColor & RGBColor::operator +=(const RGBColor &color) {
	for(int i = 0; i < RGB_len; i++) {
		val[i] += color.val[i];
	}
	return *this;
}

RGBColor RGBColor::operator -(const RGBColor &color) const {
	return RGBColor(*this) -= color;
}

RGBColor & RGBColor::operator -=(const RGBColor &color) {
	*this += color * (RTdouble)-1.;
	return *this;
}

RGBColor & RGBColor::operator *= (const RTdouble &scalar) {
	for(int i = 0; i < RGB_len; i++) {
		val[i] *= scalar; // decimal rate with precision loss
	}
	return *this;
}

RGBColor RGBColor::operator *(const RTdouble &scalar) const {
	return RGBColor(*this) *= scalar;
}

RGBColor RGBColor::operator *(const RGBColor &color) const {
	return RGBColor(R()*color.R(), G()*color.G(), B()*color.B());
}

RGBColor operator *(const RTdouble &scalar, const RGBColor &color) {
	return color * scalar;
}

RGBColor RGBColor::operator /(const RTdouble &scalar) const {
	return RGBColor(*this) /= scalar;
}

RGBColor & RGBColor::operator /= (const RTdouble &scalar) {
	*this *= (1. / scalar);
	return *this;
}

RGBColor RGBColor::operator ^(const RTdouble &n) const {
	RGBColor temp(pow(R(), n), pow(G(), n), pow(B(), n));
	return temp;
}

RTdouble RGBColor::R() const {
	return val[0];
}

RTdouble RGBColor::G() const {
	return val[1];
}

RTdouble RGBColor::B() const {
	return val[2];
}

void RGBColor::print(const string &prompt) const {
	printf("Color %s is (%.3lf, %.3lf, %.3lf).\n", prompt.c_str(), R(), G(), B());
}

string RGBColor::to_rep() const {
	return "(" + to_string(R()) + ", " + to_string(G()) + ", " + to_string(B()) + ")";
}
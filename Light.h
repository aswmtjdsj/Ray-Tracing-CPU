#ifndef LIGHT_H
#define LIGHT_H

#include "RGBColor.h"
#include "Vector.h"

class ShadeRec;
class Ray;

class Light {

public:
	Light();
	virtual Vector getDirection(ShadeRec &) = 0;
	virtual RGBColor L(ShadeRec &) = 0;
	virtual bool inShadow(const Ray &, const ShadeRec &) const = 0;
	bool castShadows() const; // no difference being derived

protected:
	bool shadows;
};

class Ambient: public Light {
public:
	Ambient();

	virtual Vector getDirection(ShadeRec &);
	virtual RGBColor L(ShadeRec &);
	void scaleRadience(const RTdouble &);

	// shadow
	virtual bool inShadow(const Ray &, const ShadeRec &) const;

private:
	RTdouble ls;
	RGBColor color;
};

class PointLight: public Light {
public:
	PointLight();

	virtual Vector getDirection(ShadeRec &);
	virtual RGBColor L(ShadeRec &);
	void scaleRadience(const RTdouble &);
	Point getLocation() const;

	void setLocation(const Point &);
	void setCoeff(const RTdouble &);
	void setColor(const RGBColor &);

	virtual bool inShadow(const Ray &, const ShadeRec &) const;

private:
	RTdouble ls;
	RGBColor color;
	Point location;
	
	RTdouble coeff;
};

class Directional: public Light {
public:

	Directional();

	virtual Vector getDirection(ShadeRec &);
	virtual RGBColor L(ShadeRec &);
	void setDir(const Vector &);

	virtual bool inShadow(const Ray &, const ShadeRec &) const;
private:
	RTdouble ls;
	RGBColor color;
	Vector dir;
};

#endif

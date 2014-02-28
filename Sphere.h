#ifndef SPHERE_H
#define SPHERE_H

#include "common.h"
#include "GeometryObject.h"
#include "Point.h"

class Sphere: public GeometryObject {
public:
	Sphere();
	Sphere(const Point &, const RTdouble &);

	void setCenter(const RTdouble &);
	void setCenter(const Point &);
	void setRadius(const RTdouble &);

	virtual bool hit(const Ray &, RTdouble &, ShadeRec &) const;
	virtual bool shadowHit(const Ray &, RTdouble &) const;
	virtual RGBColor getColor() const;
	virtual void setColor(const RGBColor &);
	virtual Material * getMaterial() const;
	virtual void setMaterial(Material *);
	void print(const string &) const;

private:
	Point c;
	RTdouble r;
	static const RTdouble kEpsilon;
};

#endif 

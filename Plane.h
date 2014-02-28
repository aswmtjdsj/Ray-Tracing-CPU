#ifndef PLANE_H
#define PLANE_H

#include "common.h"
#include "Constants.h"
#include "GeometryObject.h"
#include "Point.h"
#include "Vector.h"
#include "Normal.h"
#include "ShadeRec.h"
#include "Ray.h"

class Plane: public GeometryObject {
public:
	Plane();
	Plane(const Point &, const Normal &);
	
	virtual bool hit(const Ray &, double &, ShadeRec &) const;
	virtual bool shadowHit(const Ray &, RTdouble &) const;
	virtual RGBColor getColor() const;
	virtual void setColor(const RGBColor &);
	virtual Material * getMaterial() const;
	virtual void setMaterial(Material *);

	void print(const string &) const;

private:
	Point p;
	Normal n;
	static const RTdouble kEpsilon;
};

#endif

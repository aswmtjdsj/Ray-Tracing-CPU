#ifndef GEOMETRYOBJECT_H
#define GEOMETRYOBJECT_H

#include "common.h"
#include "RGBColor.h"
#include "Material.h"

class Ray; // fake
class ShadeRec; // fake
class GeometryObject { // abstract base class
public:
	GeometryObject();
	virtual ~GeometryObject() = 0;
	virtual bool hit(const Ray &, RTdouble &, ShadeRec &) const = 0;
	virtual bool shadowHit(const Ray &, RTdouble &) const = 0;
	virtual RGBColor getColor() const = 0;
	virtual void setColor(const RGBColor &) = 0;
	virtual Material * getMaterial() const = 0;
	virtual void setMaterial(Material *) = 0;

protected:
	RGBColor color; // temp
	Material *material;
	bool shadows;
};

#endif

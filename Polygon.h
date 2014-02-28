#ifndef POLYGON_H
#define POLYGON_H

#include "common.h"
#include "GeometryObject.h"
#include "Point.h"
#include "Normal.h"

class Polygon: public GeometryObject {
public:
	Polygon();
	Polygon(const vector <Point> &);
	Polygon(const Point *, const int &);

	// detect the polygon can construct a plane or not
	void coplanarTest();

	// some geometrical funtions 
	bool getNormal(Normal &) const;
	bool inPolygon(const Point &) const;

	virtual bool hit(const Ray &, RTdouble &, ShadeRec &) const;
	virtual bool shadowHit(const Ray &, RTdouble &) const;

	virtual RGBColor getColor() const;
	virtual void setColor(const RGBColor &);
	virtual Material * getMaterial() const;
	virtual void setMaterial(Material *);

	void print(const string &) const;

private:
	vector <Point> vertices;
	static const RTdouble kEpsilon;
	bool coplanar;
};

#endif
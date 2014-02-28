#ifndef RAY_H
#define RAY_H 

#include "common.h"
#include "Vector.h"
#include "Point.h"

class Ray {
public:

	// f(o+td)=0
	Point o;
	Vector d;

	Ray();
	Ray(const Point &, const Vector &);
	Ray(const Ray &);

	Ray & operator = (const Ray &);

	~Ray();

	void print(const string &) const;
};

#endif
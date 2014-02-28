#ifndef SHADEREC_H
#define SHADEREC_H

#include "common.h"
#include "Point.h"
#include "Vector.h"
#include "Normal.h"
#include "Ray.h"
#include "RGBColor.h"

class World;
class Material;

class ShadeRec {
public:
	bool hit_an_object;
	Material * material_ptr;
	Point hit_point;
	Point local_hit_point;
	Normal normal;
	RGBColor color;
	Ray ray;
	int depth;
	Vector dir;
	World &w;
	RTdouble t;

	ShadeRec(World &);
	ShadeRec(const ShadeRec &);
	~ShadeRec();
};

#endif
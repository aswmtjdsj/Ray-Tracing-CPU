#ifndef CAMERA_H
#define CAMERA_H

#include "common.h"
#include "Point.h"
#include "Vector.h"
class World;

class Camera {
public:
	Camera();
	// maybe we should not let a const param have default value
	Camera(const Point &, const Point &, const Vector &/*, const RTdouble &*/);
	void setEye(const Point &);
	void setLookAt(const Point &);
	void setUp(const Vector &);
	void setExposureTime(const RTdouble &);
	void uvwCompute();
	virtual void renderScene(World &) = 0;

protected:
	Point eye;
	Point lookAt;
	Vector up;
	Vector u, v, w;
	RTdouble exposureTime;
	
};

#endif
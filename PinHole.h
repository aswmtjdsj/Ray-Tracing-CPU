#ifndef PIN_HOLE_H
#define PIN_HOLE_H

#include "Camera.h"

class PinHole: public Camera {
public:
	PinHole();
	// exposure time can be omitted if not willing to set
	PinHole(const Point &, const Point &, const Vector &, /*const RTdouble &,*/ 
		const RTdouble &, const RTdouble &);

	void setViewPlaneDistance(const RTdouble &);
	void setZoomFactor(const RTdouble &);
	Vector rayDirection(const Point2D &) const;
	virtual void renderScene(World &);
private:
	RTdouble d;
	RTdouble zoom;
};

#endif
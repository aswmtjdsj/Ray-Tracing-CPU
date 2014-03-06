#include "Camera.h"
#include "Constants.h"

Camera::Camera(): up(Vector(RT_ZERO, RT_ONE, RT_ZERO)), exposureTime(RT_ONE) {
}

Camera::Camera(const Point &_eye, const Point &l_a, const Vector &_up/*, const RTdouble &exp_t = 1.0*/):
	eye(_eye), lookAt(l_a), up(_up)/*, exposureTime(exp_t)*/ {
		uvwCompute();
}

void Camera::setEye(const Point &_eye) {
	eye = _eye;
}

void Camera::setLookAt(const Point &l_a) {
	lookAt = l_a;
}

void Camera::setUp(const Vector &_up) {
	up = _up;
}

void Camera::setExposureTime(const RTdouble &exp_t) {
	exposureTime = exp_t;
}

void Camera::uvwCompute() {
	// should be called after construction
	w = (eye - lookAt).unit();
	u = (up ^ w).unit();
	v = (w ^ u).unit();

	infoPrint("Camera Coordinates:\n\tu: " + u.to_rep() + "\n\tv: " + v.to_rep() + "\n\tw: " + w.to_rep() + "\n");
}

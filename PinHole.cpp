#include "PinHole.h"
#include "Constants.h"
#include "World.h"
#include "Sampler.h"

PinHole::PinHole(): Camera(), zoom(RT_ONE) {
}

PinHole::PinHole(const Point &_eye, const Point &l_a, const Vector &_up, /*const RTdouble &exp_t,*/
				 const RTdouble &_d, const RTdouble &zoom_factor = RT_ONE): Camera(_eye, l_a, _up), d(_d), zoom(zoom_factor) {
					 uvwCompute();
}

void PinHole::renderScene(World &w) {
	RGBColor L;
	ViewPlane vp(w.vp);
	Ray ray;
	int depth = 0;
	Point2D sp, pp;
	// wrongly open another window.... so there are too many window pointers....
	vp.s /= zoom;
	ray.o = eye;

	for(int r = 0; r < vp.vRes; r++) {
		w.draw.setRefresh(true);
		for(int c = 0; c < vp.hRes; c++) {
			L = COLOR_BLACK;
			for(int j = 0; j < vp.num_samples; j++) {
				sp = vp.sampler_ptr->sampleUnitSquare();
				pp.first = vp.s * (c - (RTdouble)0.5 * (vp.hRes - RT_ONE)) + sp.first;
				pp.second = vp.s * (r - (RTdouble)0.5 * (vp.vRes - RT_ONE)) + sp.second;
				ray.d = rayDirection(pp);
				//ray.d.print("direction");
				//system("pause");
				L += w.tracer_ptr->traceRay(ray, depth);
			}

			L /= vp.num_samples;
			//L.print("aaa");
			L *= exposureTime;

			if(vp.gamma != RT_ONE) {
				L = L^vp.gamma;
			}

			w.displayPixel(r, c, L);
		}
	}
}

Vector PinHole::rayDirection(const Point2D &pp) const {
	return (pp.first * u + pp.second * v - d * w).unit();
}

void PinHole::setViewPlaneDistance(const RTdouble &_d) {
	d = _d;
}

#include "Constants.h"
#include "Random.h"
#include "Sampler.h"

#include "Vector.h"
#include "Normal.h"
#include "Ray.h"

#include "World.h"
#include "ShadeRec.h"

#include "SingleSphere.h"
#include "MultipleObjects.h"

#include "Sphere.h"
#include "Plane.h"

#include "BuildFunctions.h"

#include "AmbientOccluder.h"

World::World()://camera_ptr(NULL)
bg_color(COLOR_BLACK),
tracer_ptr(NULL),
ambient(new Ambient){
}


void World::work() { // now that show window is another thread, while ray tracing is not
	infoPrint("Begin Working Load!");
	openWindow();
	infoPrint("Launch Ray Tracing Thread!");
	draw.nonBlockRayTracingWorld(this);
	infoPrint("Waiting in the event loop!");
	draw.eventHandler();
}

void World::simpleRenderScene() {
	infoPrint("Begin Simple Scene Rendering!");
	RGBColor pixelColor;
	Ray ray;
	RTdouble zw = (RTdouble)100., d = zw*5; // z of vp

	Point2D sp; // in [0, 1]^2
	Point2D pp; // on a pixel1

	//ray.d = Vector(RT_ZERO, RT_ZERO, -RT_ONE);
	ray.o = Point(RT_ZERO, RT_ZERO, d);

	for(int r = 0; r < vp.vRes; r++) {
		draw.setRefresh(true);
		for(int c = 0; c < vp.hRes; c++) {

			pixelColor = COLOR_BLACK;

			// random sampling
			for(int p = 0; p < vp.num_samples; p++) {
				sp = vp.sampler_ptr->sampleUnitSquare();
				pp.first = vp.s * (c - (RTdouble)0.5 * (vp.hRes - RT_ONE) + sp.first);
				pp.second = vp.s * (r - (RTdouble)0.5 * (vp.vRes - RT_ONE) + sp.second);
				//ray.o = Point(x, y, zw);
				ray.d = Vector(pp.first, pp.second, -d).unit();
				pixelColor += tracer_ptr->traceRay(ray, 1);
			}

			if( vp.gamma != RT_ONE) {
				pixelColor = pixelColor^vp.gamma;
			}

			// average after sampling
			pixelColor /= vp.num_samples;

			displayPixel(r, c, pixelColor);
		}
	}
}

void World::build() {
	infoPrint("Begin building the world!");
	Random::rand_init();
	infoPrint("Random seed initiated!");
	//buildAmbient(*this);
	buildCornell2(*this);
}

void World::openWindow() {
	infoPrint("Begin Creating Window!");
	draw.setHeight(vp.vRes);
	draw.setWidth(vp.hRes);
	draw.init();
	// only on macosx
	//draw.nonBlockingShowWindow();
	//Drawing::showWindowThread(&draw);
}

void World::finish() {
	// clear other resources
	draw.close();
}

void World::displayPixel(const int &r, const int &c, const RGBColor &pixelColor) {
	// in case of color overflow
	RGBColor showColor = maxToOne(pixelColor);
	Uint32 colorConverted = 0;
	int cr = (int)(showColor.R() * 255),
		cg = (int)(showColor.G() * 255),
		cb = (int)(showColor.B() * 255);

	colorConverted |= cr << 16; // R
	colorConverted |= cg << 8; // G
	colorConverted |= cb; // B

	draw.setPixel(r, c, colorConverted);
}

void World::addObject( GeometryObject * obj_ptr) {
	objects.push_back(obj_ptr);
}

ShadeRec World::hitBareBonesOjbects(const Ray &ray) {
	ShadeRec sr(*this);
	double t;
	double min_t = RT_INFINITY;

	int num_obj = objects.size();

	for(int j = 0; j < num_obj; j++) {
		if(objects[j]->hit(ray, t, sr) && (t < min_t)) {
			sr.hit_an_object = true;
			min_t = t;
			sr.color = objects[j]->getColor();
		}
	}

	return sr;
}

ShadeRec World::hitOjbects(const Ray &ray) {
	ShadeRec sr(*this);

	RTdouble t;
	Normal normal;
	Point local_hit_point;
	RTdouble min_t = RT_INFINITY;
	RGBColor color = COLOR_WHITE;
	int num_obj = objects.size();

	for(int j = 0; j < num_obj; j++) {
		if(objects[j]->hit(ray, t, sr) && (t < min_t)) {
			sr.hit_an_object = true;
			min_t = t;
			sr.material_ptr = objects[j]->getMaterial();
			sr.hit_point = ray.o + t * ray.d;
			normal = sr.normal;
			local_hit_point = sr.local_hit_point;
			color = objects[j]->getColor();
		}

		if(sr.hit_an_object) {
			sr.t = min_t;
			sr.normal = normal;
			sr.local_hit_point = local_hit_point;
			sr.color = color;
		}
	}
	return sr;
}

void World::addLight( Light * light_ptr) {
	lights.push_back(light_ptr);
}

void World::generateVPLs(PointLight *pl, const Normal &n) {
	Sampler * for_use = new MultiJittered(64);
	for_use->setNumSets(83);
	for_use->generateSamples();
	for_use->setupShuffledIndices();
	for_use->mapSamplesToHemisphere(RT_ONE);

	Vector u, v, w;
	w = n;
	v = (w ^ Vector(0.0071, 1., 0.0035)).unit();
	u = (v ^ w).unit();

	int num = for_use->getNumSamples();

	for(int j = 0; j < num; j++) {

		Point sp = for_use->sampleHemisphere();
		Vector dir = sp.getX() * u + sp.getY() * v + sp.getZ() * w;

		infoPrint("dir " + to_string(j) + ": " + dir.to_rep());

		Ray ray(pl->getLocation(), dir);
		ShadeRec sr(hitOjbects(ray));

		if(sr.hit_an_object) {
			infoPrint(sr.hit_point.to_rep());
			infoPrint(pl->L(sr).to_rep());
			RTdouble r = pl->getLocation().distance(sr.hit_point);
			//pl->L(sr);
			if(sqrt(sr.color.R() * sr.color.R()
				+ sr.color.G() * sr.color.G()
				+ sr.color.B() * sr.color.B()) > 0.01) {
					PointLight * vpl = new PointLight;
					vpl->setColor(sr.color);
					vpl->setCoeff(0.0001);
					vpl->setLocation(sr.hit_point - ray.d * 0.00001);
					addLight(vpl);
			}
		}
	}
}

void World::setAmbientLight(Ambient *ambient_ptr) {
	ambient = ambient_ptr;
}

void World::setAmbientOccluder(AmbientOccluder *ambient_ptr) {
	ambient = ambient_ptr;
}

void World::setCamera(Camera * specific_camera) {
	camera_ptr = specific_camera;
}

RGBColor World::maxToOne(const RGBColor &c) const {
	RTdouble maxVal = max(c.R(), max(c.G(), c.B()));
	if(maxVal > RT_ONE) {
		return c / maxVal;
	}
	else {
		return c;
	}
}

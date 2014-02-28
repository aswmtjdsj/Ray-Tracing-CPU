#ifndef WORLD_H
#define WORLD_H

#include "common.h"
#include "RGBColor.h"
#include "Sphere.h"
#include "ViewPlane.h"
#include "Tracer.h"
#include "Drawing.h"
#include "Light.h"
#include "Camera.h"

class AmbientOccluder;

class World {
public:
	ViewPlane vp; // the plane to show rendered results

	Camera * camera_ptr; // camera used to do projection

	RGBColor bg_color; // background color

	Sphere sphere; // no use here, but for Single Sphere Tracer

	Tracer * tracer_ptr; // tracer pointer to point to different tracers

	Drawing draw; // the part used to interact with GUI

	vector <GeometryObject *> objects; // object storage

	Light * ambient; //

	vector<Light *> lights; // light storage

	// base functions
	World();

	//
	void build();

	// init screen
	void openWindow();

	// work procedure
	void work();

	// finish the work
	void finish();

	// when without cameras
	void simpleRenderScene();
	
	// update the screen
	void displayPixel(const int &, const int &, const RGBColor &);

	// for multiple objects
	void addObject(GeometryObject *);

	// simple hit system 
	ShadeRec hitBareBonesOjbects(const Ray &);
	
	// for adding lights
	void addLight(Light *);

	// fake, generate VPLs
	void generateVPLs(PointLight *, const Normal &);

	void setAmbientLight(Ambient *);
	void setAmbientOccluder(AmbientOccluder *);

	void setCamera(Camera *);

	// for general use
	ShadeRec hitOjbects(const Ray &); // wtf, different from here to there in the context book

	// for overflow colors
	RGBColor maxToOne(const RGBColor &) const;
};

#endif

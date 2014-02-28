#include "Normal.h"
#include "Constants.h"

#include "Sphere.h"
#include "Plane.h"
#include "Polygon.h"

#include "MultipleObjects.h"
//#include "SingleSphere.h"

#include "Light.h"
#include "AmbientOccluder.h"

#include "Matte.h"
#include "Phong.h"

#include "RayCasting.h"

#include "World.h"

#include "Random.h"
#include "Sampler.h"
#include "PinHole.h"

#include "BuildFunctions.h"

void buildSphere(World &w) {
	w.vp.setResH(1000);
	w.vp.setResV(1000);
	w.vp.setPixelSize((RTdouble)1.);
	w.vp.setGamma((RTdouble)1.);

	w.bg_color = COLOR_BLACK;

	// single sphere world
	/*tracer_ptr = new SingleSphere(this);

	sphere.setCenter(RT_ZERO);
	sphere.setRadius((RTdouble)85.);*/

	w.tracer_ptr = new MultipleObjects(&w);

	Sphere * red_ball = new Sphere( Point(RT_ZERO, -25, 0), (RTdouble)80.);
	red_ball->setColor(COLOR_RED);
	w.addObject(red_ball);

	Sphere * yellow_ball = new Sphere;
	yellow_ball->setCenter(Point(0, 30, 0));
	yellow_ball->setRadius((RTdouble)60.);
	yellow_ball->setColor(RGBColor(1., 1., 0.));
	w.addObject(yellow_ball);

	Plane * plane = new Plane(Point(RT_ZERO), Normal(0, 1, 1));
	plane->setColor(RGBColor(1., 0.3, 1.));
	w.addObject(plane);
	// as plane intersects with viewplane, so something strange happens

	// should not be here
	w.openWindow();
}

void buildRandom(World & w) {

	infoPrint("Setting world params!");
	int res_h = 600, res_v = 600;
	RTdouble gamma_value = RT_ONE, pixel_size = RT_ONE;
	int num_samples = 4;
	int sampler_sets = 83;

	w.vp.setResH(res_h);
	w.vp.setResV(res_v);
	infoPrint("Resolution of view plane, Horizontal: " + to_string(w.vp.hRes) + " Vertical: "+ to_string(w.vp.hRes) + "!");

	w.vp.setPixelSize(pixel_size);
	infoPrint("Pixel size of view plane: " + to_string(pixel_size) + "!");
	w.vp.setGamma(gamma_value);
	infoPrint("Gamma value of view plane: " + to_string(gamma_value) + "!");

	//w.vp.setSampler(new MultiJittered(num_samples));
	w.vp.setSamples(num_samples);
	infoPrint("Selected Sampler of view plane: "+string(w.vp.num_samples==1?"Regular":"MultiJittered")+"!");
	infoPrint("Sample number of chosen Sampler: " + to_string(w.vp.sampler_ptr->getNumSamples()) + "!");
	w.vp.sampler_ptr->setNumSets(sampler_sets);
	infoPrint("Sample sets of chosen Sampler: " + to_string(w.vp.sampler_ptr->getNumSets()) + "!");
	w.vp.sampler_ptr->generateSamples();
	infoPrint("Generating Samples of the Sampler!");
	w.vp.sampler_ptr->setupShuffledIndices();
	infoPrint("Shuffle Samples of the Sampler!");
	w.vp.sampler_ptr->mapSamplesToUnitDisk();
	infoPrint("Try Mapping Samples onto the disk!");
	w.vp.sampler_ptr->mapSamplesToHemisphere(1.);
	infoPrint("Try Mapping Samples onto the hemisphere!");

	w.bg_color = COLOR_BLACK;
	infoPrint("Background color of the world: " + string("black") + "!");

	w.tracer_ptr = new RayCasting(&w);
	infoPrint("Ray tracer of the world: " + string("Ray Casting") + "!");

	PinHole * pinhole_ptr = new PinHole;
	/*RTdouble view_distance = 500.;
	Point eye(RT_ZERO, RT_ZERO, view_distance), look_at(RT_ZERO, RT_ZERO, RT_ZERO);*/
	RTdouble view_distance = 400.;
	Point eye(300., 400., 500.), look_at(RT_ZERO, RT_ZERO, -50);
	infoPrint("Selected Camera: "+string("PinHole")+"!");
	pinhole_ptr->setEye(eye);
	infoPrint("Camera Eye: "+eye.to_rep()+"!");
	pinhole_ptr->setLookAt(look_at);
	infoPrint("Camera Look At Point: "+look_at.to_rep()+"!");
	pinhole_ptr->setViewPlaneDistance(view_distance);
	infoPrint("Distance between Camera and ViewPlane: "+to_string(view_distance)+"!");
	pinhole_ptr->uvwCompute();
	w.setCamera(pinhole_ptr);

	infoPrint("Adding ambient light(s)!");
	Ambient * ambient = new Ambient;
	// the value of ambient
	ambient->scaleRadience(RT_ONE);
	w.setAmbientLight(ambient);

	infoPrint("Adding point light(s)!");
	PointLight * light_ptr = new PointLight;
	light_ptr->setLocation(Point(100, 300, -50));
	light_ptr->scaleRadience(3.0);
	w.addLight(light_ptr);

	infoPrint("Adding Matte object(s)!");
	// matte objects
	for(int i = 0; i < 5; i++) {
		Matte * matte_ptr = new Matte;
		RTdouble x, y, r, ka, kd, cr, cg, cb;
		ka = Random::rand_float();
		kd = Random::rand_float();
		cr = Random::rand_float();
		cg = Random::rand_float();
		cb = Random::rand_float();

		matte_ptr->set_ka(0.25);
		matte_ptr->set_kd(0.65);
		matte_ptr->set_cd(RGBColor(cr,cg,cb));

		x = Random::rand_float() * w.vp.hRes - w.vp.hRes / 2.;
		y = Random::rand_float() * w.vp.vRes - w.vp.vRes / 2.;
		r = Random::rand_float() * 50 + 10;
		w.addObject(new Sphere(Point(x,y,i*(-5)), r));
		w.objects[w.objects.size()-1]->setMaterial(matte_ptr);
	}

	infoPrint("Adding Phong object(s)!");
	// phong objects
	for(int i = 0; i < 5; i++) {
		RTdouble x, y, r, cr, cg, cb, exp;
		cr = Random::rand_float();
		cg = Random::rand_float();
		cb = Random::rand_float();
		exp = Random::rand_float() * 20;

		Phong * phong_ptr = new Phong;
		phong_ptr->set_ka(0.25);
		phong_ptr->set_kd(0.65);
		phong_ptr->set_ks(0.2);
		phong_ptr->set_exp(exp);
		phong_ptr->set_cd(RGBColor(cr,cg,cb));
		phong_ptr->set_cs(RGBColor(cr,cg,cb));

		x = Random::rand_float() * w.vp.hRes - w.vp.hRes / 2.;
		y = Random::rand_float() * w.vp.vRes /*- w.vp.vRes*/ / 2.;
		r = /*Random::rand_float() **/ 50 + 10;

		w.addObject(new Sphere(Point(x,y,i*(-50)), r));
		w.objects[w.objects.size()-1]->setMaterial(phong_ptr);
	}

	// plane
	if(1) {
		Phong * phong_ptr = new Phong;
		phong_ptr->set_ka(0.25);
		phong_ptr->set_kd(0.65);
		phong_ptr->set_ks(0.2);
		phong_ptr->set_exp(20);
		phong_ptr->set_cd(RGBColor(1.,1.,1.));
		phong_ptr->set_cs(RGBColor(1.,1.,1.));

		//for(int i = 0; i < 5; i++) {
			//Plane * plane = new Plane(Point(-300, 0, 0), Normal(1, 0, 0));
		Plane * plane = new Plane(Point(0, 0, 0), Normal(0, 1, 0));

		w.addObject(plane);
		w.objects[w.objects.size()-1]->setMaterial(phong_ptr);
		//}
		infoPrint("Adding a plane!");
	}

	// polyhedron
	if(1) {
		Phong * phong_ptr = new Phong;
		phong_ptr->set_ka(0.25);
		phong_ptr->set_kd(0.65);
		phong_ptr->set_ks(0.2);
		phong_ptr->set_exp(5);
		phong_ptr->set_cd(RGBColor(0., 1., 1.));
		phong_ptr->set_cs(RGBColor(0., 1., 0.)); // specular color no use

		RTdouble length_edge = 100, offset = 0;
		Point vertex[8];
		for(int i = 0; i < 8; i++) {
			RTdouble temp[3] = {0};
			for(int j = 0; j < 3; j++) {
				temp[j] = offset;
				if( (i >> j) & 1) {
					temp[j] += length_edge;
				}
			}
			vertex[i] = Point(temp[0], temp[1], temp[2]);
		}
		int pp_index[6][4] = {
			{0, 1, 3, 2},
			{0, 2, 6, 4},
			{0, 1, 5, 4},
			{1, 3, 7, 5},
			{2, 3, 7, 6},
			{4, 5, 7, 6},
		};

		for( int i = 0; i < 6; i++) {
			vector <Point> ps;
			for(int j = 0; j < 4; j++) {
				ps.push_back(vertex[pp_index[i][j]]);
			}
			Polygon * poly= new Polygon(ps);

			w.addObject(poly);
			w.objects[w.objects.size()-1]->setMaterial(phong_ptr);
		}
		infoPrint("Adding a polyhedron!");
	}

}

void buildAmbient(World & w) {

	infoPrint("Setting world params!");
	int res_h = 300, res_v = 300;
	RTdouble gamma_value = RT_ONE, pixel_size = RT_ONE;
	int num_samples = 4;
	int sampler_sets = 83;

	w.vp.setResH(res_h);
	w.vp.setResV(res_v);
	infoPrint("Resolution of view plane, Horizontal: " + to_string(w.vp.hRes) + " Vertical: "+ to_string(w.vp.hRes) + "!");

	w.vp.setPixelSize(pixel_size);
	infoPrint("Pixel size of view plane: " + to_string(pixel_size) + "!");
	w.vp.setGamma(gamma_value);
	infoPrint("Gamma value of view plane: " + to_string(gamma_value) + "!");

	//w.vp.setSampler(new MultiJittered(num_samples));
	w.vp.setSamples(num_samples);
	infoPrint("Selected Sampler of view plane: "+string(w.vp.num_samples==1?"Regular":"MultiJittered")+"!");
	infoPrint("Sample number of chosen Sampler: " + to_string(w.vp.sampler_ptr->getNumSamples()) + "!");
	w.vp.sampler_ptr->setNumSets(sampler_sets);
	infoPrint("Sample sets of chosen Sampler: " + to_string(w.vp.sampler_ptr->getNumSets()) + "!");
	w.vp.sampler_ptr->generateSamples();
	infoPrint("Generating Samples of the Sampler!");
	w.vp.sampler_ptr->setupShuffledIndices();
	infoPrint("Shuffle Samples of the Sampler!");
	w.vp.sampler_ptr->mapSamplesToUnitDisk();
	infoPrint("Try Mapping Samples onto the disk!");
	w.vp.sampler_ptr->mapSamplesToHemisphere(1.);
	infoPrint("Try Mapping Samples onto the hemisphere!");

	w.bg_color = COLOR_BLACK;
	infoPrint("Background color of the world: " + string("black") + "!");

	w.tracer_ptr = new RayCasting(&w);
	infoPrint("Ray tracer of the world: " + string("Ray Casting") + "!");

	PinHole * pinhole_ptr = new PinHole;
	/*RTdouble view_distance = 500.;
	Point eye(RT_ZERO, RT_ZERO, view_distance), look_at(RT_ZERO, RT_ZERO, RT_ZERO);*/
	RTdouble view_distance = 50.;
	Point eye(0., 100., 60.), look_at(RT_ZERO, 0, -30.);
	infoPrint("Selected Camera: "+string("PinHole")+"!");
	pinhole_ptr->setEye(eye);
	infoPrint("Camera Eye: "+eye.to_rep()+"!");
	pinhole_ptr->setLookAt(look_at);
	infoPrint("Camera Look At Point: "+look_at.to_rep()+"!");
	pinhole_ptr->setViewPlaneDistance(view_distance);
	infoPrint("Distance between Camera and ViewPlane: "+to_string(view_distance)+"!");
	pinhole_ptr->uvwCompute();
	w.setCamera(pinhole_ptr);

	infoPrint("Adding ambient light(s)!");
	//Ambient * ambient = new Ambient;
	AmbientOccluder * ambient = new AmbientOccluder; // need debugging
	// the value of ambient
	ambient->scaleRadience(2. * RT_ONE);
	ambient->setSampler(new MultiJittered(256));//num_samples * num_samples));
	infoPrint("Selected Sampler of Ambient Occluder: "+string("MultiJittered")+"!");
	infoPrint("Sample number of chosen Sampler: " + to_string(ambient->getSamplerPtr()->getNumSamples()) + "!");
	ambient->getSamplerPtr()->setNumSets(sampler_sets);
	infoPrint("Sample sets of chosen Sampler: " + to_string(ambient->getSamplerPtr()->getNumSets()) + "!");
	ambient->getSamplerPtr()->generateSamples();
	infoPrint("Generating Samples of the Sampler!");
	ambient->getSamplerPtr()->setupShuffledIndices();
	infoPrint("Shuffle Samples of the Sampler!");
	ambient->getSamplerPtr()->mapSamplesToHemisphere(RT_ONE);
	infoPrint("Try Mapping Samples onto the hemisphere!");

	w.setAmbientOccluder(ambient);

	if(1) { // point light
		infoPrint("Adding point light(s)!");
		PointLight * light_ptr = new PointLight;
		light_ptr->setLocation(Point(100, 300, -50));
		light_ptr->scaleRadience(3.0);
		w.addLight(light_ptr);
	}

	infoPrint("Adding Matte object(s)!");
	// matte objects
	for(int i = 0; i < 1; i++) {
		Matte * matte_ptr = new Matte;
		RTdouble x, y, r, cr, cg, cb;
		cr = 0.5;
		cg = 0.3;
		cb = 0.8;

		matte_ptr->set_ka(0.25);
		matte_ptr->set_kd(0.65);
		matte_ptr->set_cd(RGBColor(cr,cg,cb));

		x = 0;
		y = 50;
		r = 50;
		w.addObject(new Sphere(Point(x,y,0), r));
		w.objects[w.objects.size()-1]->setMaterial(matte_ptr);
	}

	// plane
	if(1) {
		Phong * phong_ptr = new Phong;
		phong_ptr->set_ka(0.25);
		phong_ptr->set_kd(0.65);
		phong_ptr->set_ks(0.2);
		phong_ptr->set_exp(20);
		phong_ptr->set_cd(RGBColor(1.,1.,1.));
		phong_ptr->set_cs(RGBColor(1.,1.,1.));

		//for(int i = 0; i < 5; i++) {
			//Plane * plane = new Plane(Point(-300, 0, 0), Normal(1, 0, 0));
		Plane * plane = new Plane(Point(0, 0, 0), Normal(0, 1, 0));

		w.addObject(plane);
		w.objects[w.objects.size()-1]->setMaterial(phong_ptr);
		//}
		infoPrint("Adding a plane!");
	}

	// polyhedron
	if(0) {
		Phong * phong_ptr = new Phong;
		phong_ptr->set_ka(0.25);
		phong_ptr->set_kd(0.65);
		phong_ptr->set_ks(0.2);
		phong_ptr->set_exp(5);
		phong_ptr->set_cd(RGBColor(0., 1., 1.));
		phong_ptr->set_cs(RGBColor(0., 1., 0.)); // specular color no use

		RTdouble length_edge = 100, offset = 0;
		Point vertex[8];
		for(int i = 0; i < 8; i++) {
			RTdouble temp[3] = {0};
			for(int j = 0; j < 3; j++) {
				temp[j] = offset;
				if( (i >> j) & 1) {
					temp[j] += length_edge;
				}
			}
			vertex[i] = Point(temp[0], temp[1], temp[2]);
		}
		int pp_index[6][4] = {
			{0, 1, 3, 2},
			{0, 2, 6, 4},
			{0, 1, 5, 4},
			{1, 3, 7, 5},
			{2, 3, 7, 6},
			{4, 5, 7, 6},
		};

		for( int i = 0; i < 6; i++) {
			vector <Point> ps;
			for(int j = 0; j < 4; j++) {
				ps.push_back(vertex[pp_index[i][j]]);
			}
			Polygon * poly= new Polygon(ps);

			w.addObject(poly);
			w.objects[w.objects.size()-1]->setMaterial(phong_ptr);
		}
		infoPrint("Adding a polyhedron!");
	}

}

void buildCornell(World &w) {

	infoPrint("Setting world params!");
	int res_h = 600, res_v = 600;
	RTdouble gamma_value = RT_ONE, pixel_size = RT_ONE;
	int num_samples = 4;
	int sampler_sets = 83;

	w.vp.setResH(res_h);
	w.vp.setResV(res_v);
	infoPrint("Resolution of view plane, Horizontal: " + to_string(w.vp.hRes) + " Vertical: "+ to_string(w.vp.hRes) + "!");

	w.vp.setPixelSize(pixel_size);
	infoPrint("Pixel size of view plane: " + to_string(pixel_size) + "!");
	w.vp.setGamma(gamma_value);
	infoPrint("Gamma value of view plane: " + to_string(gamma_value) + "!");

	//w.vp.setSampler(new MultiJittered(num_samples));
	w.vp.setSamples(num_samples);
	infoPrint("Selected Sampler of view plane: "+string(w.vp.num_samples==1?"Regular":"MultiJittered")+"!");
	infoPrint("Sample number of chosen Sampler: " + to_string(w.vp.sampler_ptr->getNumSamples()) + "!");
	w.vp.sampler_ptr->setNumSets(sampler_sets);
	infoPrint("Sample sets of chosen Sampler: " + to_string(w.vp.sampler_ptr->getNumSets()) + "!");
	w.vp.sampler_ptr->generateSamples();
	infoPrint("Generating Samples of the Sampler!");
	w.vp.sampler_ptr->setupShuffledIndices();
	infoPrint("Shuffle Samples of the Sampler!");
	w.vp.sampler_ptr->mapSamplesToUnitDisk();
	infoPrint("Try Mapping Samples onto the disk!");
	w.vp.sampler_ptr->mapSamplesToHemisphere(1.);
	infoPrint("Try Mapping Samples onto the hemisphere!");

	w.bg_color = COLOR_BLACK;
	infoPrint("Background color of the world: " + string("black") + "!");

	w.tracer_ptr = new RayCasting(&w);
	infoPrint("Ray tracer of the world: " + string("Ray Casting") + "!");

	PinHole * pinhole_ptr = new PinHole;
	/*RTdouble view_distance = 500.;
	Point eye(RT_ZERO, RT_ZERO, view_distance), look_at(RT_ZERO, RT_ZERO, RT_ZERO);*/
	RTdouble view_distance = 500.;
	Point eye(0., 150., 150.), look_at(0, 150., -300.);
	infoPrint("Selected Camera: "+string("PinHole")+"!");
	pinhole_ptr->setEye(eye);
	infoPrint("Camera Eye: "+eye.to_rep()+"!");
	pinhole_ptr->setLookAt(look_at);
	infoPrint("Camera Look At Point: "+look_at.to_rep()+"!");
	pinhole_ptr->setViewPlaneDistance(view_distance);
	infoPrint("Distance between Camera and ViewPlane: "+to_string(view_distance)+"!");
	pinhole_ptr->uvwCompute();
	w.setCamera(pinhole_ptr);

	infoPrint("Adding ambient light(s)!");
	//Ambient * ambient = new Ambient;

	AmbientOccluder * ambient = new AmbientOccluder; // need debugging
	// the value of ambient
	ambient->setSampler(new MultiJittered(16));//num_samples * num_samples));
	infoPrint("Selected Sampler of Ambient Occluder: "+string("MultiJittered")+"!");
	infoPrint("Sample number of chosen Sampler: " + to_string(ambient->getSamplerPtr()->getNumSamples()) + "!");
	ambient->getSamplerPtr()->setNumSets(sampler_sets);
	infoPrint("Sample sets of chosen Sampler: " + to_string(ambient->getSamplerPtr()->getNumSets()) + "!");
	ambient->getSamplerPtr()->generateSamples();
	infoPrint("Generating Samples of the Sampler!");
	ambient->getSamplerPtr()->setupShuffledIndices();
	infoPrint("Shuffle Samples of the Sampler!");
	ambient->getSamplerPtr()->mapSamplesToHemisphere(RT_ONE);
	infoPrint("Try Mapping Samples onto the hemisphere!"); 
	ambient->scaleRadience(2. * RT_ONE);

	w.setAmbientOccluder(ambient);
	//w.setAmbientLight(ambient);

	//if(1) { 
	// point light
	PointLight * light_ptr = new PointLight;
	infoPrint("Adding point light(s)!");
	light_ptr->setLocation(Point(0, 299, -150));
	light_ptr->scaleRadience(3.0);
	light_ptr->setCoeff(0.00005);
	light_ptr->setColor(RGBColor(1,1,1));
	//}

	// plane
	if(1) {
		Point plane_p[5] = {
			Point(0, 0, 0), // bottom
			Point(-150, 0, 0), // left
			Point(150, 0, 0), // right
			Point(-150, 300, 0), // top
			Point(150, 0, -300) // back
		};

		RGBColor plane_color[5] = {
			COLOR_WHITE,
			COLOR_RED,
			COLOR_GREEN,
			COLOR_WHITE,
			COLOR_WHITE
		};

		Normal plane_n[5] = {
			Normal(0, 1, 0),
			Normal(1, 0, 0),
			Normal(-1, 0, 0),
			Normal(0, -1, 0),
			Normal(0, 0, 1),
		};

		for(int i = 0; i < 5; i++) {
			Phong * phong_ptr = new Phong;
			phong_ptr->set_ka(0.25);
			phong_ptr->set_kd(0.65);
			phong_ptr->set_ks(0.2);
			phong_ptr->set_exp(20);
			phong_ptr->set_cd(plane_color[i]);
			phong_ptr->set_cs(plane_color[i]);

			//for(int i = 0; i < 5; i++) {
			//Plane * plane = new Plane(Point(-300, 0, 0), Normal(1, 0, 0));
			Plane * plane = new Plane(plane_p[i], plane_n[i]);

			w.addObject(plane);
			w.objects[w.objects.size()-1]->setMaterial(phong_ptr);
			w.objects[w.objects.size()-1]->setColor(plane_color[i]);
			//}
			infoPrint("Adding a plane!");
		}
	}

	// polyhedron
	if(1) {
		Phong * phong_ptr = new Phong;
		phong_ptr->set_ka(0.25);
		phong_ptr->set_kd(0.65);
		phong_ptr->set_ks(0.2);
		phong_ptr->set_exp(5);
		phong_ptr->set_cd(RGBColor(0., 1., 1.));
		phong_ptr->set_cs(RGBColor(0., 1., 1.)); // specular color no use

		RTdouble length_edge = 100, offset = 0;
		Point vertex[8] = {
			Point(50, 0, -150),
			Point(74, 0, -132),
			Point(68, 0, -174),
			Point(92, 0, -156),
			Point(50, 100, -150),
			Point(74, 100, -132),
			Point(68, 100, -174),
			Point(92, 100, -156)
		};

		int pp_index[6][4] = {
			{0, 1, 3, 2},
			{0, 2, 6, 4},
			{0, 1, 5, 4},
			{1, 3, 7, 5},
			{2, 3, 7, 6},
			{4, 5, 7, 6},
		};

		for( int i = 0; i < 6; i++) {
			vector <Point> ps;
			for(int j = 0; j < 4; j++) {
				ps.push_back(vertex[pp_index[i][j]]);
			}
			Polygon * poly= new Polygon(ps);

			w.addObject(poly);
			w.objects[w.objects.size()-1]->setMaterial(phong_ptr);
			w.objects[w.objects.size()-1]->setColor(RGBColor(0., 1., 1.));
		}

		infoPrint("Adding a polyhedron!");
	}

	if(1) { // ball

		Phong * phong_ptr = new Phong;
		phong_ptr->set_ka(0.25);
		phong_ptr->set_kd(0.65);
		phong_ptr->set_ks(0.2);
		phong_ptr->set_exp(10);
		phong_ptr->set_cd(COLOR_WHITE);
		phong_ptr->set_cs(COLOR_WHITE);

		w.addObject(new Sphere(Point(-50,50,-150), 50));
		w.objects[w.objects.size()-1]->setMaterial(phong_ptr);
		w.objects[w.objects.size()-1]->setColor(COLOR_BLUE);
		infoPrint("Adding a sphere!");
	}

	w.addLight(light_ptr);
	w.generateVPLs(light_ptr, Normal(0, -1, 0));
	//w.lights.erase(w.lights.begin());
}

void buildCornell2(World &w) {

	infoPrint("Setting world params!");
	int res_h = 600, res_v = 600;
	RTdouble gamma_value = RT_ONE, pixel_size = RT_ONE;
	int num_samples = 4;
	int sampler_sets = 83;

	w.vp.setResH(res_h);
	w.vp.setResV(res_v);
	infoPrint("Resolution of view plane, Horizontal: " + to_string(w.vp.hRes) + " Vertical: "+ to_string(w.vp.hRes) + "!");

	w.vp.setPixelSize(pixel_size);
	infoPrint("Pixel size of view plane: " + to_string(pixel_size) + "!");
	w.vp.setGamma(gamma_value);
	infoPrint("Gamma value of view plane: " + to_string(gamma_value) + "!");

	//w.vp.setSampler(new MultiJittered(num_samples));
	w.vp.setSamples(num_samples);
	infoPrint("Selected Sampler of view plane: "+string(w.vp.num_samples==1?"Regular":"MultiJittered")+"!");
	infoPrint("Sample number of chosen Sampler: " + to_string(w.vp.sampler_ptr->getNumSamples()) + "!");
	w.vp.sampler_ptr->setNumSets(sampler_sets);
	infoPrint("Sample sets of chosen Sampler: " + to_string(w.vp.sampler_ptr->getNumSets()) + "!");
	w.vp.sampler_ptr->generateSamples();
	infoPrint("Generating Samples of the Sampler!");
	w.vp.sampler_ptr->setupShuffledIndices();
	infoPrint("Shuffle Samples of the Sampler!");
	w.vp.sampler_ptr->mapSamplesToUnitDisk();
	infoPrint("Try Mapping Samples onto the disk!");
	w.vp.sampler_ptr->mapSamplesToHemisphere(1.);
	infoPrint("Try Mapping Samples onto the hemisphere!");

	w.bg_color = COLOR_BLACK;
	infoPrint("Background color of the world: " + string("black") + "!");

	w.tracer_ptr = new RayCasting(&w);
	infoPrint("Ray tracer of the world: " + string("Ray Casting") + "!");

	PinHole * pinhole_ptr = new PinHole;
	/*RTdouble view_distance = 500.;
	Point eye(RT_ZERO, RT_ZERO, view_distance), look_at(RT_ZERO, RT_ZERO, RT_ZERO);*/
	RTdouble view_distance = 500.;
	Point eye(0., 150., 150.), look_at(0, 150., -300.);
	infoPrint("Selected Camera: "+string("PinHole")+"!");
	pinhole_ptr->setEye(eye);
	infoPrint("Camera Eye: "+eye.to_rep()+"!");
	pinhole_ptr->setLookAt(look_at);
	infoPrint("Camera Look At Point: "+look_at.to_rep()+"!");
	pinhole_ptr->setViewPlaneDistance(view_distance);
	infoPrint("Distance between Camera and ViewPlane: "+to_string(view_distance)+"!");
	pinhole_ptr->uvwCompute();
	w.setCamera(pinhole_ptr);

	infoPrint("Adding ambient light(s)!");
	//Ambient * ambient = new Ambient;

	AmbientOccluder * ambient = new AmbientOccluder; // need debugging
	// the value of ambient
	ambient->setSampler(new MultiJittered(16));//num_samples * num_samples));
	infoPrint("Selected Sampler of Ambient Occluder: "+string("MultiJittered")+"!");
	infoPrint("Sample number of chosen Sampler: " + to_string(ambient->getSamplerPtr()->getNumSamples()) + "!");
	ambient->getSamplerPtr()->setNumSets(sampler_sets);
	infoPrint("Sample sets of chosen Sampler: " + to_string(ambient->getSamplerPtr()->getNumSets()) + "!");
	ambient->getSamplerPtr()->generateSamples();
	infoPrint("Generating Samples of the Sampler!");
	ambient->getSamplerPtr()->setupShuffledIndices();
	infoPrint("Shuffle Samples of the Sampler!");
	ambient->getSamplerPtr()->mapSamplesToHemisphere(RT_ONE);
	infoPrint("Try Mapping Samples onto the hemisphere!"); 
	ambient->scaleRadience(2. * RT_ONE);

	w.setAmbientOccluder(ambient);
	//w.setAmbientLight(ambient);

	//if(1) { 
	// point light
	PointLight * light_ptr = new PointLight;
	infoPrint("Adding point light(s)!");
	light_ptr->setLocation(Point(0, 299, -150));
	light_ptr->scaleRadience(3.0);
	light_ptr->setCoeff(0.00005);
	light_ptr->setColor(RGBColor(1,1,1));
	//}

	// plane
	if(1) {
		Point plane_p[5] = {
			Point(0, 0, 0), // bottom
			Point(-150, 0, 0), // left
			Point(150, 0, 0), // right
			Point(-150, 300, 0), // top
			Point(150, 0, -300) // back
		};

		RGBColor plane_color[5] = {
			COLOR_RED,
			COLOR_BLUE,
			COLOR_GREEN,
			COLOR_WHITE,
			COLOR_WHITE
		};

		Normal plane_n[5] = {
			Normal(0, 1, 0),
			Normal(1, 0, 0),
			Normal(-1, 0, 0),
			Normal(0, -1, 0),
			Normal(0, 0, 1),
		};

		for(int i = 0; i < 1; i++) {
			Phong * phong_ptr = new Phong;
			phong_ptr->set_ka(0.25);
			phong_ptr->set_kd(0.65);
			phong_ptr->set_ks(0.2);
			phong_ptr->set_exp(20);
			phong_ptr->set_cd(plane_color[i]);
			phong_ptr->set_cs(plane_color[i]);

			//for(int i = 0; i < 5; i++) {
			//Plane * plane = new Plane(Point(-300, 0, 0), Normal(1, 0, 0));
			Plane * plane = new Plane(plane_p[i], plane_n[i]);

			w.addObject(plane);
			w.objects[w.objects.size()-1]->setMaterial(phong_ptr);
			w.objects[w.objects.size()-1]->setColor(plane_color[i]);
			//}
			infoPrint("Adding a plane!");
		}
	}

	// polyhedron
	if(1) {
		Phong * phong_ptr = new Phong;
		phong_ptr->set_ka(0.25);
		phong_ptr->set_kd(0.65);
		phong_ptr->set_ks(0.2);
		phong_ptr->set_exp(5);
		phong_ptr->set_cd(RGBColor(0., 0., 1.));
		phong_ptr->set_cs(RGBColor(0., 0., 1.)); // specular color no use

		RTdouble length_edge = 100, offset = 0;
		Point vertex[8] = {
			Point(50, 0, -150),
			Point(74, 0, -132),
			Point(68, 0, -174),
			Point(92, 0, -156),
			Point(50, 100, -150),
			Point(74, 100, -132),
			Point(68, 100, -174),
			Point(92, 100, -156)
		};

		int pp_index[6][4] = {
			{0, 1, 3, 2},
			{0, 2, 6, 4},
			{0, 1, 5, 4},
			{1, 3, 7, 5},
			{2, 3, 7, 6},
			{4, 5, 7, 6},
		};

		for( int i = 0; i < 6; i++) {
			vector <Point> ps;
			for(int j = 0; j < 4; j++) {
				ps.push_back(vertex[pp_index[i][j]]);
			}
			Polygon * poly= new Polygon(ps);

			w.addObject(poly);
			w.objects[w.objects.size()-1]->setMaterial(phong_ptr);
			w.objects[w.objects.size()-1]->setColor(RGBColor(0., 1., 1.));
		}

		infoPrint("Adding a polyhedron!");
	}

	if(1) { // ball

		Phong * phong_ptr = new Phong;
		phong_ptr->set_ka(0.25);
		phong_ptr->set_kd(0.65);
		phong_ptr->set_ks(0.2);
		phong_ptr->set_exp(10);
		phong_ptr->set_cd(COLOR_WHITE);
		phong_ptr->set_cs(COLOR_WHITE);

		w.addObject(new Sphere(Point(-50,50,-150), 50));
		w.objects[w.objects.size()-1]->setMaterial(phong_ptr);
		w.objects[w.objects.size()-1]->setColor(COLOR_BLUE);
		infoPrint("Adding a sphere!");
	}

	w.addLight(light_ptr);
	w.generateVPLs(light_ptr, Normal(0, -1, 0));
	//w.lights.erase(w.lights.begin());
}
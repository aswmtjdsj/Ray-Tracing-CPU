#ifndef BUILD_FUNCTIONS_H
#define BUILD_FUNCTIONS_H

#include "Normal.h"
#include "Constants.h"

#include "Sphere.h"
#include "Plane.h"
#include "Polygon.h"

//#include "MultipleObjects.h"
//#include "SingleSphere.h"

#include "Light.h"

#include "Matte.h"
#include "Phong.h"

#include "RayCasting.h"

#include "World.h"

#include "Random.h"

void buildSphere(World &);
void buildRandom(World &);
void buildAmbient(World &);
void buildCornell(World &);
void buildCornell2(World &);

#endif
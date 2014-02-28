#include "Emissive.h"
#include "Constants.h"

RGBColor Emissive::areaLightShade(ShadeRec &sr) {
	if( -sr.normal * sr.ray.d > 0.0) {
		return ls * ce;
	}
	else {
		return COLOR_BLACK;
	}
}
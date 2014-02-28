#include "Material.h"
#include "ShadeRec.h"
#include "Constants.h"

RGBColor Material::shade(ShadeRec &sr) {
	return COLOR_BLACK;
}

RGBColor Material::areaLightShade(ShadeRec &sr) {
	return COLOR_BLACK;
}

RGBColor Material::shadePath(ShadeRec &sr) {
	return COLOR_BLACK;
}

RGBColor Material::get_Le(ShadeRec &sr) const{
	return COLOR_BLACK;
}
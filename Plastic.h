#ifndef PLASTIC_H
#define PLASTIC_H

#include "Material.h"
#include "BRDF.h"

class Plastic: public Material {
	public:
		Plastic();
		~Plastic();

		void setAmbientBRDF(BRDF *);
		void setDiffuseBRDF(BRDF *);
		void setSpecularBRDF(BRDF *);

		virtual RGBColor shade(ShadeRec &);

	private:
		BRDF * ambientBRDF;
		BRDF * diffuseBRDF;
		BRDF * specularBRDF;
};

#endif

#include "GeometryObject.h"

GeometryObject::GeometryObject():shadows(true) {
}

GeometryObject::~GeometryObject() {
	cout << "Destructing Geometry Objects!" << endl;
	/*if(material != NULL) {
		delete material;
		material = NULL;
	}*/
}

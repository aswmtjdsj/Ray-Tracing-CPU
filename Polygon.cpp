#include "Polygon.h"
#include "Constants.h"
#include "Vector.h"
#include "Ray.h"
#include "ShadeRec.h"

const RTdouble Polygon::kEpsilon = RT_EPSILON;

Polygon::Polygon(): GeometryObject(), coplanar(true) {
	vertices.resize(0);
}

// I must make sure that the point are legal, so that they can construct a planar polygon
// but up till now, I don't want to implement such verification
// maybe including number verification and collinear verfication
// and I must make sure that the order of points are clockwise or counter-clockwise

Polygon::Polygon(const vector <Point> & points) {
	vertices = points;
}

Polygon::Polygon(const Point *pts, const int &num) {
	for(int i = 0; i < num; i++) {
		vertices.push_back(*pts);
		pts++;
	}
}

bool Polygon::getNormal(Normal &n) const {
	// the return value returns the status of verification of collinear test

	// collinear test first
	Vector a = vertices[1] - vertices[0],
		b = vertices[2] - vertices[1];
	n = a ^ b;

	if(n.length() < kEpsilon) {
		// collinear
		return false;
	}

	n = n.unit();
	return true;
}

bool Polygon::inPolygon(const Point &pt) const{
	// an unprecise way to prove this
	// a little fake
	// after I implement the line class, I would implement a more precise way

	RTdouble accum = RT_ZERO;
	int n = vertices.size();
	for(int i = 0; i < n; i++) {
		Vector a = (vertices[i] - pt), b = (vertices[(i+1)%n] - pt);
		accum += acos( a * b / a.length() / b.length());
	}

	// the loss in accuracy caused by acos func is too much
	if( fabs(2. * RT_PI - accum) < kEpsilon * 1000) {
		return true;
	}

	return false;
}

bool Polygon::hit(const Ray &ray, double &min_t, ShadeRec &sr) const {
	Normal n;

	if(!getNormal(n)) {
		return false;
	}

	Point p = vertices[0];
	double t = (p - ray.o) * n / (ray.d  * n);

	if(t > kEpsilon) {
		Point temp_pt = ray.o + t * ray.d;

		// you cannot use a non-cost func in a const func
		if(inPolygon(temp_pt)) {
			min_t = t;
			sr.normal = n;
			sr.local_hit_point = temp_pt;
			return true;
		}
		else {
			return false;
		}
	}
	else {
		return false;
	}

}

bool Polygon::shadowHit(const Ray &ray, RTdouble &min_t) const {

	if(!shadows) {
		return false;
	}

	Normal n;
	if(!getNormal(n)) {
		return false;
	}

	Point p = vertices[0];
	double t = (p - ray.o) * n / (ray.d  * n);

	if(t > kEpsilon) {
		Point temp_pt = ray.o + t * ray.d;

		if(inPolygon(temp_pt)) {
			min_t = t;
			return true;
		}
		else {
			return false;
		}

	}
	else {
		return false;
	}
}

/* deprecated */
RGBColor Polygon::getColor() const {
	return color;
}

void Polygon::setColor(const RGBColor &t_color) {
	color = t_color;
}
/* ---------- */

Material * Polygon::getMaterial() const {
	return material;
}

void Polygon::setMaterial(Material * mat) {
	material = mat;
}

void Polygon::print(const string &prompt) const {
	printf("Info of Polygon %s>\n", prompt.c_str());
	for(int i = 0; i != vertices.size(); i++) {
		string subPrompt = "Vertex #" + to_string(i);
		vertices[i].print(subPrompt);
	}
}

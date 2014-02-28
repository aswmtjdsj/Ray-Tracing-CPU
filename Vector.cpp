#include "Vector.h"
#include "Matrix.h"

// Constructor
Vector::Vector():Point() {

}

Vector::Vector(const RTdouble &t_v):
	Point(t_v) {
}

Vector::Vector(const RTdouble &t_x, const RTdouble &t_y, const RTdouble &t_z):
	Point(t_x, t_y, t_z) {

}

Vector::Vector(const Point &t_from, const Point &t_to):
	Point(t_to.getX()-t_from.getX(),
	t_to.getY()-t_from.getY(),
	t_to.getZ()-t_from.getZ()) {

}

// = operator
Vector & Vector::operator =(const Vector &t_v) {
	setX(t_v.getX());
	setY(t_v.getY());
	setZ(t_v.getZ());
	setW(t_v.getW());
	return *this;
}

// Copy Constructor
Vector::Vector(const Vector &t_v){
	*this=t_v;
}

// operators
Vector Vector::operator -() const{
	return Vector( -getX(), -getY(), -getZ());
}

Vector Vector::operator +(const Vector &t_v) const {
	return Vector(*this) += t_v; 
}

Vector & Vector::operator +=(const Vector &t_v) {
	setX(getX() + t_v.getX());
	setY(getY() + t_v.getY());
	setZ(getZ() + t_v.getZ());
	return *this;
}

Point Vector::operator +(const Point &t_p) const {
	// we do not recommend this style: v + p
	return Point(
		t_p.getX() + getX(),
		t_p.getY() + getY(),
		t_p.getZ() + getZ()
		);
}

Point operator +(const Point &t_p, const Vector &t_v) {
	// recommended
	return t_v + t_p;
}

Vector Vector::operator -(const Vector &t_v) const {
	return Vector(*this) -= t_v; 
}

Point operator -(const Point &t_p, const Vector &t_v) {
	return t_p + (-t_v);
}

Vector operator -(const Point &t_a, const Point &t_b) {
	return Vector(t_b, t_a);
}

Vector & Vector::operator -=(const Vector &t_v) {
	*this += -t_v;
	return *this;
}

Vector Vector::operator *(const RTdouble &scalar) const {
	return Vector(*this) *= scalar; 
	// we can not return a reference of local memory
}

Vector operator *(const RTdouble &scalar, const Vector &t_v) {
	return t_v * scalar;
}

Vector & Vector::operator *=(const RTdouble &scalar) {
	setX(getX() * scalar);
	setY(getY() * scalar);
	setZ(getZ() * scalar);
	return *this;
}

RTdouble Vector::operator *(const Vector &t_v) const {
	return getX()*t_v.getX() + getY()*t_v.getY() + getZ()*t_v.getZ();
}

Vector Vector::operator /(const RTdouble &scalar) const {
	return *this * (1. / scalar);
}

Vector & Vector::operator /=(const RTdouble &scalar) {
	*this = *this / scalar;
	return *this;
}

// vector product
Vector Vector::operator ^(const Vector &t_v) const {
	/*Matrix a(1, 4), b(4, 1);

	a.setValue(0, 0, getX());
	a.setValue(0, 1, getY());
	a.setValue(0, 2, getZ());
	a.setValue(0, 3, getW());
	
	b.setValue(0, 0, t_v.getX());
	b.setValue(1, 0, t_v.getY());
	b.setValue(2, 0, t_v.getZ());
	b.setValue(3, 0, t_v.getW()); 

	Matrix a_mul_b = a * b;*/
	// naive...
	// didn't do normalization
	return Vector(getY() * t_v.getZ() - t_v.getY() * getZ(),
		getZ() * t_v.getX() - t_v.getZ() * getX(),
		getX() * t_v.getY() - t_v.getX() * getY());
}

// normalization
void Vector::normalize(){ // / w
	setX(getX()/getW());
	setY(getY()/getW());
	setZ(getZ()/getW());
	setW(1.);
}

RTdouble Vector::length() const {
	return sqrt( getX()*getX() + getY()*getY() + getZ()*getZ());
}

Vector Vector::unit() const { // return unit vector
	return *this / length();
}

// point distance
RTdouble Point::distance(const Point &p) const{
	return (*this - p).length();
}

//
void Vector::print(const string &prompt) const {
	printf("Vector %s: (%.2lf, %.2lf, %.2lf, %.2lf)\n", prompt.c_str(), getX(), getY(), getZ(), getW());
}

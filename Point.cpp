#include "Point.h"
#include "Constants.h"

// Constructor
Point::Point():
    x(RT_ZERO), y(RT_ZERO), z(RT_ZERO), w(RT_ZERO) {

    }

Point::Point(const RTdouble &t_value):
    x(t_value), y(t_value), z(t_value), w(RT_ONE) {

    }

Point::Point(const RTdouble &t_x, const RTdouble &t_y, const RTdouble &t_z):
    x(t_x), y(t_y), z(t_z), w(RT_ONE) {

    }

// = operator
Point & Point::operator =(const Point &t_p) {
    setX(t_p.getX());
    setY(t_p.getY());
    setZ(t_p.getZ());
    setW(t_p.getW());
    return *this;
}

// Copy Constructor
Point::Point(const Point &t_p){
    *this=t_p;
}

// Destructor
Point::~Point() {
    // Default Desctrutor
}

// get
RTdouble Point::getX() const {
    return x;
}

RTdouble Point::getY() const {
    return y;
}

RTdouble Point::getZ() const {
    return z;
}

RTdouble Point::getW() const {
    return w;
}

// set
void Point::setX(RTdouble t_x) {
    x = t_x;
}

void Point::setY(RTdouble t_y) {
    y = t_y;
}

void Point::setZ(RTdouble t_z) {
    z = t_z;
}

void Point::setW(RTdouble t_w) {
    w = t_w;
}

// normalization
void Point::normalize(){ // / w
    setX(getX()/getW());
    setY(getY()/getW());
    setZ(getZ()/getW());
    setW(1.);
}

// print
void Point::print(const string &prompt) const {
    printf("Point %s: (%.2lf, %.2lf, %.2lf, %.2lf)\n", prompt.c_str(), getX(), getY(), getZ(), getW());
}

string Point::to_rep() const {
	return "(" + to_string(getX()) + ", " + to_string(getY()) + ", " + to_string(getZ()) + ", " + to_string(getW()) + ")";
}
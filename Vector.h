#ifndef VECTOR_H
#define VECTOR_H
#include "common.h"
#include "Point.h"

class Vector: public Point {
    public:
        // Constructor
        Vector();
        Vector(const RTdouble &);
        Vector(const RTdouble &, const RTdouble &, const RTdouble &);
        Vector(const Point &, const Point &);
        
        // = operator
        Vector & operator =(const Vector &);

        // Copy Constructor
        Vector(const Vector &);

        // operators

		// add
        Vector operator +(const Vector &) const;
        Vector & operator +=(const Vector &);
        Point operator +(const Point &) const;
        friend Point operator +(const Point &, const Vector &);

		// subtract
        Vector operator -() const;
        Vector operator -(const Vector &) const;
        Vector & operator -=(const Vector &);

		// multiply (scale)
        Vector operator *(const RTdouble &) const;
        friend Vector operator *(const RTdouble &, const Vector &);
        Vector & operator *=(const RTdouble &);

		// divide (scale)
        Vector operator /(const RTdouble &) const;
        Vector & operator /=(const RTdouble &);

		// scalar product 
        RTdouble operator *(const Vector &) const;

        // vector product
        Vector operator ^(const Vector &) const;

        // normalization
        void normalize(); // / w
        Vector unit() const; // return unit vector

		// length
		RTdouble length() const;

        // instantiation
        void print(const string &) const;
};

Point operator -(const Point &, const Vector &);
Vector operator -(const Point&, const Point &);

#endif

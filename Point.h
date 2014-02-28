#ifndef POINT_H
#define POINT_H

#include "common.h"

class Point: public Geometry {
    public:
        // Constructor
        Point();
        Point(const RTdouble &);
        Point(const RTdouble &, const RTdouble &, const RTdouble &);

        // = operator
        Point & operator =(const Point &);
        
        // Copy Constructor
        Point(const Point &);

        // Destructor
        ~Point();

        // Achieve Value
        RTdouble getX() const;
        RTdouble getY() const;
        RTdouble getZ() const;
        RTdouble getW() const;

        // normalization
        void normalize(); // / w

        // print, instantiation of virtual function of base class
        void print(const string &) const;
		string to_rep() const;

		// distance between 2 points
		RTdouble distance(const Point &) const;

        // Set Value
        void setX(RTdouble);
        void setY(RTdouble);
        void setZ(RTdouble);
        void setW(RTdouble);

    private:
        RTdouble x, y, z, w;
};

#endif

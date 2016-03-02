// Point header file
// Khen Cruzat - sc13kvc - 200760716

#ifndef POINT_H
#define POINT_H

#include <ostream>

class Vector;					// forward declaration

class Point
{
	public:
		float x, y, z, w;							// coordinates
		
		float& operator [] (int);					// index operator
		Point& operator = (Point);					// assignment operator
		bool operator == (Point);					// equality operator
		bool operator != (Point);					// not equal operator
		Point operator + (Vector);					// point+vector
		Point operator - (Vector);					// point-vector
		Vector operator - (Point);					// point-point

		Vector normalVector(Point);			// computes normal using 2 points
		float normalC(Point);				// computes the c of the normal
		void normalForm(Point);				// displays line in normal form
		int pointSide(Point, Point);		// displays the side of the point
		void parametricForm(Point);			// displays parametric form

		Point();									  		// default constructor
		Point(float X, float Y, float Z, float W = 1.0);	// initializing constructor

};

std::ostream& operator << (std::ostream&, Point);	// formats the point print
#endif
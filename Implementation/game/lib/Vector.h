// Vector header file
// Khen Cruzat - sc13kvc - 200760716

#ifndef VECTOR_H
#define VECTOR_H

#include "Point.h"

#include <ostream>

class Vector
{

	public:
		float x, y, z, w;					// coordinates

		float& operator [] (int);			// index operator
		Vector& operator = (Vector);		// assignment operator
		Vector operator - ();				// unary minus
		Vector operator + (Vector);			// vector addition
		Vector operator + (Point);			// vector+point
		Vector operator - (Vector);			// vector subtraction
		Vector operator * (float);			// scalar multiplication
		Vector operator / (float);			// scalar divison

		
		float dotProduct(Vector);			// dot product
		Vector crossProduct(Vector);		// cross product
		float vLength();					// computes length of vector
		float angle(Vector);				// angle between 2 vectors
		Vector getUnitVector(Vector);
		int checkWidth();					// for formatting the output
		
	Vector();									// default constructor
	Vector(float X, float Y, float Z, float W = 0); // initializing constructor

};
std::ostream& operator << (std::ostream&, Vector);	// formats vector printing
#endif
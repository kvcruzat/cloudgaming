// Matrix header file
// Khen Cruzat - sc13kvc - 200760716

#ifndef MATRIX_H
#define MATRIX_H

#include "Vector.h"
#include "Point.h"
#include <ostream>

class Matrix
{
	public:
		float coords[4][4];				// treats each row as a vector

		Vector operator [] (int);		// returns a row as a vector
		Vector column (int);			// returns a column as a vector
		Matrix operator + (Matrix);		// addition		
		Matrix operator * (Matrix);		// matrix multiplication
		Vector operator * (Vector);		// matrix*vector
		Point operator * (Point);		// matrix*point
		Matrix transpose();				// returns transposed matrix

	Matrix();						// default constructor
	static Matrix Identity();		// returns identity matrix
	static Matrix xRotation(float);
	static Matrix yRotation(float);
	static Matrix zRotation(float);	

};

std::ostream& operator << (std::ostream&, Matrix); // formats matrix print
#endif
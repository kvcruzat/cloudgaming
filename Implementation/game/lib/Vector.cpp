// Vector implementation
// Khen Cruzat - sc13kvc - 200760716

#include "Vector.h"

#include <iostream>
#include <iomanip>
#include <stdio.h>
#include <cmath>

Vector::Vector()					// default constructor
{
	x = 0; y = 0; z = 0; w = 0;		// set to default values
}

Vector::Vector(float X, float Y, float Z, float W) // initializing constructor
{
	x = X, y = Y; z = Z; w = W;					// copy the input values
}

int Vector::checkWidth()	// checks the maximum width of each value in vector
{
	Vector v = *this;
	int maxWidth = 1;
	char* str = new char[10];
	for (int i = 0; i < 4; ++i)		// loops through vector to find longest value
	{
		sprintf(str, "%.4g", v[i] );
		int strLength = std::string(str).length();
		if ( strLength > maxWidth)
		{
			maxWidth = strLength;
		}
	}
	return maxWidth;		// returns max width of value
}

std::ostream& operator << (std::ostream& ostr, Vector v)	// formats Vector print
{	
	int width = v.checkWidth();
	ostr << "| " << std::setw(width) << v.x << " |\n| " << std::setw(width) << v.y << " |\n| "
			<< std::setw(width) << v.z << " |\n| " << std::setw(width) << v.w << " |";
	return ostr;
}

float& Vector::operator[] (int i)				// index operator
{
	switch(i)
	{
		case 0: return x;
		case 1: return y;
		case 2: return z;
		case 3: return w;
		default:
			std::cout << "Error: Enter valid index from 0 to 3";
			return x;
	}
}

Vector& Vector::operator= (Vector other)		// assignment operator
{
	x = other.x;
	y = other.y;
	z = other.z;
	w = other.w;
	return *this;
}

Vector Vector::operator - ()				// unary minus
{
	Vector v;
	v.x = -x;
	v.y = -y;
	v.z = -z;
	v.w = -w;
	return v;
}

Vector Vector::operator + (Vector other) // addition(Vector+Vector=Vector)
{
	Vector v;
	v.x = x + other.x;
	v.y = y + other.y;
	v.z = z + other.z;
	v.w = w + other.w;
	return v;
}


Vector Vector::operator - (Vector other)  // subtraction(Vector-Vector=Vector)
{
	Vector v;
	v.x = x - other.x;
	v.y = y - other.y;
	v.z = z - other.z;
	v.w = w - other.w;
	return v;
}

Vector Vector::operator * (float s)	// scalar multiplier(Vector*float=Vector)
{
	Vector v;
	v.x = x * s;
	v.y = y * s;
	v.z = z * s;
	v.w = w * s;
	return v;
}


Vector Vector::operator / (float s)	// scalar division(Vector/float=Vector)
{
	Vector v;
	v.x = x / s;
	v.y = y / s;
	v.z = z / s;
	return v;
}

Vector Vector::operator + (Point p)	// addition (Vector+Point=Vector)
{
	Vector v = *this;
	Vector w;
	for ( int i = 0; i < 4; ++i)
	{
		w[i] = v[i] + p[i];
	}
	return w;
}

float Vector::dotProduct (Vector other)	// dot product
{
	return x*other.x + y*other.y + z*other.z + w*other.w;
}

Vector Vector::crossProduct (Vector other)	// cross product
{
	Vector v;
	v.x = (y*other.z) - (z*other.y);
	v.y = (z*other.x) - (x*other.z);
	v.z = (x*other.y) - (y*other.x);
	return v;
}

float Vector::vLength()			// magnitude of vector
{
	return sqrt(x*x + y*y + z*z + w*w);
}

float Vector::angle(Vector other)	// angle between 2 vectors in degrees
{
	float dot = this->dotProduct(other);
	float angle = acos(dot / (this->vLength()*other.vLength()) );
	angle = angle * (180/M_PI);		// converts angle from radians to degrees
  return angle;
}

Vector Vector::getUnitVector(Vector v)
{
    return (v / v.vLength());
}
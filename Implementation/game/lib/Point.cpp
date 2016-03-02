// Point implementation
// Khen Cruzat - sc13kvc - 200760716

#include "Point.h"
#include "Vector.h"

#include <iostream>
#include <iomanip>
#include <stdio.h>

Point::Point()					// default constructor
{
	x = 0; y = 0; z = 0; w = 1;	// set to default values
}

Point::Point(float X, float Y, float Z, float W)	// initializing constructor
{
	x = X, y = Y; z = Z; w = W;						// copy the input values
}

std::ostream& operator << (std::ostream& ostr, Point p)	// formats Point print
{
	ostr << "(" << p.x << ", " << p.y << ", " << p.z << ", " << p.w << ")";
	return ostr;
}

float& Point::operator[] (int i)	// index operator
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

Point& Point::operator= (Point other)	// assignment operator
{
	x = other.x;
	y = other.y;
	z = other.z;
	w = other.w;
	return *this;
}

bool Point::operator == (Point other)
{
	return (x == other.x &&
            y == other.y &&
            z == other.z &&
            w == other.w);
}

bool Point::operator != (Point other)
{
	return !(*this == other);
}


Point Point::operator + (Vector v) 		// addition (Point+Vector=Point)
{
	Point p = *this;
	Point q;
	for ( int i = 0; i < 4; ++i)
	{
		q[i] = p[i] + v[i];
	}
	return q;
}

Point Point::operator - (Vector v)		// subtraction (Point-Vector=Point)
{
	Point p = *this;
	Point q;
	for ( int i = 0; i < 4; ++i)
	{
		q[i] = p[i] - v[i];
	}
	return q;
}

Vector Point::operator - (Point head)	// subtraction (Point-Point=Vector)
{
	Point tail = *this;
	Vector v;
	for (int i = 0; i < 4; ++i)
	{
		v[i] = tail[i] - head[i];
	}
	return v;
}

Vector Point::normalVector(Point q)	// returns normal vector of two points
{
	Point p = *this;
	Vector v = p-q;
	float m = v[1]/v[0];		// gradient of line
	Vector normalV (-m,1,0);

	return normalV;
}

float Point::normalC(Point q)	// returns c value of normal form
{
	Point p = *this;
	Vector v = p-q;
	float m = v[1]/v[0];
	float c = p[1] - m*p[0];

	return c;
}

void Point::normalForm(Point q)	// displays line between two points in normal form
{
	Point p = *this;
	Vector normalV = p.normalVector(q);
	float c = p.normalC(q);
	int width = normalV.checkWidth();
	std::cout << "| " << std::setw(width) << normalV[0] << " || x |" << std::endl;
	std::cout << "| " << std::setw(width) << normalV[1] << " || y | = " << c
				<< std::endl;
}

int Point::pointSide(Point p, Point q)	// returns the side of a point
{
	Point r = *this;
	Vector normalV = p.normalVector(q);
	float c = p.normalC(q);
	Vector rV (r[0],r[1],0);
	float norm = (normalV.dotProduct(rV))-c;		// uses n.p-c

	if (norm > 0)
	{
		std::cout << "The point is in the direction of the normal" << std::endl;
		return 1;
	}
	else if (norm == 0)
	{
		std::cout << "The point is on the line" << std::endl;
		return 0;
	}
	else
	{
		std::cout << "The point is in the direction away from the normal" << std::endl;
		return -1;
	}
}

void Point::parametricForm (Point q)	// outputs parametric form of a line
{
	Point p = *this;
	Vector v = p-q;
	Vector pV (p[0],p[1],p[2]);
	int pwidth = pV.checkWidth();
	int vwidth = v.checkWidth();
	std::cout << "| x(t) |   | " << std::setw(pwidth) << pV[0] << " |   | "
				<< std::setw(vwidth) << v[0] << " |" << std::endl;
	std::cout << "| y(t) | = | " << std::setw(pwidth) << pV[1] << " | + | "
				<< std::setw(vwidth) << v[1] << " | t" << std::endl; 
}
// Matrix implementation
// Khen Cruzat - sc13kvc - 200760716

#include "Matrix.h"
#include "Vector.h"
#include "Point.h"

#include <ostream>
#include <iomanip>
#include <math.h>

#define PI 3.14159265

Matrix::Matrix()						// default constructor
{
	for (int i = 0; i < 4; ++i)
	{
		for (int j = 0; j < 4; ++j)
		{
			coords[i][j] = 0;			// sets all values to 0
		}
	}
}

Matrix Matrix::Identity()			// returns identity matrix
{
	Matrix I;
	I.coords[0][0] = 1;
	I.coords[1][1] = 1;
	I.coords[2][2] = 1;
	I.coords[3][3] = 1;
	return I;
}

std::ostream& operator << (std::ostream& ostr, Matrix m)	// formats matrix output
{
	int width1 = m.column(0).checkWidth();		// finds max width of each column
	int width2 = m.column(1).checkWidth();
	int width3 = m.column(2).checkWidth();
	int width4 = m.column(3).checkWidth();

	for (int i = 0; i < 4; ++i)			// sets appropriate width for each value
	{
		ostr << "| " << std::setw(width1) << m[i][0] << " "  << std::setw(width2) << m[i][1]
				<< " " << std::setw(width3) << m[i][2] << " " << std::setw(width4) << 
				m[i][3] << " |" << std::endl;
	}
	return ostr;
}

Vector Matrix::operator[](int i)	// index operator for row of matrix
{
	return Vector(coords[i][0], coords[i][1], coords[i][2], coords[i][3]);
}

Vector Matrix::column(int j)		// returns a column as a vector
{
	return Vector(coords[0][j], coords[1][j], coords[2][j], coords[3][j]);
}

Matrix Matrix::operator + (Matrix other)	// matrix addition
{
	Matrix resultMatrix;
	for (int i = 0; i < 4; ++i)
	{
		for (int j = 0; j < 4; ++j)
		{
			resultMatrix.coords[i][j] = coords[i][j] + other[i][j];
		}
	}
	return resultMatrix;
}

Vector Matrix::operator * (Vector v)	// matrix*vector=vector
{
	Matrix m = *this;
	Vector w;
	for (int i = 0; i < 4; ++i)
	{
		w[i] = m[i].dotProduct(v);
	}
	return w;
}

Matrix Matrix::operator * (Matrix other)	// matrix multiplication
{
	Matrix resultMatrix;
	for (int i = 0; i < 4; ++i)
	{
		for (int j = 0; j < 4; ++j)
		{
			resultMatrix.coords[i][j] = 0;
			for (int k = 0; k < 4; ++k)
			{
				resultMatrix.coords[i][j] += coords[i][k] * other[k][j];
			}
		}
	}
	return resultMatrix;
}

Point Matrix::operator * (Point p)		// matrix*point=point
{
	Matrix m = *this;
	Point q (0,0,0,0);
	for (int i = 0; i < 4; ++i)
	{
		for (int j = 0; j < 4; ++j)
		{
			q[i] += m[i][j] * p[j];
		}
	}
	return q;
}

Matrix Matrix::transpose()		// function to transpose the matrix
{
	Matrix m = *this;
	for (int i = 0; i < 4; ++i)
	{
		for (int j = 0; j < 4; ++j)
		{
			m.coords[i][j] = coords[j][i];	// matrix value [i,j] becomes [j,i]
		}
	}
	return m;

}

Matrix Matrix::xRotation(float angle){
	Matrix x;
	angle = angle * ( PI / 180);
	x.coords[0][0] = 1;
	x.coords[1][1] = cos(angle);
	x.coords[1][2] = -sin(angle);
	x.coords[2][1] = sin(angle);
	x.coords[2][2] = cos(angle);
	x.coords[3][3] = 1;
	return x;
}

Matrix Matrix::yRotation(float angle){
	Matrix y;
	angle = angle * ( PI / 180);
	y.coords[0][0] = cos(angle);
	y.coords[0][2] = sin(angle);
	y.coords[1][1] = 1;
	y.coords[2][0] = -sin(angle);
	y.coords[2][2] = cos(angle);
	y.coords[3][3] = 1;
	return y;
}

Matrix Matrix::zRotation(float angle){
	Matrix z;
	angle = angle * ( PI / 180);
	z.coords[0][0] = cos(angle);
	z.coords[0][1] = -sin(angle);
	z.coords[1][0] = sin(angle);
	z.coords[1][1] = cos(angle);
	z.coords[2][2] = 1;
	z.coords[3][3] = 1;
	return z;
}
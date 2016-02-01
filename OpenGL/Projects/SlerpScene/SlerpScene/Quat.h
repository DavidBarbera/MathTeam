/****************************************************************************

Class Quaternion to implement all the functions related with that

-----------------------------------------------------------------------

01/02/2016	David Barbera
			Javier de la Osa

****************************************************************************/


#pragma once
#include <cmath>
#include <cstdlib>
#include <sstream>
#include <iostream>
#include <fstream>
#include "Matrices.h"
#include "Vectors.h"

#define PI 3.14159265


class Quat {

public:

	// Quaternion elements.
	float X; 
	float Y;
	float Z;
	float W; 

	/////////////////////////////// Definition of Headers ////////////////////////

	// 1. Default Constructor
	Quat() : X(0.0f), Y(0.0f), Z(0.0f), W(1.0f) {};

	// 2. Constructor which converts a matrix to a quaternion
	Quat(const Matrix4& mat);

	// 3. Constructor which converts euler angles (radians) to a quaternion
	Quat(float x, float y, float z);

	// 4. Constructor which converts euler angles (radians) to a quaternion
	Quat(const Vector3& vec);

	// 5. Assignment operator (quaternion = quaternion)
	inline Quat& operator=(const Quat& other);

	// 6. Add operator
	inline Quat operator+(const Quat& other) const;

	// 7. Multiplication operator
	inline Quat operator*(const Quat& other) const;

	// 8. Sets new quaternion based on euler angles (radians)
	inline Quat& set(float x, float y, float z);

	// 9. Creates a matrix from this quaternion
	inline Matrix4 getMatrix() const;


	/////////////////////////////// Definition of Headers ////////////////////////
};

// 2. Constructor which converts a matrix to a quaternion
inline Quat::Quat(const Matrix4& mat)
{
	(*this) = mat;
}

// 3. Constructor which converts euler angles to a quaternion from three numbers
inline Quat::Quat(float x, float y, float z)
{
	set(x, y, z);
}


// 4. Constructor which converts euler angles to a quaternion from a Vector3
inline Quat::Quat(const Vector3& vec)
{
	set(vec.x, vec.y, vec.z);
}

// 5. Assignment operator (quaternion = quaternion)
inline Quat& Quat::operator=(const Quat& other)
{
	X = other.X;
	Y = other.Y;
	Z = other.Z;
	W = other.W;
	return *this;
}

// 6. Add operator
inline Quat Quat::operator+(const Quat& b) const
{
	Quat tmp;

	tmp.W = W + b.W;
	tmp.X = X + b.X;
	tmp.Y = Y + b.Y;
	tmp.Z = Z + b.Z;

	return tmp;
}

// 7. Multiplication operator
inline Quat Quat::operator*(const Quat& other) const
{
	Quat tmp;

	tmp.W = (other.W * W) - (other.X * X) - (other.Y * Y) - (other.Z * Z);
	tmp.X = (other.W * X) + (other.X * W) + (other.Y * Z) - (other.Z * Y);
	tmp.Y = (other.W * Y) + (other.Y * W) + (other.Z * X) - (other.X * Z);
	tmp.Z = (other.W * Z) + (other.Z * W) + (other.X * Y) - (other.Y * X);

	return tmp;
}

// 8. Sets new quaternion based on euler angles
inline Quat& Quat::set(float x, float y, float z)
{
	return set(x, y , z);
}

// 9. Creates a matrix from this quaternion
inline Matrix4 Quat::getMatrix() const
{
	Matrix4 dest;

	dest[0] = W*W + X*X - Y*Y - Z*Z;
	dest[1] = 2.0f*X*Y + 2.0f*Z*W;
	dest[2] = 2.0f*X*Z - 2.0f*Y*W;
	dest[3] = 0.0f;

	dest[4] = 2.0f*X*Y - 2.0f*Z*W;
	dest[5] = W*W - X*X + Y*Y- Z*Z;
	dest[6] = 2.0f*Z*Y + 2.0f*X*W;
	dest[7] = 0.0f;

	dest[8] = 2.0f*X*Z + 2.0f*Y*W;
	dest[9] = 2.0f*Z*Y - 2.0f*X*W;
	dest[10] = W*W - X*X - Y*Y + Z*Z;
	dest[11] = 0.0f;

	dest[12] = 0.0f;
	dest[13] = 0.0f;
	dest[14] = 0.0f;
	dest[15] = 1.f;

	return dest;
}


//RotationMatrix quaternionToRotationMatrix(Quaternion q)
//{
//	float w, x, y, z;
//	float m[16];
//
//	w = q.getW(); x = q.getX(); y = q.getY(); z = q.getZ();
//
//	m[0] = w*w + x*x - y*y - z*z;
//	m[1] = 2.0*x*y + 2.0*w*z;
//	m[2] = 2.0*x*z - 2.0*y*w;
//	m[3] = 0.0;
//
//	m[4] = 2.0*x*y - 2.0*w*z;
//	m[5] = w*w - x*x + y*y - z*z;
//	m[6] = 2.0*y*z + 2.0*w*x;
//	m[7] = 0.0;
//
//	m[8] = 2.0*x*z + 2.0*w*y;
//	m[9] = 2.0*y*z - 2.0*w*x;
//	m[10] = w*w - x*x - y*y + z*z;
//	m[11] = 0.0;
//
//	m[12] = 0.0;
//	m[13] = 0.0;
//	m[14] = 0.0;
//	m[15] = 1.0;
//
//	return *new RotationMatrix(m);
//}
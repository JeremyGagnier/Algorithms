#include <cmath>
#include "Vector.h"

Vector::Vector(): 
	x(0),
	y(0),
	z(0)
{
}

Vector::Vector(double x, double y):
	x(x),
	y(y),
	z(0)
{
}

Vector::Vector(double x, double y, double z):
	x(x),
	y(y),
	z(z)
{
}

Vector& Vector::operator+(const Vector& other)
{
	return Vector(x + other.x, y + other.y, z + other.z);
}
Vector& Vector::operator+=(const Vector& rhs)
{
	x += rhs.x;
	y += rhs.y;
	z += rhs.z;
	return *this;
}

Vector& Vector::operator-(const Vector& other)
{
	return Vector(x - other.x, y - other.y, z - other.z);
}
Vector& Vector::operator-=(const Vector& rhs)
{
	x -= rhs.x;
	y -= rhs.y;
	z -= rhs.z;
	return *this;
}

Vector& Vector::operator*(const double& other)
{
	return Vector(x * other, y * other, z * other);
}
Vector& Vector::operator*=(const double& rhs)
{
	x *= rhs;
	y *= rhs;
	z *= rhs;
	return *this;
}

Vector& Vector::operator*(const Vector& other)
{
	return Vector(x * other.x, y * other.y, z * other.z);
}
Vector& Vector::operator*=(const Vector& rhs)
{
	x *= rhs.x;
	y *= rhs.y;
	z *= rhs.z;
	return *this;
}

Vector& Vector::operator/(const double& other)
{
	return Vector(x / other, y / other, z / other);
}
Vector& Vector::operator/=(const double& rhs)
{
	x /= rhs;
	y /= rhs;
	z /= rhs;
	return *this;
}

Vector& Vector::operator/(const Vector& other)
{
	return Vector(x / other.x, y / other.y, z / other.z);
}
Vector& Vector::operator/=(const Vector& rhs)
{
	x /= rhs.x;
	y /= rhs.y;
	z /= rhs.z;
	return *this;
}

bool Vector::operator==(const Vector& rhs)
{
	return (x == rhs.x && y == rhs.y && z == rhs.z);
}

double Vector::Length()
{
	return sqrt(x*x + y*y + z*z);
}

double Vector::LengthSqr()
{
	return x*x + y*y + z*z;
}

Vector Vector::Normalized()
{
	return *this / (this->Length());
}

void Vector::Normalize()
{
	*this /= this->Length();
}

double Vector::Dot(Vector& other)
{
	return x*other.x + y*other.y + z*other.z;
}

Vector Vector::Crossed(Vector& other)
{
	return Vector(y * other.z, z * other.x, x * other.y);
}



Line::Line():
	mPosition(Vector()),
	mDirection(Vector())
{
}

Line::Line(Vector position, Vector direction):
	mPosition(position),
	mDirection(direction)
{
}

double Line::Length()
{
	return mDirection.Length();
}

double Line::LengthSqr()
{
	return mDirection.LengthSqr();
}



Sphere::Sphere():
	mPosition(Vector()),
	mRadius(0)
{
}

Sphere::Sphere(Vector position, double radius):
	mPosition(position),
	mRadius(radius)
{
}

double Sphere::Perimeter()
{
	return 2*PI*mRadius;
}

double Sphere::Area()
{
	return PI*mRadius*mRadius;
}

double Sphere::SurfaceArea()
{
	return 4*PI*mRadius*mRadius;
}

double Sphere::Volume()
{
	return 4.0/3.0*PI*mRadius*mRadius*mRadius;
}



Box::Box():
	mPosition(Vector()),
	mSides(Vector())
{
}

Box::Box(Vector position, Vector sides):
	mPosition(position),
	mSides(sides)
{
}

double Box::Perimeter()
{
	return mSides.x * 2 + mSides.y * 2;
}

double Box::Area()
{
	return mSides.x*mSides.y;
}

double Box::SurfaceArea()
{
	return 2*mSides.x*mSides.y + 2*mSides.y*mSides.z + 2*mSides.x*mSides.z;
}

double Box::Volume()
{
	return mSides.x*mSides.y*mSides.z;
}

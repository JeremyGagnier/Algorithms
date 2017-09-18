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
	position(Vector()),
	direction(Vector())
{
}

Line::Line(Vector position, Vector direction):
	position(position),
	direction(direction)
{
}

double Line::Length()
{
	return direction.Length();
}

double Line::LengthSqr()
{
	return direction.LengthSqr();
}



Sphere::Sphere():
	position(Vector()),
	radius(0)
{
}

Sphere::Sphere(Vector position, double radius):
	position(position),
	radius(radius)
{
}

double Sphere::Perimeter()
{
	return 2.0 * PI * radius;
}

double Sphere::Area()
{
	return PI * radius * radius;
}

double Sphere::SurfaceArea()
{
	return 4 * PI * radius * radius;
}

double Sphere::Volume()
{
	return 4.0 / 3.0 * PI * radius * radius * radius;
}



Box::Box():
	position(Vector()),
	sides(Vector())
{
}

Box::Box(Vector position, Vector sides):
	position(position),
	sides(sides)
{
}

double Box::Perimeter()
{
	return 2.0 * sides.x + 2.0 * sides.y;
}

double Box::Area()
{
	return sides.x * sides.y;
}

double Box::SurfaceArea()
{
	return 2.0 * sides.x * sides.y + 2.0 * sides.y * sides.z + 2.0 * sides.x * sides.z;
}

double Box::Volume()
{
	return sides.x * sides.y * sides.z;
}

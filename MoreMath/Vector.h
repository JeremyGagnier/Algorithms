#pragma once

const double PI = 3.14159265359;

class Vector
{
public:
	Vector();
	Vector(double x, double y);
	Vector(double x, double y, double z);
	double Length();
	double LengthSqr();
	Vector Normalized();
	void Normalize();
	double Dot(Vector& other);
	Vector Crossed(Vector& other);
	void Cross(Vector& other);
	
	Vector& operator+(const Vector& other);
	Vector& operator+=(const Vector& rhs);
	Vector& operator-(const Vector& other);
	Vector& operator-=(const Vector& rhs);
	Vector& operator*(const double& other);
	Vector& operator*(const Vector& other);
	Vector& operator*=(const double& rhs);
	Vector& operator*=(const Vector& rhs);
	Vector& operator/(const double& other);
	Vector& operator/(const Vector& other);
	Vector& operator/=(const double& rhs);
	Vector& operator/=(const Vector& rhs);
	bool operator==(const Vector& rhs);

	double x;
	double y;
	double z;
};

class Line
{
public:
	Line();
	Line(Vector position, Vector direction);
	double Length();
	double LengthSqr();

	Vector mPosition;
	Vector mDirection;
};

class Sphere
{
public:
	// The sphere doubles as a circle
	Sphere();
	Sphere(Vector position, double radius);

	double Perimeter();		// circles only
	double Area();			// circles only
	double SurfaceArea();	// spheres only
	double Volume();		// spheres only

	Vector mPosition;
	double mRadius;
};

class Box
{
public:
	// The box (rectangular prism) doubles as a rectangle
	Box();
	Box(Vector position, Vector sides);

	double Perimeter();		// rectangles only
	double Area();			// rectangles only
	double SurfaceArea();	// boxes only
	double Volume();		// boxes only

	Vector mPosition;
	Vector mSides;
};
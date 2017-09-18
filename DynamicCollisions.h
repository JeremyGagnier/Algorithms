#pragma once
#include <cmath>
#include "Vector.h"
#include "StaticCollisions.cpp"

bool DynamicPointToPoint(Vector p1, Vector p2, Vector v1, Vector v2);
bool DynamicPointToLine(Vector p, Line l, Vector v1, Vector v2);
bool DynamicPointToCircle(Vector p, Sphere s, Vector v1, Vector v2);
bool DynamicPointToRect(Vector p, Box b, Vector v1, Vector v2);

bool DynamicLineToLine(Line l1, Line l2, Vector v1, Vector v2);
bool DynamicLineToCircle(Line l, Sphere s, Vector v1, Vector v2);
bool DynamicLineToRect(Line l, Box b, Vector v1, Vector v2);

bool DynamicCircleToCircle(Sphere s1, Sphere s2, Vector v1, Vector v2);
bool DynamicCircleToRect(Sphere s, Box b, Vector v1, Vector v2);

bool DynamicRectToRect(Box b1, Box b2, Vector v1, Vector v2);

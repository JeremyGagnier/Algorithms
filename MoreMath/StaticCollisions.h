#pragma once
#include <cmath>
#include "Vector.h"

bool StaticPointToPoint(Vector p1, Vector p2);
bool StaticPointToLine(Vector p, Line l);
bool StaticPointToCircle(Vector p, Sphere s);
bool StaticPointToRect(Vector p, Box b);

bool StaticLineToLine(Line l1, Line l2);
bool StaticLineToCircle(Line l, Sphere s);
bool StaticLineToRect(Line l, Box b);

bool StaticCircleToCircle(Sphere s1, Sphere s2);
bool StaticCircleToRect(Sphere c, Box b);

bool StaticRectToRect(Box b1, Box b2);

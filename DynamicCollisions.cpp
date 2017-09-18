#include "DynamicCollisions.h"

// Always 17 computations.
bool DynamicPointToPoint(Vector p1, Vector p2, Vector v1, Vector v2)
{
	double vdx = v1.x - v2.x;
	double vdy = v1.y - v2.y;
	double m = (p2.x - p1.x) * vdy;
	double dirMul = vdx * vdy;
	double absM = abs(m);
	return (m == (p2.y - p1.y) * vdx)) & ((m < 0.0) == (dirMul < 0.0)) & (0.0 <= absM) & (absM <= abs(dirMul));
}

// Always 2 computations plus StaticLineToLine.
bool DynamicPointToLine(Vector p, Line l, Vector v1, Vector v2)
{
	double vdx = v1.x - v2.x;
	double vdy = v1.y - v2.y;
	return StaticLineToLine(p.x, p.y, vdx, vdy, l.position.x, l.position.y, l.direction.x, l.direction.y);
}

// TODO: Finish optimizing, fixing, and converting the following functions
/*
bool DynamicPointToCircle(Vector p, Sphere s, Vector v1, Vector v2)
{
	double vdx = v1.x - v2.x;
	double vdy = v1.y - v2.y;

	double meh = vdx * vdx + vdy * vdy;
	double x = (vdx * s.mPosition.x - p.x * vdx + vdy * s.mPosition.y - p.y * vdy);
	if(0 <= x && x <= meh && (p.x * meh + x * vdx - s.mPosition.x * meh) * 
		                     (p.x * meh + x * vdx - s.mPosition.x * meh) + 
							 (p.y * meh + x * vdy - s.mPosition.y * meh) * 
							 (p.y * meh + x * vdy - s.mPosition.y * meh) <= s.mRadius * s.mRadius * meh * meh)
	{
		return true;
	}
	return false;
}

bool DynamicPointToRect(Vector p, Box b, Vector v1, Vector v2)
{
	double vdx = v1.x - v2.x;
	double vdy = v1.y - v2.y;

	if(StaticLineToLine(p.x, p.y, vdx, vdy, b.mPosition.x, b.mPosition.y, b.mSides.x, 0) ||
	   StaticLineToLine(p.x, p.y, vdx, vdy, b.mPosition.x, b.mPosition.y, 0, b.mSides.y) ||
	   StaticLineToLine(p.x, p.y, vdx, vdy, b.mPosition.x, b.mPosition.y + b.mSides.y, b.mSides.x, 0) ||
	   StaticLineToLine(p.x, p.y, vdx, vdy, b.mPosition.x + b.mSides.x, b.mPosition.y, 0, b.mSides.y))
	{
		return true;
	}
	return false;
}

bool DynamicLineToLine(Line l1, Line l2, Vector v1, Vector v2)
{
	double vdx = v2.x - v1.x;
	double vdy = v2.y - v1.y;

	if(StaticLineToLine(l1.mPosition.x, l1.mPosition.y, -vdx, -vdy, l2.mPosition.x, l2.mPosition.y, l2.mDirection.x, l2.mDirection.y) ||
	   StaticLineToLine(l1.mPosition.x, l1.mPosition.y, l1.mDirection.x, l1.mDirection.y, l2.mPosition.x, l2.mPosition.y, l2.mDirection.x, l2.mDirection.y) ||
	   StaticLineToLine(l1.mPosition.x, l1.mPosition.y, l1.mDirection.x, l1.mDirection.y, l2.mPosition.x, l2.mPosition.y, vdx, vdy) ||
	   StaticLineToLine(l1.mPosition.x, l1.mPosition.y, l1.mDirection.x, l1.mDirection.y, l2.mPosition.x + vdx, l2.mPosition.y + vdy, l2.mDirection.x, l2.mDirection.y) ||
	   StaticLineToLine(l1.mPosition.x, l1.mPosition.y, l1.mDirection.x, l1.mDirection.y, l2.mPosition.x + l2.mDirection.x, l2.mPosition.y + l2.mDirection.y, vdx, vdy))
	{
		return true;
	}
	return false;
}

bool DynamicLineToCircle(Line l, Sphere s, Vector v1, Vector v2)
{
	double vdx = v1.x - v2.x;
	double vdy = v1.y - v2.y;
	double lLength = l.mDirection.Length();
	double vLength = sqrt(vdx * vdx + vdy * vdy);
	double lExtensionx, lExtensiony, vExtensionx, vExtensiony;
	if(lLength == 0)
	{
		lExtensionx = 0;
		lExtensiony = 0;
	}
	else
	{
		lExtensionx = l.mDirection.x / lLength * s.mRadius;
		lExtensiony = l.mDirection.y / lLength * s.mRadius;
	}
	if(vLength == 0)
	{
		vExtensionx = 0;
		vExtensiony = 0;
	}
	else
	{
		vExtensionx = vdx / vLength * s.mRadius;
		vExtensiony = vdy / vLength * s.mRadius;
	}

	if(StaticLineToLine(s.mPosition.x, s.mPosition.y, -vdx, -vdy, l.mPosition.x - lExtensionx, l.mPosition.y - lExtensiony, l.mDirection.x + 2 * lExtensionx, l.mDirection.y + 2 * lExtensiony) ||
	   StaticLineToLine(s.mPosition.x, s.mPosition.y, -l.mDirection.x, -l.mDirection.y, l.mPosition.x - vExtensionx, l.mPosition.y - vExtensiony, vdx + 2 * vExtensionx, vdy + 2 * vExtensiony) ||
	   ((l.mPosition.x - s.mPosition.x) * (l.mPosition.x - s.mPosition.x) + (l.mPosition.y - s.mPosition.y) * (l.mPosition.y - s.mPosition.y)) <= s.mRadius * s.mRadius ||
	   ((l.mPosition.x + vdx - s.mPosition.x) * (l.mPosition.x + vdx - s.mPosition.x) + (l.mPosition.y + vdy - s.mPosition.y) * (l.mPosition.y + vdy - s.mPosition.y)) <= s.mRadius * s.mRadius ||
	   ((l.mPosition.x + l.mDirection.x - s.mPosition.x) * (l.mPosition.x + l.mDirection.x - s.mPosition.x) + (l.mPosition.y + l.mDirection.y - s.mPosition.y) * (l.mPosition.y + l.mDirection.y - s.mPosition.y)) <= s.mRadius * s.mRadius ||
	   ((l.mPosition.x + l.mDirection.x + vdx - s.mPosition.x) * (l.mPosition.x + l.mDirection.x + vdx - s.mPosition.x) + (l.mPosition.y + l.mDirection.y + vdy - s.mPosition.y) * (l.mPosition.y + l.mDirection.y + vdy - s.mPosition.y)) <= s.mRadius * s.mRadius)
	{
		return true;
	}
	return false;
}

bool DynamicLineToRect(Line l, Box b, Vector v1, Vector v2)
{
	double vdx = v1.x - v2.x;
	double vdy = v1.y - v2.y;

	if(StaticLineToLine(l.mPosition.x, l.mPosition.y, vdx, vdy, b.mPosition.x, b.mPosition.y, -l.mDirection.x, -l.mDirection.y) ||
		
	   StaticLineToLine(l.mPosition.x, l.mPosition.y, vdx, vdy, b.mPosition.x, b.mPosition.y, b.mSides.x, 0) ||
	   StaticLineToLine(l.mPosition.x, l.mPosition.y, vdx, vdy, b.mPosition.x, b.mPosition.y, 0, b.mSides.y) ||
	   StaticLineToLine(l.mPosition.x, l.mPosition.y, vdx, vdy, b.mPosition.x, b.mPosition.y + b.mSides.y, b.mSides.x, 0) ||
	   StaticLineToLine(l.mPosition.x, l.mPosition.y, vdx, vdy, b.mPosition.x + b.mSides.x, b.mPosition.y, 0, b.mSides.y) ||
	   
	   StaticLineToLine(l.mPosition.x, l.mPosition.y, l.mDirection.x, l.mDirection.y, b.mPosition.x, b.mPosition.y, b.mSides.x, 0) ||
	   StaticLineToLine(l.mPosition.x, l.mPosition.y, l.mDirection.x, l.mDirection.y, b.mPosition.x, b.mPosition.y, 0, b.mSides.y) ||
	   StaticLineToLine(l.mPosition.x, l.mPosition.y, l.mDirection.x, l.mDirection.y, b.mPosition.x, b.mPosition.y + b.mSides.y, b.mSides.x, 0) ||
	   StaticLineToLine(l.mPosition.x, l.mPosition.y, l.mDirection.x, l.mDirection.y, b.mPosition.x + b.mSides.x, b.mPosition.y, 0, b.mSides.y) ||
	   
	   StaticLineToLine(l.mPosition.x + l.mDirection.x, l.mPosition.y + l.mDirection.y, vdx, vdy, b.mPosition.x, b.mPosition.y, b.mSides.x, 0) ||
	   StaticLineToLine(l.mPosition.x + l.mDirection.x, l.mPosition.y + l.mDirection.y, vdx, vdy, b.mPosition.x, b.mPosition.y, 0, b.mSides.y) ||
	   StaticLineToLine(l.mPosition.x + l.mDirection.x, l.mPosition.y + l.mDirection.y, vdx, vdy, b.mPosition.x, b.mPosition.y + b.mSides.y, b.mSides.x, 0) ||
	   StaticLineToLine(l.mPosition.x + l.mDirection.x, l.mPosition.y + l.mDirection.y, vdx, vdy, b.mPosition.x + b.mSides.x, b.mPosition.y, 0, b.mSides.y) ||
	   
	   StaticLineToLine(l.mPosition.x + vdx, l.mPosition.y + vdy, l.mDirection.x, l.mDirection.y, b.mPosition.x, b.mPosition.y, b.mSides.x, 0) ||
	   StaticLineToLine(l.mPosition.x + vdx, l.mPosition.y + vdy, l.mDirection.x, l.mDirection.y, b.mPosition.x, b.mPosition.y, 0, b.mSides.y) ||
	   StaticLineToLine(l.mPosition.x + vdx, l.mPosition.y + vdy, l.mDirection.x, l.mDirection.y, b.mPosition.x, b.mPosition.y + b.mSides.y, b.mSides.x, 0) ||
	   StaticLineToLine(l.mPosition.x + vdx, l.mPosition.y + vdy, l.mDirection.x, l.mDirection.y, b.mPosition.x + b.mSides.x, b.mPosition.y, 0, b.mSides.y))
	{
		return true;
	}
	return false;
}

bool DynamicCircleToCircle(Sphere s1, Sphere s2, Vector v1, Vector v2)
{
	double vdx = v1.x - v2.x;
	double vdy = v1.y - v2.y;
	double relength = (s1.mRadius + s2.mRadius) / sqrt(vdx * vdx + vdy * vdy);
	double posx = s1.mPosition.x - vdy * relength;
	double posy = s1.mPosition.y + vdx * relength;
	double dirx = 2 * vdy * relength;
	double diry = -2 * vdx * relength;
	
	if(((s1.mPosition.x - s2.mPosition.x) * (s1.mPosition.x - s2.mPosition.x) + (s1.mPosition.y - s2.mPosition.y) * (s1.mPosition.y - s2.mPosition.y)) <= (s1.mRadius + s2.mRadius) * (s1.mRadius + s2.mRadius) ||
	   ((s1.mPosition.x + vdx - s2.mPosition.x) * (s1.mPosition.x + vdx - s2.mPosition.x) + (s1.mPosition.y + vdy - s2.mPosition.y) * (s1.mPosition.y + vdy - s2.mPosition.y)) <= (s1.mRadius + s2.mRadius) * (s1.mRadius + s2.mRadius) ||
	   StaticLineToLine(posx, posy, dirx, diry, s2.mPosition.x, s2.mPosition.y, -vdx, -vdy))
	{
		return true;
	}
	return false;
}

bool DynamicCircleToRect(Sphere s, Box b, Vector v1, Vector v2)
{
	double vdx = v1.x - v2.x;
	double vdy = v1.y - v2.y;
	double relength = s.mRadius / sqrt(vdx * vdx + vdy * vdy);
	double posx = s.mPosition.x - vdy * relength;
	double posy = s.mPosition.y + vdx * relength;
	double dirx = 2 * vdy * relength;
	double diry = -2 * vdx * relength;

	if(StaticLineToLine(posx, posy, vdx, vdy, b.mPosition.x, b.mPosition.y, -dirx, -diry) ||
		
	   StaticLineToLine(posx, posy, vdx, vdy, b.mPosition.x, b.mPosition.y, b.mSides.x, 0) ||
	   StaticLineToLine(posx, posy, vdx, vdy, b.mPosition.x, b.mPosition.y, 0, b.mSides.y) ||
	   StaticLineToLine(posx, posy, vdx, vdy, b.mPosition.x, b.mPosition.y + b.mSides.y, b.mSides.x, 0) ||
	   StaticLineToLine(posx, posy, vdx, vdy, b.mPosition.x + b.mSides.x, b.mPosition.y, 0, b.mSides.y) ||
	   
	   StaticLineToLine(posx, posy, dirx, diry, b.mPosition.x, b.mPosition.y, b.mSides.x, 0) ||
	   StaticLineToLine(posx, posy, dirx, diry, b.mPosition.x, b.mPosition.y, 0, b.mSides.y) ||
	   StaticLineToLine(posx, posy, dirx, diry, b.mPosition.x, b.mPosition.y + b.mSides.y, b.mSides.x, 0) ||
	   StaticLineToLine(posx, posy, dirx, diry, b.mPosition.x + b.mSides.x, b.mPosition.y, 0, b.mSides.y) ||
	   
	   StaticLineToLine(posx + dirx, posy + diry, vdx, vdy, b.mPosition.x, b.mPosition.y, b.mSides.x, 0) ||
	   StaticLineToLine(posx + dirx, posy + diry, vdx, vdy, b.mPosition.x, b.mPosition.y, 0, b.mSides.y) ||
	   StaticLineToLine(posx + dirx, posy + diry, vdx, vdy, b.mPosition.x, b.mPosition.y + b.mSides.y, b.mSides.x, 0) ||
	   StaticLineToLine(posx + dirx, posy + diry, vdx, vdy, b.mPosition.x + b.mSides.x, b.mPosition.y, 0, b.mSides.y) ||
	   
	   StaticLineToLine(posx + vdx, posy + vdy, dirx, diry, b.mPosition.x, b.mPosition.y, b.mSides.x, 0) ||
	   StaticLineToLine(posx + vdx, posy + vdy, dirx, diry, b.mPosition.x, b.mPosition.y, 0, b.mSides.y) ||
	   StaticLineToLine(posx + vdx, posy + vdy, dirx, diry, b.mPosition.x, b.mPosition.y + b.mSides.y, b.mSides.x, 0) ||
	   StaticLineToLine(posx + vdx, posy + vdy, dirx, diry, b.mPosition.x + b.mSides.x, b.mPosition.y, 0, b.mSides.y) ||
	   
	   ((b.mPosition.x - s.mRadius <= s.mPosition.x && s.mPosition.x <= b.mPosition.x + b.mSides.x + s.mRadius) &&
	    (b.mPosition.y <= s.mPosition.y && s.mPosition.y <= b.mPosition.y + b.mSides.y)) ||
	   ((b.mPosition.y - s.mRadius <= s.mPosition.y && s.mPosition.y <= b.mPosition.y + b.mSides.y + s.mRadius) &&
	    (b.mPosition.x <= s.mPosition.x && s.mPosition.x <= b.mPosition.x + b.mSides.x)) ||
	   (b.mPosition.x - s.mPosition.x) * (b.mPosition.x - s.mPosition.x) + (b.mPosition.y - s.mPosition.y) * (b.mPosition.y - s.mPosition.y) <= (s.mRadius * s.mRadius) ||
	   (b.mPosition.x + b.mSides.x - s.mPosition.x) * (b.mPosition.x + b.mSides.x - s.mPosition.x) + (b.mPosition.y - s.mPosition.y) * (b.mPosition.y - s.mPosition.y) <= (s.mRadius * s.mRadius) ||
	   (b.mPosition.x - s.mPosition.x) * (b.mPosition.x - s.mPosition.x) + (b.mPosition.y + b.mSides.y - s.mPosition.y) * (b.mPosition.y + b.mSides.y - s.mPosition.y) <= (s.mRadius * s.mRadius) ||
	   (b.mPosition.x + b.mSides.x - s.mPosition.x) * (b.mPosition.x + b.mSides.x - s.mPosition.x) + (b.mPosition.y + b.mSides.y - s.mPosition.y) * (b.mPosition.y + b.mSides.y - s.mPosition.y) <= (s.mRadius * s.mRadius) ||
	   
	   ((b.mPosition.x - s.mRadius <= s.mPosition.x + vdx && s.mPosition.x + vdx <= b.mPosition.x + b.mSides.x + s.mRadius) &&
	    (b.mPosition.y <= s.mPosition.y + vdy && s.mPosition.y + vdy <= b.mPosition.y + b.mSides.y)) ||
	   ((b.mPosition.y - s.mRadius <= s.mPosition.y + vdy && s.mPosition.y + vdy <= b.mPosition.y + b.mSides.y + s.mRadius) &&
	    (b.mPosition.x <= s.mPosition.x + vdx && s.mPosition.x + vdx <= b.mPosition.x + b.mSides.x)) ||
	   (b.mPosition.x - s.mPosition.x - vdx) * (b.mPosition.x - s.mPosition.x - vdx) + (b.mPosition.y - s.mPosition.y - vdy) * (b.mPosition.y - s.mPosition.y - vdy) <= (s.mRadius * s.mRadius) ||
	   (b.mPosition.x + b.mSides.x - s.mPosition.x - vdx) * (b.mPosition.x + b.mSides.x - s.mPosition.x - vdx) + (b.mPosition.y - s.mPosition.y - vdy) * (b.mPosition.y - s.mPosition.y - vdy) <= (s.mRadius * s.mRadius) ||
	   (b.mPosition.x - s.mPosition.x - vdx) * (b.mPosition.x - s.mPosition.x - vdx) + (b.mPosition.y + b.mSides.y - s.mPosition.y - vdy) * (b.mPosition.y + b.mSides.y - s.mPosition.y - vdy) <= (s.mRadius * s.mRadius) ||
	   (b.mPosition.x + b.mSides.x - s.mPosition.x - vdx) * (b.mPosition.x + b.mSides.x - s.mPosition.x - vdx) + (b.mPosition.y + b.mSides.y - s.mPosition.y - vdy) * (b.mPosition.y + b.mSides.y - s.mPosition.y - vdy) <= (s.mRadius * s.mRadius))
	{
		return true;
	}
	return false;
}

bool DynamicRectToRect(Box b1, Box b2, Vector v1, Vector v2)
{
	double vdx = v1.x - v2.x;
	double vdy = v1.y - v2.y;
	
	double bdx = b1.mPosition.x + b1.mSides.x / 2 - b2.mPosition.x - b2.mSides.x / 2;
	double bdy = b1.mPosition.y + b1.mSides.y / 2 - b2.mPosition.y - b2.mSides.y / 2;

	if((abs(bdx) <= b1.mSides.x / 2 + b2.mSides.x / 2) && 
		(abs(bdy) <= b1.mSides.y / 2 + b2.mSides.y / 2))
	{
		return true;
	}

	bdx += vdx;
	bdy += vdy;

	if((abs(bdx) <= b1.mSides.x / 2 + b2.mSides.x / 2) && 
		(abs(bdy) <= b1.mSides.y / 2 + b2.mSides.y / 2))
	{
		return true;
	}

	if(vdx * vdy >= 0)
	{
		if(StaticLineToLine(b1.mPosition.x, b1.mPosition.y + b1.mSides.y, vdx, vdy, b2.mPosition.x, b2.mPosition.y, -b1.mSides.x, b1.mSides.y) ||
			
		   StaticLineToLine(b1.mPosition.x, b1.mPosition.y + b1.mSides.y, vdx, vdy, b2.mPosition.x, b2.mPosition.y, b2.mSides.x, 0) ||
		   StaticLineToLine(b1.mPosition.x, b1.mPosition.y + b1.mSides.y, vdx, vdy, b2.mPosition.x, b2.mPosition.y, 0, b2.mSides.y) ||
		   StaticLineToLine(b1.mPosition.x, b1.mPosition.y + b1.mSides.y, vdx, vdy, b2.mPosition.x, b2.mPosition.y + b2.mSides.y, b2.mSides.x, 0) ||
		   StaticLineToLine(b1.mPosition.x, b1.mPosition.y + b1.mSides.y, vdx, vdy, b2.mPosition.x + b2.mSides.x, b2.mPosition.y, 0, b2.mSides.y) ||
	   
		   StaticLineToLine(b1.mPosition.x + b1.mSides.x, b1.mPosition.y, vdx, vdy, b2.mPosition.x, b2.mPosition.y, b2.mSides.x, 0) ||
		   StaticLineToLine(b1.mPosition.x + b1.mSides.x, b1.mPosition.y, vdx, vdy, b2.mPosition.x, b2.mPosition.y, 0, b2.mSides.y) ||
		   StaticLineToLine(b1.mPosition.x + b1.mSides.x, b1.mPosition.y, vdx, vdy, b2.mPosition.x, b2.mPosition.y + b2.mSides.y, b2.mSides.x, 0) ||
		   StaticLineToLine(b1.mPosition.x + b1.mSides.x, b1.mPosition.y, vdx, vdy, b2.mPosition.x + b2.mSides.x, b2.mPosition.y, 0, b2.mSides.y) ||
	   
		   StaticLineToLine(b1.mPosition.x, b1.mPosition.y + b1.mSides.y, b1.mSides.x, -b1.mSides.y, b2.mPosition.x, b2.mPosition.y, b2.mSides.x, 0) ||
		   StaticLineToLine(b1.mPosition.x, b1.mPosition.y + b1.mSides.y, b1.mSides.x, -b1.mSides.y, b2.mPosition.x, b2.mPosition.y, 0, b2.mSides.y) ||
		   StaticLineToLine(b1.mPosition.x, b1.mPosition.y + b1.mSides.y, b1.mSides.x, -b1.mSides.y, b2.mPosition.x, b2.mPosition.y + b2.mSides.y, b2.mSides.x, 0) ||
		   StaticLineToLine(b1.mPosition.x, b1.mPosition.y + b1.mSides.y, b1.mSides.x, -b1.mSides.y, b2.mPosition.x + b2.mSides.x, b2.mPosition.y, 0, b2.mSides.y) ||
	   
		   StaticLineToLine(b1.mPosition.x + vdx, b1.mPosition.y + b1.mSides.y + vdy, b1.mSides.x, -b1.mSides.y, b2.mPosition.x, b2.mPosition.y, b2.mSides.x, 0) ||
		   StaticLineToLine(b1.mPosition.x + vdx, b1.mPosition.y + b1.mSides.y + vdy, b1.mSides.x, -b1.mSides.y, b2.mPosition.x, b2.mPosition.y, 0, b2.mSides.y) ||
		   StaticLineToLine(b1.mPosition.x + vdx, b1.mPosition.y + b1.mSides.y + vdy, b1.mSides.x, -b1.mSides.y, b2.mPosition.x, b2.mPosition.y + b2.mSides.y, b2.mSides.x, 0) ||
		   StaticLineToLine(b1.mPosition.x + vdx, b1.mPosition.y + b1.mSides.y + vdy, b1.mSides.x, -b1.mSides.y, b2.mPosition.x + b2.mSides.x, b2.mPosition.y, 0, b2.mSides.y))
		{
			return true;
		} 
	}
	else if(StaticLineToLine(b1.mPosition.x, b1.mPosition.y, vdx, vdy, b2.mPosition.x, b2.mPosition.y, -b1.mSides.x, -b1.mSides.y) ||
		
			StaticLineToLine(b1.mPosition.x, b1.mPosition.y, vdx, vdy, b2.mPosition.x, b2.mPosition.y, b2.mSides.x, 0) ||
			StaticLineToLine(b1.mPosition.x, b1.mPosition.y, vdx, vdy, b2.mPosition.x, b2.mPosition.y, 0, b2.mSides.y) ||
			StaticLineToLine(b1.mPosition.x, b1.mPosition.y, vdx, vdy, b2.mPosition.x, b2.mPosition.y + b2.mSides.y, b2.mSides.x, 0) ||
			StaticLineToLine(b1.mPosition.x, b1.mPosition.y, vdx, vdy, b2.mPosition.x + b2.mSides.x, b2.mPosition.y, 0, b2.mSides.y) ||
	   
			StaticLineToLine(b1.mPosition.x + b1.mSides.x, b1.mPosition.y + b1.mSides.y, vdx, vdy, b2.mPosition.x, b2.mPosition.y, b2.mSides.x, 0) ||
			StaticLineToLine(b1.mPosition.x + b1.mSides.x, b1.mPosition.y + b1.mSides.y, vdx, vdy, b2.mPosition.x, b2.mPosition.y, 0, b2.mSides.y) ||
			StaticLineToLine(b1.mPosition.x + b1.mSides.x, b1.mPosition.y + b1.mSides.y, vdx, vdy, b2.mPosition.x, b2.mPosition.y + b2.mSides.y, b2.mSides.x, 0) ||
			StaticLineToLine(b1.mPosition.x + b1.mSides.x, b1.mPosition.y + b1.mSides.y, vdx, vdy, b2.mPosition.x + b2.mSides.x, b2.mPosition.y, 0, b2.mSides.y) ||
	   
			StaticLineToLine(b1.mPosition.x, b1.mPosition.y, b1.mSides.x, b1.mSides.y, b2.mPosition.x, b2.mPosition.y, b2.mSides.x, 0) ||
			StaticLineToLine(b1.mPosition.x, b1.mPosition.y, b1.mSides.x, b1.mSides.y, b2.mPosition.x, b2.mPosition.y, 0, b2.mSides.y) ||
			StaticLineToLine(b1.mPosition.x, b1.mPosition.y, b1.mSides.x, b1.mSides.y, b2.mPosition.x, b2.mPosition.y + b2.mSides.y, b2.mSides.x, 0) ||
			StaticLineToLine(b1.mPosition.x, b1.mPosition.y, b1.mSides.x, b1.mSides.y, b2.mPosition.x + b2.mSides.x, b2.mPosition.y, 0, b2.mSides.y) ||
	   
			StaticLineToLine(b1.mPosition.x + vdx, b1.mPosition.y + vdy, b1.mSides.x, b1.mSides.y, b2.mPosition.x, b2.mPosition.y, b2.mSides.x, 0) ||
			StaticLineToLine(b1.mPosition.x + vdx, b1.mPosition.y + vdy, b1.mSides.x, b1.mSides.y, b2.mPosition.x, b2.mPosition.y, 0, b2.mSides.y) ||
			StaticLineToLine(b1.mPosition.x + vdx, b1.mPosition.y + vdy, b1.mSides.x, b1.mSides.y, b2.mPosition.x, b2.mPosition.y + b2.mSides.y, b2.mSides.x, 0) ||
			StaticLineToLine(b1.mPosition.x + vdx, b1.mPosition.y + vdy, b1.mSides.x, b1.mSides.y, b2.mPosition.x + b2.mSides.x, b2.mPosition.y, 0, b2.mSides.y))
	{
		return true;
	}
	return false;
}
*/

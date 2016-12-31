#include "StaticCollisions.h"

inline bool StaticLineToLine(
	double line1_point_x,
	double line1_point_y,
	double line1_destination_x,
	double line1_destination_y,
	double line2_point_x,
	double line2_point_y,
	double line2_destination_x,
	double line2_destination_y)
{
	double dx = line2_point_x - line1_point_x;
	double determinant = (line1_destination_x * line2_destination_y - line2_destination_x * line1_destination_y);
	double dy = line2_point_y - line1_point_y;
	
	if(determinant != 0)
	{
		double s = (line1_destination_y * dx - line1_destination_x * dy) / determinant;
		double t = (line2_destination_y * dx - line2_destination_x * dy) / determinant;
		if(0 <= s && s <= 1 &&
		   0 <= t && t <= 1)
		{
			return true;
		}
	}
	else
	{
		double bdx = line1_point_x * 2 + line1_destination_x - line2_point_x * 2 - line2_destination_x;
		double bdy = line1_point_y * 2 + line1_destination_y - line2_point_y * 2 - line2_destination_y;
		if(abs(bdx) <= abs(line1_destination_x) + abs(line2_destination_x) &&
		   abs(bdy) <= abs(line1_destination_y) + abs(line2_destination_y))
		{
			return true;
		}
	}
	return false;
}

bool StaticPointToPoint(Vector p1, Vector p2)
{
	// It turns out that after optimizations, a distance comparison is faster than a logical one.
	if((p1.x - p2.x) * (p1.x - p2.x) + (p1.y - p2.y) * (p1.y - p2.y) == 0)
	{
		return true;
	}
	return false;
}

bool StaticPointToLine(Vector p, Line l)
{
	double m = (p.x - l.mPosition.x) * l.mDirection.y;
	if(m == (p.y - l.mPosition.y) * l.mDirection.x)
	{
		double dirMul = l.mDirection.x * l.mDirection.y;
		if(dirMul < 0)
		{
			if(0 >= m && m >= dirMul)
			{
				return true;
			}
		}
		if(0 <= m && m <= dirMul)
		{
			return true;
		}
	}
	return false;
}

bool StaticPointToCircle(Vector p, Sphere s)
{
	if((p.x-s.mPosition.x) * (p.x-s.mPosition.x) + (p.y-s.mPosition.y) * (p.y-s.mPosition.y) <= (s.mRadius * s.mRadius))
	{
		return true;
	}
	return false;
}

bool StaticPointToRect(Vector p, Box b)
{
	// It turns out that the fewer logical operations you have the faster something runs
	double dx = b.mPosition.x * 2 + b.mSides.x - p.x * 2;
	double dy = b.mPosition.y * 2 + b.mSides.y - p.y * 2;

	if((abs(dx) <= b.mSides.x) && (abs(dy) <= b.mSides.y))
	{
		return true;
	}
	return false;
}

bool StaticLineToLine(Line l1, Line l2)
{
	double dx = l2.mPosition.x - l1.mPosition.x;
	double det = (l1.mDirection.x * l2.mDirection.y - l2.mDirection.x * l1.mDirection.y);
	double dy = l2.mPosition.y - l1.mPosition.y;
	double s = (l1.mDirection.y * dx - l1.mDirection.x * dy);
	double t = (l2.mDirection.y * dx - l2.mDirection.x * dy);
	if(det < 0)
	{
		if(0 >= s && s >= det && 
		   0 >= t && t >= det)
		{
			return true;
		}
	}
	else if(det > 0)
	{
		if(0 <= s && s <= det && 
		   0 <= t && t <= det)
		{
			return true;
		}
	}
	else
	{
		double bdx = l1.mPosition.x * 2 + l1.mDirection.x - l2.mPosition.x * 2 - l2.mDirection.x;
		double bdy = l1.mPosition.y * 2 + l1.mDirection.y - l2.mPosition.y * 2 - l2.mDirection.y;
		if(abs(bdx) <= abs(l1.mDirection.x) + abs(l2.mDirection.x) &&
		   abs(bdy) <= abs(l1.mDirection.y) + abs(l2.mDirection.y))
		{
			return true;
		}
	}
	return false;
}

bool StaticLineToCircle(Line l, Sphere s)
{
	double meh = l.mDirection.x * l.mDirection.x + l.mDirection.y * l.mDirection.y;
	double x = (l.mDirection.x * s.mPosition.x - l.mPosition.x * l.mDirection.x + 
	            l.mDirection.y * s.mPosition.y - l.mPosition.y * l.mDirection.y);
	if(0 <= x && x <= meh && (l.mPosition.x * meh + x * l.mDirection.x - s.mPosition.x * meh) * 
		                     (l.mPosition.x * meh + x * l.mDirection.x - s.mPosition.x * meh) + 
							 (l.mPosition.y * meh + x * l.mDirection.y - s.mPosition.y * meh) * 
							 (l.mPosition.y * meh + x * l.mDirection.y - s.mPosition.y * meh) <= s.mRadius * s.mRadius * meh * meh)
	{
		return true;
	}
	return false;
}

bool StaticLineToRect(Line l, Box b)
{
	if(StaticPointToRect(l.mPosition, b) ||
	   StaticLineToLine(l.mPosition.x, l.mPosition.y, l.mDirection.x, l.mDirection.y, b.mPosition.x, b.mPosition.y, b.mSides.x, 0) ||
	   StaticLineToLine(l.mPosition.x, l.mPosition.y, l.mDirection.x, l.mDirection.y, b.mPosition.x, b.mPosition.y, 0, b.mSides.y) ||
	   StaticLineToLine(l.mPosition.x, l.mPosition.y, l.mDirection.x, l.mDirection.y, b.mPosition.x, b.mPosition.y + b.mSides.y, b.mSides.x, 0) ||
	   StaticLineToLine(l.mPosition.x, l.mPosition.y, l.mDirection.x, l.mDirection.y, b.mPosition.x + b.mSides.x, b.mPosition.y, 0, b.mSides.y))
	{
		return true;
	}
	return false;
}

bool StaticCircleToCircle(Sphere s1, Sphere s2)
{
	if((s1.mPosition.x - s2.mPosition.x) * (s1.mPosition.x-s2.mPosition.x) + 
	   (s1.mPosition.y - s2.mPosition.y) * (s1.mPosition.y-s2.mPosition.y) <=
	   (s1.mRadius + s2.mRadius) * (s1.mRadius + s2.mRadius))
	{
		return true;
	}
	return false;
}

bool StaticCircleToRect(Sphere s, Box b)
{
	if(((b.mPosition.x - s.mRadius <= s.mPosition.x && s.mPosition.x <= b.mPosition.x + b.mSides.x + s.mRadius) &&
	    (b.mPosition.y <= s.mPosition.y && s.mPosition.y <= b.mPosition.y + b.mSides.y)) ||
	   ((b.mPosition.y - s.mRadius <= s.mPosition.y && s.mPosition.y <= b.mPosition.y + b.mSides.y + s.mRadius) &&
	    (b.mPosition.x <= s.mPosition.x && s.mPosition.x <= b.mPosition.x + b.mSides.x)) ||
	   (b.mPosition.x - s.mPosition.x) * (b.mPosition.x - s.mPosition.x) + (b.mPosition.y - s.mPosition.y) * (b.mPosition.y - s.mPosition.y) <= (s.mRadius * s.mRadius) ||
	   (b.mPosition.x + b.mSides.x - s.mPosition.x) * (b.mPosition.x + b.mSides.x - s.mPosition.x) + (b.mPosition.y - s.mPosition.y) * (b.mPosition.y - s.mPosition.y) <= (s.mRadius * s.mRadius) ||
	   (b.mPosition.x - s.mPosition.x) * (b.mPosition.x - s.mPosition.x) + (b.mPosition.y + b.mSides.y - s.mPosition.y) * (b.mPosition.y + b.mSides.y - s.mPosition.y) <= (s.mRadius * s.mRadius) ||
	   (b.mPosition.x + b.mSides.x - s.mPosition.x) * (b.mPosition.x + b.mSides.x - s.mPosition.x) + (b.mPosition.y + b.mSides.y - s.mPosition.y) * (b.mPosition.y + b.mSides.y - s.mPosition.y) <= (s.mRadius * s.mRadius))
	{
		return true;
	}
	return false;
}

bool StaticRectToRect(Box b1, Box b2)
{
	double bdx = b1.mPosition.x * 2 + b1.mSides.x - b2.mPosition.x * 2 - b2.mSides.x;
	double bdy = b1.mPosition.y * 2 + b1.mSides.y - b2.mPosition.y * 2 - b2.mSides.y;

	if((abs(bdx) <= b1.mSides.x + b2.mSides.x) && 
	   (abs(bdy) <= b1.mSides.y + b2.mSides.y))
	{
		return true;
	}
	return false;
}

#pragma once
#include <cmath>
#include "FInt.h"

namespace Static
{
	bool PointToPoint  (FInt p1x,   FInt p1y,
		                FInt p2x,   FInt p2y);
	bool PointToLine   (FInt p1x,   FInt p1y,
		                FInt l1p1x, FInt l1p1y, FInt l1p2x, FInt l1p2y);
	bool PointToCircle (FInt p1x,   FInt p1y,
		                FInt s1x,   FInt s1y,   FInt s1r);
	bool PointToRect   (FInt p1x,   FInt p1y,
		                FInt b1x,   FInt b1y,   FInt b1w,   FInt b1h);

	bool LineToLine    (FInt l1p1x, FInt l1p1y, FInt l1p2x, FInt l1p2y,
		                FInt l2p1x, FInt l2p1y, FInt l2p2x, FInt l2p2y);
	bool LineToCircle  (FInt l1p1x, FInt l1p1y, FInt l1p2x, FInt l1p2y,
		                FInt s1x,   FInt s1y,   FInt s1r);
	bool LineToRect    (FInt l1p1x, FInt l1p1y, FInt l1p2x, FInt l1p2y,
		                FInt b1x,   FInt b1y,   FInt b1w,   FInt b1h);

	bool CircleToCircle(FInt s1x,   FInt s1y,   FInt s1r,
		                FInt s2x,   FInt s2y,   FInt s2r);
	bool CircleToRect  (FInt s1x,   FInt s1y,   FInt s1r,
		                FInt b1x,   FInt b1y,   FInt b1w,   FInt b1h);

	bool RectToRect    (FInt b1x,   FInt b1y,   FInt b1w,   FInt b1h,
		                FInt b2x,   FInt b2y,   FInt b2w,   FInt b2h);
}

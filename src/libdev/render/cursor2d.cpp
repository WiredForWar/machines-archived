/*
 * C U R S O R 2 D . C P P 
 * (c) Charybdis Limited, 1997. All Rights Reserved
 */

#include "mathex/point2d.hpp"
#include "render/cursor2d.hpp"

RenCursor2d::RenCursor2d():
	ox_(0),
	oy_(0)
{
}

// virtual
RenCursor2d::~RenCursor2d()
{
}

void RenCursor2d::origin( const MexPoint2d& point )
{
    ox_ = point.x();
    oy_ = point.y();
}

int  RenCursor2d::originX() const
{
	return ox_;
}

int  RenCursor2d::originY() const
{
	return oy_;
}

ostream& operator <<( ostream& o, const RenCursor2d& t )
{
	t.print(o);
    return o;
}

/* End CURSOR2D.CPP *************************************************/

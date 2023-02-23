/*
 * C S 2 P O L Y G . I P P
 * (c) Charybdis Limited, 1997. All Rights Reserved
 */

//  Definitions of inline non-template methods and inline global functions

#ifdef _INLINE
#define _CODE_INLINE inline
#else
#define _CODE_INLINE
#endif

//////////////////////////////////////////////////////////////////////////////////////////
_CODE_INLINE
const PhysConfigSpace2d::PolygonId& PhysCS2dPolygon::id() const
{
    return id_;
}
//////////////////////////////////////////////////////////////////////////////////////////
_CODE_INLINE
const MexPolygon2d& PhysCS2dPolygon::polygon() const
{
    return polygon_;
}
//////////////////////////////////////////////////////////////////////////////////////////
_CODE_INLINE
MATHEX_SCALAR PhysCS2dPolygon::height() const
{
    return height_;
}
//////////////////////////////////////////////////////////////////////////////////////////
_CODE_INLINE
PhysConfigSpace2d::Longevity PhysCS2dPolygon::longevity() const
{
    return longevity_;
}
//////////////////////////////////////////////////////////////////////////////////////////
_CODE_INLINE
void PhysCS2dPolygon::longevity(PhysConfigSpace2d::Longevity newLongevity)
{
    longevity_ = newLongevity;
}
//////////////////////////////////////////////////////////////////////////////////////////
_CODE_INLINE
const MexAlignedBox2d& PhysCS2dPolygon::boundary() const
{
    return boundary_;
}
//////////////////////////////////////////////////////////////////////////////////////////
_CODE_INLINE
void PhysCS2dPolygon::boundary(MexAlignedBox2d* pBox) const
{
    *pBox = boundary_;
}
//////////////////////////////////////////////////////////////////////////////////////////
_CODE_INLINE
bool PhysCS2dPolygon::isEnabled() const
{
    return enabled_;
}
//////////////////////////////////////////////////////////////////////////////////////////
_CODE_INLINE
void PhysCS2dPolygon::isEnabled(bool doEnable)
{
    enabled_ = doEnable;
}
//////////////////////////////////////////////////////////////////////////////////////////
_CODE_INLINE
PhysCS2dPolygon::Flags PhysCS2dPolygon::flags() const
{
    return flags_;
}

//////////////////////////////////////////////////////////////////////////////////////////
/* End CS2POLYG.IPP *************************************************/

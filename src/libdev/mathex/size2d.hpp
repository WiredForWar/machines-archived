/*
 * size2d.hpp
 */

#ifndef _MATHEX_SIZE2D_HPP
#define _MATHEX_SIZE2D_HPP

#include "base/base.hpp"
#include "base/persist.hpp"

#include "mathex/mathex.hpp"

class MexSize2d
{
public:
	MexSize2d( MATHEX_SCALAR width, MATHEX_SCALAR height);
	MexSize2d() = default;

	~MexSize2d() = default;

	MexSize2d& operator =( const MexSize2d& rhs ) = default;
	bool operator ==( const MexSize2d& ) const;
	bool operator !=( const MexSize2d& ) const;

	MATHEX_SCALAR width() const;
	MATHEX_SCALAR height() const;
	void setWidth( MATHEX_SCALAR widthNew );
	void setHeight( MATHEX_SCALAR heightNew );

	void CLASS_INVARIANT;

	friend ostream& operator <<( ostream& o, const MexSize2d& t );

private:
	//The coordinates
	MATHEX_SCALAR width_ = 0;
	MATHEX_SCALAR height_ = 0;
};

inline MexSize2d::MexSize2d( MATHEX_SCALAR w, MATHEX_SCALAR h)
	: width_(w)
	, height_(h)
{
}

inline MATHEX_SCALAR MexSize2d::width() const
{
	return width_;
}

inline MATHEX_SCALAR MexSize2d::height() const
{
	return height_;
}

inline void MexSize2d::setWidth( MATHEX_SCALAR widthNew )
{
	width_ = widthNew;
}

inline void MexSize2d::setHeight( MATHEX_SCALAR heightNew )
{
	height_ = heightNew;
}

#endif // _MATHEX_SIZE2D_HPP

/* End size2d.hpp **************************************************/

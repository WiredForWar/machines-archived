/*
 * size2d.cpp
 */

#include <iostream>

#include "mathex/size2d.hpp"

ostream& operator <<( ostream& o, const MexSize2d& t )
{

    o << "  (" << t.width_ << "," << t.height_ << ")";
    return o;
}

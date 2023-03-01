/*
 * B U I L D B A R . C P P
 * (c) Charybdis Limited, 1998. All Rights Reserved
 */

//  Definitions of non-inline non-template methods and global functions

#include "machgui/buildbar.hpp"
#include "machgui/gui.hpp"
#include "gui/manager.hpp"
#include "gui/painter.hpp"

enum
{
    BORDER_THICKNESS = 1
};
enum
{
    BAR_THICKNESS = 2
};
enum
{
    SHADOW_THICKNESS = 1
};

MachGuiBuildProgressBar::MachGuiBuildProgressBar(GuiDisplayable* pParent, const Gui::Coord& rel, size_t width)
    : GuiDisplayable(pParent, Gui::Box(rel, width, MachGuiBuildProgressBar::height()))
    , percentageComplete_(0.0)
{

    TEST_INVARIANT;
}

MachGuiBuildProgressBar::~MachGuiBuildProgressBar()
{
    TEST_INVARIANT;

}

void MachGuiBuildProgressBar::CLASS_INVARIANT
{
    INVARIANT( this != NULL );
}

void MachGuiBuildProgressBar::depress( bool doDepress )
{
	if ( doDepress )
	{
		relativeCoord( Gui::Coord( 3, 3 ) );
	}
	else
	{
		relativeCoord( Gui::Coord( 2, 2 ) );
	}
}

Gui::Colour	MachGuiBuildProgressBar::barColour() const
// width in pixels for a given ratio
{
	unsigned currentValue = 1;
	unsigned maxValue = 1;

	PRE( currentValue <= maxValue );
	const float LOW_THRESHOLD = 1.0 / 3.0;
	const float MID_THRESHOLD = 1.7 / 3.0;

	Gui::Colour result = MachGui::PROGRESSGREEN();
	float ratio = currentValue  / (float)maxValue;
	if( ratio <= LOW_THRESHOLD )
		result = Gui::RED();
	else if( ratio <= MID_THRESHOLD )
		result = Gui::YELLOW();

	return result;
}

void MachGuiBuildProgressBar::doDisplay()
{
    const int BorderThickness = BORDER_THICKNESS * MachGui::uiScaleFactor();
    const int ShadowThickness = SHADOW_THICKNESS * MachGui::uiScaleFactor();
    const int BarThickness = MachGui::uiScaleFactor() == 1 ? BAR_THICKNESS : BAR_THICKNESS + 1;

    GuiPainter::instance().filledRectangle(absoluteBoundary(), MachGui::PURPLE());

    size_t interiorWidth = width() - (2 * BorderThickness) - ShadowThickness;
    size_t barWidth = (percentageComplete_ / 100.0) * interiorWidth;

    Gui::Coord topLeft(absoluteCoord().x() + BorderThickness, absoluteCoord().y() + BorderThickness);
    Gui::Coord sc(topLeft + Gui::Coord(ShadowThickness, 0));

    GuiPainter::instance().horizontalLine(sc, interiorWidth, Gui::BLACK(), ShadowThickness);
    if (barWidth)
    {
        // Only draw if the barWidth is not zero
        Gui::Coord bc(topLeft + Gui::Coord(ShadowThickness, ShadowThickness + 1 * MachGui::uiScaleFactor()));
        GuiPainter::instance().horizontalLine(bc, barWidth, barColour(), BarThickness);
    }
    GuiPainter::instance().verticalLine(topLeft, height() - BorderThickness, Gui::BLACK(), ShadowThickness);

    GuiPainter::instance().hollowRectangle(absoluteBoundary(), Gui::WHITE(), BorderThickness);
}

//static
size_t MachGuiBuildProgressBar::height()
{
    const int BarThickness = MachGui::uiScaleFactor() == 1 ? BAR_THICKNESS : BAR_THICKNESS + 1;
    return (BORDER_THICKNESS + SHADOW_THICKNESS + BORDER_THICKNESS) * MachGui::uiScaleFactor() + BarThickness;
}

void MachGuiBuildProgressBar::percentageComplete( float complete )
{
	percentageComplete_ = complete;
	changed();
}


ostream& operator <<( ostream& o, const MachGuiBuildProgressBar& t )
{

    o << "MachGuiBuildProgressBar " << (void*)&t << " start" << std::endl;
    o << "MachGuiBuildProgressBar " << (void*)&t << " end" << std::endl;

    return o;
}

float MachGuiBuildProgressBar::percentageComplete() const
{
	return percentageComplete_;
}

/* End BUILDBAR.CPP *************************************************/

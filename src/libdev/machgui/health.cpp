/*
 * H E A L T H . C P P 
 * (c) Charybdis Limited, 1997. All Rights Reserved
 */

#include "machgui/health.hpp"
#include "machgui/gui.hpp"
#include "gui/manager.hpp"
#include "gui/painter.hpp"

//////////////////////////////////////////////////////////////////////

enum
{
    BORDER_THICKNESS = 1
};
enum
{
    HP_THICKNESS = 2
};
enum
{
    DIVIDER_THICKNESS = 1
};
enum
{
    AP_THICKNESS = 2
};
enum
{
    SHADOW_THICKNESS = 1
};

MachGuiHealthBar::MachGuiHealthBar(GuiDisplayable* pParent,
                                   const Gui::Coord& rel,
                                   unsigned width,
                                   MachPhys::HitPointUnits maxHits,
                                   MachPhys::ArmourUnits maxArmour)
    : GuiDisplayable(pParent, Gui::Box(rel, width, healthBarHeight()))
    , maxHits_(maxHits)
    , maxArmour_(maxArmour)
    , currentHits_(0)
    , currentArmour_(0)
{
	PRE( maxHits > 0 );
	PRE( maxArmour > 0 );
}

MachGuiHealthBar::~MachGuiHealthBar()
{
	// Intentionally Empty
}

//////////////////////////////////////////////////////////////////////

MachPhys::HitPointUnits 
MachGuiHealthBar::maxHits() const {	return maxHits_; }

MachPhys::ArmourUnits 
MachGuiHealthBar::maxArmour() const { return maxArmour_; }

void MachGuiHealthBar::hp( MachPhys::HitPointUnits hits )
{
	PRE_INFO( hits );
	PRE_INFO( maxHits() );
	PRE( hits <= maxHits() );

	unsigned interiorWidth = width() - ( 2 * BORDER_THICKNESS );
	unsigned oldWidth = ( currentHits_ * interiorWidth ) / maxHits_;
	unsigned newWidth = ( hits * interiorWidth ) / maxHits_;

	if( newWidth != oldWidth )
		changed();

	currentHits_ = hits;
}

void MachGuiHealthBar::armour( MachPhys::ArmourUnits armour )
{
	PRE_INFO( armour );
	PRE_INFO( maxArmour() );
	PRE( armour <= maxArmour() );

	unsigned interiorWidth = width() - ( 2 * BORDER_THICKNESS );
	unsigned oldWidth = ( currentArmour_ * interiorWidth ) / maxArmour_;
	unsigned newWidth = ( armour * interiorWidth ) / maxArmour_;

	if( newWidth != oldWidth )
		changed();

	currentArmour_ = armour;
}

//////////////////////////////////////////////////////////////////////

// static
Gui::Colour
MachGuiHealthBar::hpColour( unsigned currentValue, unsigned maxValue )
// width in pixels for a given ratio
{
	PRE( currentValue <= maxValue );
	const float LOW_THRESHOLD = 1.0 / 3.0;
	const float MID_THRESHOLD = 1.7 / 3.0;
	
	Gui::Colour result = Gui::Colour( 0, 128.0/255.0, 0 );
	float ratio = currentValue  / (float)maxValue;
	if( ratio <= LOW_THRESHOLD )
		result = Gui::RED();
	else if( ratio <= MID_THRESHOLD )
		result = Gui::YELLOW();

	return result;
}

// static 
Gui::Colour
MachGuiHealthBar::armourColour( unsigned currentValue, unsigned maxValue )
// width in pixels for a given ratio
{
	PRE( currentValue <= maxValue );
	const float LOW_THRESHOLD = 1.0 / 3.0;
	const float MID_THRESHOLD = 1.7 / 3.0;

	static const Gui::Colour blue( 33.0/255.0, 6.0/255.0, 217.0/255.0 );
	static const Gui::Colour purple( 128.0/255.0, 0, 128.0/255.0 );
	static const Gui::Colour red( 252.0/255.0, 0.0, 1.0/255.0 );

	Gui::Colour result = blue;
	float ratio = currentValue  / (float)maxValue;
	if( ratio <= LOW_THRESHOLD )
		result = red;
	else if( ratio <= MID_THRESHOLD )
		result = purple;

	return result;
}

//////////////////////////////////////////////////////////////////////

void MachGuiHealthBar::doDisplay()
{
    const int BorderThickness = BORDER_THICKNESS * MachGui::uiScaleFactor();
    const int ShadowThickness = SHADOW_THICKNESS * MachGui::uiScaleFactor();
    const int DividerThickness = DIVIDER_THICKNESS * MachGui::uiScaleFactor();
    const int BarThickness = MachGui::uiScaleFactor() == 1 ? 2 : 3; // HP_THICKNESS, AP_THICKNESS

    unsigned interiorWidth = width() - (2 * BorderThickness) - ShadowThickness;
    unsigned armourWidth = ((double)currentArmour_ / (double)maxArmour_) * interiorWidth;
    unsigned hitsWidth = ((double)currentHits_ / (double)maxHits_) * interiorWidth;

    Gui::Coord topLeft(absoluteCoord().x() + BorderThickness, absoluteCoord().y() + BorderThickness);
    Gui::Coord sc(absoluteCoord().x() + BorderThickness + ShadowThickness, absoluteCoord().y() + BorderThickness);
    Gui::Coord ac(absoluteCoord().x() + BorderThickness + ShadowThickness,
                  absoluteCoord().y() + 1 * MachGui::uiScaleFactor() + BorderThickness + ShadowThickness);
    Gui::Coord dc(absoluteCoord().x() + BorderThickness + ShadowThickness,
                  absoluteCoord().y() + BorderThickness + ShadowThickness + BarThickness);
    Gui::Coord hc(absoluteCoord().x() + BorderThickness + ShadowThickness,
                  absoluteCoord().y() + 1 * MachGui::uiScaleFactor() + BorderThickness + ShadowThickness + BarThickness
                      + DividerThickness);

    GuiPainter::instance().horizontalLine(sc, interiorWidth, Gui::BLACK(), ShadowThickness);
    GuiPainter::instance().horizontalLine(ac, interiorWidth - 1, Gui::LIGHTGREY(), BarThickness);
    GuiPainter::instance().horizontalLine(ac, armourWidth, armourColour(currentArmour_, maxArmour_), BarThickness);
    GuiPainter::instance().horizontalLine(dc, interiorWidth, Gui::LIGHTGREY(), DividerThickness);
    GuiPainter::instance().horizontalLine(hc, interiorWidth - 1, Gui::LIGHTGREY(), BarThickness);
    GuiPainter::instance().horizontalLine(hc, hitsWidth, hpColour(currentHits_, maxHits_), BarThickness);
    GuiPainter::instance().verticalLine(
        topLeft, ShadowThickness + BarThickness + DividerThickness + BarThickness, Gui::BLACK(), ShadowThickness);

    GuiPainter::instance().hollowRectangle(absoluteBoundary(), Gui::WHITE(), BorderThickness);
}

//static 
size_t MachGuiHealthBar::healthBarHeight()
{
    const int BarThickness = MachGui::uiScaleFactor() == 1 ? 2 : 3; // HP_THICKNESS, AP_THICKNESS

    return (BORDER_THICKNESS + SHADOW_THICKNESS + DIVIDER_THICKNESS + BORDER_THICKNESS) * MachGui::uiScaleFactor()
           + BarThickness * 2;
}

void MachGuiHealthBar::depress( bool doDepress )
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

ostream& operator <<( ostream& o, const MachGuiHealthBar& t )
{
    o << "MachGuiHealthBar " << (void*)&t << " start" << std::endl;
    o << "MachGuiHealthBar " << (void*)&t << " end" << std::endl;

    return o;
}

//////////////////////////////////////////////////////////////////////

/* End HEALTH.CPP ***************************************************/

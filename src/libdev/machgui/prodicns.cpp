/*
 * P R O D I C N S . C P P 
 * (c) Charybdis Limited, 1997. All Rights Reserved
 */

//  Definitions of non-inline non-template methods and global functions

#include "stdlib/string.hpp"
#include "ctl/list.hpp"
#include "ctl/vector.hpp"
#include "gui/manager.hpp"
#include "machgui/prodicns.hpp"
#include "machgui/prodicon.hpp"
#include "machgui/gui.hpp"
#include "machgui/ingame.hpp"
#include "machgui/controlp.hpp"
#include "machlog/factory.hpp"
#include "machlog/produnit.hpp"
#include <iostream>
#include <ostream>

/* ////////////////////////////////////////////// constructor /////////////////////////////////////////////////// */

int GetMaxDivisible(int divisible, int divider)
{
    return (divisible / divider) * divider;
}

MachProductionIcons::MachProductionIcons(GuiDisplayable* pParent,
                                         const Gui::Box& area,
                                         MachLogFactory* pFactory,
                                         MachInGameScreen* pInGameScreen)
    : GuiSimpleScrollableList(
        pParent,
        Gui::Box(area.minCorner(), GetMaxDivisible(area.width(), MachProductionIcon::buttonWidth()), area.height()),
        MachProductionIcon::buttonWidth(),
        MachProductionIcon::buttonHeight(),
        1)
    , pFactory_(pFactory)
    , pInGameScreen_(pInGameScreen)
{
    std::cerr << "MachProductionIcons area: " << area << std::endl;
    //Add the icons
    updateIcons();

    TEST_INVARIANT;
}

void MachProductionIcons::onIconClicked(GuiButton* pIcon)
{
    MachProductionIcon* pProdIcon = static_cast<MachProductionIcon*>(pIcon);
    pFactory_->cancelProductionUnit(pProdIcon->productionUnit());

    updateIcons();
}

/* /////////////////////////////////////////////// destructor /////////////////////////////////////////////////// */

MachProductionIcons::~MachProductionIcons()
{
    TEST_INVARIANT;
}

/* ////////////////////////////////////////////////////////////////////////////////////////////////////////////// */

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

void MachProductionIcons::CLASS_INVARIANT
{
	INVARIANT( this != NULL );
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

void MachProductionIcons::updateIcons()
{
    // Delete the existing icons
    deleteAllChildren();

    // Get the current production queue
    const MachLogFactory::ProductionLine& queue = pFactory_->productionLine();

    // Iterate through the queue and add an icon for each one
	MachLogFactory::ProductionLine::const_iterator it = queue.begin();
	int index = 1;

    for( ; it != queue.end(); ++it )
    {
        const MachLogProductionUnit& item = *(*it);
        MachProductionIcon* pIcon = new MachProductionIcon(this, pInGameScreen_, &item, index++);
        pIcon->setReleasedHandler([this](GuiButton* pButton) { onIconClicked(pButton); });
    }

    // Ensure redisplayed
    childrenUpdated();
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

void MachProductionIcons::doDisplay()
{
	pInGameScreen_->controlPanel().redrawAreaImmediate( *this );
	GuiSimpleScrollableList::doDisplay();
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

//static 
size_t MachProductionIcons::height()
{
	return MachProductionIcon::buttonHeight();
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

//static 
size_t MachProductionIcons::width()
{
    return (3 * MachProductionIcon::buttonWidth());
}

size_t MachProductionIcons::maxContentWidth() const
{
    int w = GuiSimpleScrollableList::width();
    std::cerr << "maxContentWidth: " << w << " bw: " << MachProductionIcon::buttonWidth() << std::endl;

    // MachProductionBank area: 2D box:   (1,770) to   (338,822) size 337x52

    // MachProductionIcons area: 2D box:   (17,0) to   (303,52) size 286x52

    // area width 337
    // left button 17
    // right button 17
    // total for icons: 303
    // corrected 303 to 294

    // maxContentWidth: 286 bw: 42
    // -34
    // cw = 252

    return (w / MachProductionIcon::buttonWidth()) * MachProductionIcon::buttonWidth();

    // return GuiSimpleScrollableList::width() - GuiSimpleScrollableList::width() % MachProductionIcon::buttonWidth();
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

void MachProductionIcons::updateProgress( float percentageComplete )
{
	if ( not children().empty() and not canScrollBackward() )
	{
		MachProductionIcon* pHeadOfList = _REINTERPRET_CAST( MachProductionIcon*, children().front() );
		pHeadOfList->updateProgress( percentageComplete );
	}
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

ostream& operator <<( ostream& o, const MachProductionIcons& t )
{
    o << "MachProductionIcons " << (void*)&t << " start" << std::endl;
    o << "MachProductionIcons " << (void*)&t << " end" << std::endl;
    return o;
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

/* End PRODICNS.CPP *************************************************/

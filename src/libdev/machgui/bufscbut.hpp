/*
 * B U F S C B U T . H P P 
 * (c) Charybdis Limited, 1998. All Rights Reserved
 */

/*
    MachGuiBufferScrollButton

    A brief description of the class should go in here
*/

#ifndef _BUFSCBUT_HPP
#define _BUFSCBUT_HPP

#include "base/base.hpp"

#include "gui/icon.hpp"
#include "gui/listobvr.hpp"

//Forward refs
class MachInGameScreen;
class GuiSimpleScrollableList;

class MachGuiBufferScrollButton : public GuiListObserver, public GuiIcon
// cannonical from revoked
{
public:
    enum ScrollDir { LEFT, RIGHT, FOWARD = RIGHT, BACKWARD = LEFT };

	MachGuiBufferScrollButton(	GuiDisplayable *pParent,
								const Gui::Coord& rel,
								const SysPathName& bitmap,
								GuiSimpleScrollableList* pList,
								ScrollDir dir,
								MachInGameScreen* pInGameScreen );

	virtual ~MachGuiBufferScrollButton();
	
	void CLASS_INVARIANT;

    static size_t width();

protected:
	virtual void listUpdated();

	virtual void doBeDepressed( const GuiMouseEvent& );
	virtual void doBeReleased( const GuiMouseEvent& );

	virtual const GuiBitmap& getBitmap() const;

private:
	// Operations revoked
	MachGuiBufferScrollButton( const MachGuiBufferScrollButton& );
	MachGuiBufferScrollButton& operator =( const MachGuiBufferScrollButton& );
	bool operator ==( const MachGuiBufferScrollButton& ) const;

	friend ostream& operator <<( ostream& o, const MachGuiBufferScrollButton& t );
	
	// Data members...
	ScrollDir scrollDir_;
	MachInGameScreen* pInGameScreen_;
};

#endif

/* End BUFSCBUT.HPP *************************************************/

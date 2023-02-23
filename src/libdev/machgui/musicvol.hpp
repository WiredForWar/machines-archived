/*
 * M U S I C V O L . H P P
 * (c) Charybdis Limited, 1998. All Rights Reserved
 */

/*
    MachGuiMusicVolumeSlideBar

    A brief description of the class should go in here
*/

#ifndef _MACHGUI_MUSICVOL_HPP
#define _MACHGUI_MUSICVOL_HPP

#include "base/base.hpp"
#include "machgui/slidebar.hpp"

class MachGuiStartupScreens;

class MachGuiMusicVolumeSlideBar : public MachGuiSlideBar
// Canonical form revoked
{
public:
    MachGuiMusicVolumeSlideBar(
        MachGuiStartupScreens* pStartupScreens,
        GuiDisplayable* pParent,
        Gui::Coord topLeft,
        size_t width);
    ~MachGuiMusicVolumeSlideBar() override;

    // Sets new CD volume. Called when slide button is moved.
    void valueChanged(float value) override;

    void CLASS_INVARIANT;

private:
    friend ostream& operator<<(ostream& o, const MachGuiMusicVolumeSlideBar& t);

    MachGuiMusicVolumeSlideBar(const MachGuiMusicVolumeSlideBar&);
    MachGuiMusicVolumeSlideBar& operator=(const MachGuiMusicVolumeSlideBar&);
};

#endif

/* End MUSICVOL.HPP *************************************************/

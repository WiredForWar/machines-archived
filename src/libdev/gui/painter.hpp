/*
 * P A I N T E R . H P P
 * (c) Charybdis Limited, 1997. All Rights Reserved.
 */

#ifndef _GUI_PAINTER_HPP
#define _GUI_PAINTER_HPP

#include "stdlib/string.hpp"

#include "gui/gui.hpp"

/* //////////////////////////////////////////////////////////////// */

class GuiBorderMetrics;
class GuiBorderDimensions;
class GuiFilledBorderColours;

// Interface for the GuiPainter Singleton
class IGuiPainter
{
public:
    virtual ~IGuiPainter() = 0;

    // Blit bitmap to backbuffer
    virtual void blit( 	const GuiBitmap& source,
                  const Gui::Box& sourceArea,
                  const Gui::Coord& dest
                  ) = 0;

    // Same as above only sourceArea is entire area of the source GuiBitmap
    virtual void blit( 	const GuiBitmap& source,
                  const Gui::Coord& dest
                  ) = 0;

    // Same as above only dest is defaulted to (0,0)
    virtual void blit( 	const GuiBitmap& source ) = 0;

    virtual void tile( 	const GuiBitmap& source,
                  const Gui::Box& sourceArea,
                  const Gui::Box& destArea
                  ) = 0;

    virtual void stretch( 	const GuiBitmap& source,
                     const Gui::Box& sourceArea,
                     const Gui::Box& destArea
                     ) = 0;

    virtual void stretch( const GuiBitmap& source,
                  const Gui::Box& destArea ) = 0;


    ///////////////////////////////

    virtual void filledRectangle( const Gui::Box&, const Gui::Colour& ) = 0;
    virtual void hollowRectangle( const Gui::Box&, const Gui::Colour&, unsigned thickness ) = 0;

    virtual void bevel( const Gui::Box& b,
                unsigned thickness,
                const Gui::Colour& hiCol,
                const Gui::Colour& loCol
                ) = 0;

    ///////////////////////////////

    virtual void line( const Gui::Coord& c1,
               const Gui::Coord& c2,
               const Gui::Colour&,
               unsigned thickness
               ) = 0;

    virtual void horizontalLine( const Gui::Coord& c1,
                         unsigned length,
                         const Gui::Colour&,
                         unsigned thickness
                         ) = 0;

    virtual void verticalLine( const Gui::Coord& c1,
                       unsigned height,
                       const Gui::Colour&,
                       unsigned thickness
                       ) = 0;

    ///////////////////////////////

    virtual void text( const Gui::Coord& c,
               const string& text,
               const Gui::Colour&
               ) = 0;

    virtual void rightAlignText(const Gui::Coord& c,
                        const string& theText,
                        const Gui::Colour& col
                        ) = 0;

    ///////////////////////////////

    virtual void filledBorder( const Gui::Coord& absCoord,
                       const GuiBorderDimensions&,
                       const GuiFilledBorderColours&,
                       const GuiBorderMetrics&
                       ) = 0;
};

class GuiPainter : public IGuiPainter
// Singleton
{
public:

	static GuiPainter& instance();

	///////////////////////////////

	// Blit bitmap to backbuffer
	void blit( 	const GuiBitmap& source,
			   	const Gui::Box& sourceArea,
			   	const Gui::Coord& dest ) override;

	// Same as above only sourceArea is entire area of the source GuiBitmap
	void blit( 	const GuiBitmap& source,
			   	const Gui::Coord& dest ) override;

	// Same as above only dest is defaulted to (0,0)
	void blit( 	const GuiBitmap& source ) override;

	void tile( 	const GuiBitmap& source,
				const Gui::Box& sourceArea,
				const Gui::Box& destArea ) override;

	void stretch( 	const GuiBitmap& source,
					const Gui::Box& sourceArea,
					const Gui::Box& destArea ) override;

	void stretch( const GuiBitmap& source,
				  const Gui::Box& destArea ) override;

	///////////////////////////////

	void filledRectangle( const Gui::Box&, const Gui::Colour& ) override;
	void hollowRectangle( const Gui::Box&, const Gui::Colour&, unsigned thickness ) override;

	void bevel( const Gui::Box& b,
				unsigned thickness,
				const Gui::Colour& hiCol,
				const Gui::Colour& loCol ) override;

	///////////////////////////////

	void line( const Gui::Coord& c1,
				const Gui::Coord& c2,
				const Gui::Colour&,
				unsigned thickness ) override;

	void horizontalLine( const Gui::Coord& c1,
							unsigned length,
							const Gui::Colour&,
							unsigned thickness ) override;

	void verticalLine( const Gui::Coord& c1,
							unsigned height,
							const Gui::Colour&,
							unsigned thickness ) override;

	///////////////////////////////

	void text( const Gui::Coord& c,
				const string& text,
				const Gui::Colour& ) override;

	void rightAlignText(const Gui::Coord& c,
						const string& theText,
						const Gui::Colour& col ) override;

	///////////////////////////////

	void filledBorder( const Gui::Coord& absCoord,
						const GuiBorderDimensions&,
						const GuiFilledBorderColours&,
						const GuiBorderMetrics& ) override;

private:
	GuiPainter( const GuiPainter& );
	GuiPainter& operator =( const GuiPainter& );
	bool operator ==( const GuiPainter& ) const;

	GuiPainter();
};

/* //////////////////////////////////////////////////////////////// */

#endif	//	#ifndef _GUI_PAINTER_HPP


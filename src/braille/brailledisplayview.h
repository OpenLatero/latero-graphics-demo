#pragma once

#include "../config.h"
#ifndef DISABLE_BRAILLE_DEMO

#include <gtkmm.h>
#include "braillegen.h"
#include <laterographics/tactiledisplaypainter.h>

class BrailleDisplayView : public Gtk::AspectFrame
{
public:
	BrailleDisplayView(BrailleGenPtr peer);
	virtual ~BrailleDisplayView() {}
		
	void SetBackground(Glib::RefPtr<Gdk::Pixbuf> buf);

protected:
	bool RefreshCursor();
	bool OnCheckPeer();
	void RefreshBackground();
	void OnDraw(const Cairo::RefPtr<Cairo::Context>& cr, int width, int height);

	BrailleGenPtr peer_;
	boost::posix_time::ptime bgUpdateTime_;

	Glib::RefPtr<Gdk::Pixbuf> bg_;
	const latero::Tactograph *dev_;
	double pos_;
	latero::BiasedImg tdState_;
	Gtk::DrawingArea drawingArea_;
	latero::graphics::TactileDisplayPainter tdPainter_;
};

#endif


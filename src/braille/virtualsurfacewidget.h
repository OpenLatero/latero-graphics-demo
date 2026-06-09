#pragma once

#include "../config.h"
#ifndef DISABLE_BRAILLE_DEMO

#include <gtkmm.h>
#include <latero/tactileimg.h>
#include <latero/tactograph.h>
#include <laterographics/point.h>
#include "braillegen.h"
#include <glibmm/main.h>

class VirtualSurfaceArea : public Gtk::DrawingArea
{
public:
	VirtualSurfaceArea(const latero::Tactograph *dev);
	virtual ~VirtualSurfaceArea() {};
	
	void SetBackground(Glib::RefPtr<Gdk::Pixbuf> buf);

	void SetDisplayState(double pos, const latero::BiasedImg &frame);

	//inline uint GetWidth() { return get_width(); };
	//inline uint GetHeight() { return get_height(); };

protected:
	void Invalidate();
	void OnDraw(const Cairo::RefPtr<Cairo::Context>& cr, int width, int height);

	Glib::RefPtr<Gdk::Pixbuf> bg_;

	const latero::Tactograph *dev_;

	double pos_;
	latero::BiasedImg tdState_;
};

/**
 * This widget represents the virtual surface explored by a tactile display. It is implement as an AspectFrame enclosing a 
 * DrawingArea so that the aspect ratio can be maintained.
 */
class VirtualSurfaceWidget : public Gtk::AspectFrame
{
public:
	VirtualSurfaceWidget(BrailleGenPtr peer);
	virtual ~VirtualSurfaceWidget() {}
	
protected:
	bool RefreshCursor();
	bool OnCheckPeer();
	void RefreshBackground();

	VirtualSurfaceArea surface_;
	BrailleGenPtr peer_;
	boost::posix_time::ptime bgUpdateTime_;
};

#endif


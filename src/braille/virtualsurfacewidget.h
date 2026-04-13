// -----------------------------------------------------------
//
// Copyright (c) 2015 by Vincent Levesque. All Rights Reserved.
//
// This file is part of latero-demo.
//
//    latero-demo is free software: you can redistribute it and/or modify
//    it under the terms of the GNU General Public License as published by
//    the Free Software Foundation, either version 3 of the License, or
//    (at your option) any later version.
//
//    latero-demo is distributed in the hope that it will be useful,
//    but WITHOUT ANY WARRANTY; without even the implied warranty of
//    MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
//    GNU General Public License for more details.
//
//    You should have received a copy of the GNU General Public License
//    along with latero-demo.  If not, see <http://www.gnu.org/licenses/>.
//
// -----------------------------------------------------------

#include "../config.h"
#ifndef DISABLE_BRAILLE_DEMO

#ifndef VIRTUAL_SURFACE_WIDGET_H
#define VIRTUAL_SURFACE_WIDGET_H

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

	inline uint GetWidth() { return get_allocation().get_width(); };
	inline uint GetHeight() { return get_allocation().get_height(); };

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
class VirtualSurfaceWidget : public Gtk::Box
{
public:
	VirtualSurfaceWidget(BrailleGenPtr peer) :
		Gtk::Box(Gtk::Orientation::VERTICAL),
 		frame_(0.5, 0.5, peer->Dev()->GetSurfaceWidth()/peer->Dev()->GetHeight(), false),
		surface_(peer->Dev()),
		peer_(peer)
	{
		append(frame_);
		frame_.set_child(surface_);

		Glib::signal_timeout().connect(
			sigc::mem_fun(*this, &VirtualSurfaceWidget::RefreshCursor),
			(uint)33, // ms
			Glib::PRIORITY_DEFAULT_IDLE);

		Glib::signal_timeout().connect(
			sigc::mem_fun(*this, &VirtualSurfaceWidget::OnCheckPeer),
			(uint)333, // ms
			Glib::PRIORITY_DEFAULT_IDLE);

		surface_.signal_resize().connect(
			[this](int, int) { RefreshBackground(); });
	}

	virtual ~VirtualSurfaceWidget() {}
	
protected:
	bool RefreshCursor();
	bool OnCheckPeer();
	void RefreshBackground();

	Gtk::AspectFrame frame_;
	VirtualSurfaceArea surface_;
	BrailleGenPtr peer_;
	boost::posix_time::ptime bgUpdateTime_;
};



#endif
#endif


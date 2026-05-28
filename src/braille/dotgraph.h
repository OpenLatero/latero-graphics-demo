#pragma once

#include "../config.h"
#ifndef DISABLE_BRAILLE_DEMO

#include "dot.h"
#include <laterographics/gtk/plot.h>
#include <gtkmm/box.h>

class DotGraph : public Gtk::Box
{
public:
	DotGraph(Dot *dot);
	virtual ~DotGraph() {};
	void Refresh();
protected:
	latero::graphics::gtk::Plot plot_;
	Dot *dot_;
};

#endif

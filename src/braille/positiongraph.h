#pragma once

#include "../config.h"
#ifndef DISABLE_BRAILLE_DEMO

#include "braillegen.h"
#include <laterographics/gtk/plot.h>
#include <gtkmm/grid.h>
#include <vector>

class PositionGraph : public Gtk::Grid
{
public:
	PositionGraph(BrailleGenPtr peer);
	virtual ~PositionGraph() {};

protected:
	bool Monitor();
	bool OnRefreshRow();

	std::vector<latero::graphics::gtk::Plot*> plots_;
	BrailleGenPtr peer_;
	uint y_;
	boost::posix_time::ptime lastUpdated_;
};

#endif

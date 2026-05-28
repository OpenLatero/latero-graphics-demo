#include "../config.h"
#ifndef DISABLE_BRAILLE_DEMO

#include "dotgraph.h"

#define NB_POINTS 1000

DotGraph::DotGraph(Dot *dot) :
	Gtk::Box(Gtk::Orientation::VERTICAL),
	plot_("blue", "white"),
	dot_(dot)
{	
	plot_.set_size_request(200, 200);
	plot_.SetRangeX(-1.0, 1.0);
	plot_.SetRangeY(0.0, 1.0);
	append(plot_);
}

void DotGraph::Refresh()
{
	plot_.Clear();
	float incr = 2.0 / NB_POINTS;
	for (float x=-1.0; x<1.0; x+=incr)
	{
		float y = dot_->GetValue_(x);
		plot_.InsertPoint(x, y);
	}
	plot_.Draw();
}


#endif

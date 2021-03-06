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

#ifndef DOT_GRAPH_H
#define DOT_GRAPH_H

#include "dot.h"
#include <laterographics/gtk/plot.h>
#include <gtkmm/box.h>

class DotGraph : public Gtk::VBox
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
#endif

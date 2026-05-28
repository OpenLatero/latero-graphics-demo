#pragma once

#include "../config.h"
#ifndef DISABLE_BRAILLE_DEMO

#include <gtkmm.h>
#include "dot.h"
#include "dotgraph.h"

class DotSideWidget : public Gtk::Box
{
public:
	DotSideWidget();
	Dot::SideParams Get();
	void Set(const Dot::SideParams &p);
	void AddShapes(const std::vector<std::string> &shapes);
	void Disable(bool v);
	void OnChange();
	sigc::signal<void()> signal_value_changed;

protected:
    Glib::RefPtr<Gtk::Adjustment> radiusAdj_;
    Glib::RefPtr<Gtk::Adjustment> plateauAdj_;
    Glib::RefPtr<Gtk::Adjustment> txAmpAdj_;
    Glib::RefPtr<Gtk::Adjustment> txNbCyclesAdj_;
    Glib::RefPtr<Gtk::StringList> shapeList_;
	Gtk::DropDown shapeDropDown_;
};


class DotWidget : public Gtk::Box
{
public:
	DotWidget(Dot *peer);
	void OnChange();
	bool LockedSides();

	sigc::signal<void()> signal_value_changed;

protected:

	DotSideWidget left_;
	DotSideWidget right_;
	Gtk::CheckButton sideLockCheck_;
	Dot *peer_;
	DotGraph *graph_;
};

#endif

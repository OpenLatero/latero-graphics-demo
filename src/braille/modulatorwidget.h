#pragma once

#include "../config.h"
#ifndef DISABLE_BRAILLE_DEMO

#include <gtkmm.h>
#include "modulator.h"

class ModulatorWidget : public Gtk::Grid
{
public:
	ModulatorWidget(Modulator *peer);
	virtual ~ModulatorWidget();

protected:
	void OnChange();
	void OnModeChange();

	Modulator *peer_;

    Glib::RefPtr<Gtk::Adjustment> ampAdj_;
    Glib::RefPtr<Gtk::Adjustment> rampMinAdj_, rampMaxAdj_;
    Glib::RefPtr<Gtk::Adjustment> rampMinAmpAdj_, rampMaxAmpAdj_;
    Glib::RefPtr<Gtk::Adjustment> maxRiseRateAdj_, maxFallRateAdj_;
  	Gtk::CheckButton fixedMode_, velMode_;

	Gtk::Box fixedBox_;
	Gtk::Box velBox_;
};

#endif

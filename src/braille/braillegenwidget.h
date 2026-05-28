#pragma once

#include "../config.h"
#ifndef DISABLE_BRAILLE_DEMO

#include "braillegen.h"
#include <gtkmm/checkbutton.h>
#include "braillestringwidget.h"
#include "dotwidget.h"
#include "modulatorwidget.h"
//#include <laterographics/generatorwidget.h>

class BrailleGenWidget : public Gtk::Box
{
public:
	BrailleGenWidget(BrailleGenPtr peer);
	virtual ~BrailleGenWidget();

protected:
	void OnStandardButton();
	void OnScaledButton();
	void OnHalfScaledButton();
	void OnVBDButton();


	void OnChange();	
	Gtk::Widget *CreateVizWidget();
	Gtk::Widget *CreateModeWidget();
	Gtk::Widget *CreateParamsWidget();
	Gtk::Widget *CreateVibWidget();

 	BrailleGenPtr peer_;

	BrailleStringWidget strWidget_;
	DotWidget dot_;
	DotWidget vibDot_;
    Glib::RefPtr<Gtk::Adjustment> dotWidthAdj_;
    Glib::RefPtr<Gtk::Adjustment> intraDotDistAdj_;
    Glib::RefPtr<Gtk::Adjustment> interDotDistAdj_;
    Glib::RefPtr<Gtk::Adjustment> offsetAdj_;
    Glib::RefPtr<Gtk::Adjustment> vibFreqAdj_;
	ModulatorWidget vibModWidget_;

	Gtk::CheckButton mode_[BRAILLE_MODE_SIZE];
	Gtk::CheckButton invertCheck_;
};

#endif

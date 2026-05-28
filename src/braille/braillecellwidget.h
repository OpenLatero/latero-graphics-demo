#pragma once

#include "../config.h"
#ifndef DISABLE_BRAILLE_DEMO

#include <gtkmm/box.h>
#include <gtkmm/checkbutton.h>
#include <gtkmm/frame.h>
#include "braillecell.h"

class BrailleCellWidget : public Gtk::Frame
{
public:
	BrailleCellWidget(BrailleCell *peer);
	virtual ~BrailleCellWidget() {};
	void Refresh();
	sigc::signal<void()> signal_value_changed;
	void SetPattern(unsigned char pattern);
protected:

	BrailleCell *peer_;	
	bool disableSignals_;
	void OnChange();
	Gtk::CheckButton dots_[2][3];
};

#endif

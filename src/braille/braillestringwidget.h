#pragma once

#include "../config.h"
#ifndef DISABLE_BRAILLE_DEMO

#include <gtkmm.h>
#include "braillestring.h"
#include "braillecellwidget.h"

class BrailleStringWidget : public Gtk::Frame
{
public:
	BrailleStringWidget(BrailleString *peer);
	virtual ~BrailleStringWidget();

	sigc::signal<void()> signal_value_changed;
protected:
	void CreateWords();
	void OnModeChange();
	void OnCellChange();
	void OnTextChange();
	void OnRandomClicked();
	void OnWordClicked();
	void OnInsertText(const Glib::ustring& str, int* pos);

	Gtk::CheckButton cellMode_;
	Gtk::CheckButton textMode_;
	Gtk::Box cellBox_;
	Gtk::Box textBox_;


	Gtk::Button randomButton_;
	Gtk::Button wordButton_;

	Gtk::Entry entry_;
	std::vector<BrailleCellWidget*> cell_;
	BrailleString *peer_;
	std::vector<std::string> words_;
};

#endif

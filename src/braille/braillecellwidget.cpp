#include "../config.h"
#ifndef DISABLE_BRAILLE_DEMO

#include "braillecellwidget.h"
#include <gtkmm.h>

BrailleCellWidget::BrailleCellWidget(BrailleCell *peer):
	peer_(peer),
	disableSignals_(false)
{
	Refresh();

	Gtk::Grid *grid = new Gtk::Grid();
	set_child(*manage(grid));

	for (uint x=0; x<2; ++x)
	{
		for (uint y=0; y<3; ++y)
		{
			grid->attach(dots_[x][y], x, y, 1,1);
			dots_[x][y].signal_toggled().connect(
				sigc::mem_fun(*this, &BrailleCellWidget::OnChange));
			dots_[x][y].set_active(peer->Get(x,y));
		}
	}
}

void BrailleCellWidget::OnChange()
{
	if (!disableSignals_)
	{
		for (uint x=0; x<2; ++x)
			for (uint y=0; y<3; ++y)
				peer_->Set(x,y,dots_[x][y].get_active());

		signal_value_changed();
	}
}

void BrailleCellWidget::Refresh()
{
	for (uint x=0; x<2; ++x)
		for (uint y=0; y<3; ++y)
			dots_[x][y].set_active(peer_->Get(x,y));
}

void BrailleCellWidget::SetPattern(unsigned char pattern)
{
	disableSignals_ = true;
	dots_[0][0].set_active(pattern&DOT_1);
	dots_[0][1].set_active(pattern&DOT_2);
	dots_[0][2].set_active(pattern&DOT_3);
	dots_[1][0].set_active(pattern&DOT_4);
	dots_[1][1].set_active(pattern&DOT_5);
	dots_[1][2].set_active(pattern&DOT_6);
	disableSignals_ = false;
}

#endif

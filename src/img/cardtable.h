#pragma once

#include "../config.h"
#ifndef DISABLE_GRAPHICS_DEMO

#include <gtkmm.h>
#include "card.h"

class CardTable : public Gtk::Grid
{
public:
	CardTable(uint sx, uint sy);
	~CardTable();
	void SetCards(std::vector<CardPtr> cards);
	void RemoveCards();

protected:
	uint sx_, sy_;
};

#endif


#pragma once

#include "../config.h"
#ifndef DISABLE_GRAPHICS_DEMO

#include <gtkmm.h>
#include "card.h"

class CardTable : public Gtk::Box
{
public:
	CardTable(uint sx, uint sy);
	~CardTable();
	void SetCards(std::vector<CardPtr> cards);

	void RemoveCards();
	CardPtr GetFirstCard() { return cards_.empty() ? nullptr : cards_[0]; }

protected:
	void SetCard(uint x, uint y, CardPtr card);
	
	Gtk::Grid grid_;
    std::vector<CardPtr> cards_;
	uint sx_, sy_;
};

#endif


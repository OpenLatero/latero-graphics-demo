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
	void SetCards(std::vector<CardPtr> &cards);
	void SetCard(uint x, uint y, CardPtr card);
	void RemoveCards();
	void GetLocation(CardPtr card, int &x, int &y);
	CardPtr GetCard(uint x, uint y);
	CardPtr GetFirstCard() { return cards_.empty() ? nullptr : cards_[0]; }

protected:
	
	Gtk::Grid grid_;
    std::vector<CardPtr> cards_;
	uint sx_, sy_;
};

#endif


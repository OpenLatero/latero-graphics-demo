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
	void SetCards(std::vector<Card*> &cards);
	void SetCard(uint x, uint y, Card* card);
	void RemoveCards();
	void GetLocation(Card* card, int &x, int &y);
	Card* GetCard(uint x, uint y);

protected:
	
	Gtk::Grid grid_;
    std::vector<Card*> cards_;
	uint sx_, sy_;
};

#endif


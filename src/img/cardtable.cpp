#include "../config.h"
#ifndef DISABLE_GRAPHICS_DEMO

#include "cardtable.h"

CardTable::CardTable(uint sx, uint sy) :
	sx_(sx), sy_(sy)
{
	append(grid_);
	grid_.set_margin(10);
	grid_.set_row_spacing(10);
	grid_.set_column_spacing(10);
}

CardTable::~CardTable()
{
}

void CardTable::SetCards(std::vector<Card*> &cards)
{
	RemoveCards();
    cards_ = cards;
	for (uint x=0; x<sx_; ++x)
		for (uint y=0; y<sy_; ++y)
			SetCard(x, y, cards[y*sx_+x]);
}

void CardTable::SetCard(uint x, uint y, Card* card)
{
	/** @todo: doesn't work if a card is already at that location */
	grid_.attach(*card, x, y, 1, 1);
	card->set_vexpand(true);
	card->set_hexpand(true);	
    cards_[y*sx_+x] = card;
}

void CardTable::RemoveCards()
{
    for (auto card : cards_)
        grid_.remove(*card);
    cards_.clear();
}

void CardTable::GetLocation(Card* card, int &x, int &y)
{
	for (x=0; x<(int)sx_; ++x)
		for (y=0; y<(int)sy_; ++y)
			if (GetCard(x,y) == card)
				return;
	assert(0); 
}

Card* CardTable::GetCard(uint x, uint y)
{
	assert(x<sx_ && y<sy_);
	return cards_[y*sx_+x];
}
#endif

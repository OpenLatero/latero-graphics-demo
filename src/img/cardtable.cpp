// -----------------------------------------------------------
//
// Copyright (c) 2015 by Vincent Levesque. All Rights Reserved.
//
// This file is part of latero-demo.
//
//    latero-demo is free software: you can redistribute it and/or modify
//    it under the terms of the GNU General Public License as published by
//    the Free Software Foundation, either version 3 of the License, or
//    (at your option) any later version.
//
//    latero-demo is distributed in the hope that it will be useful,
//    but WITHOUT ANY WARRANTY; without even the implied warranty of
//    MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
//    GNU General Public License for more details.
//
//    You should have received a copy of the GNU General Public License
//    along with latero-demo.  If not, see <http://www.gnu.org/licenses/>.
//
// -----------------------------------------------------------

#include "../config.h"
#ifndef DISABLE_GRAPHICS_DEMO

#include "cardtable.h"

CardTable::CardTable(uint sx, uint sy) :
	sx_(sx), sy_(sy)
{
	add(grid_);
	grid_.set_border_width(10);
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
	card->UpdateImg();
}

void CardTable::RemoveCards()
{
    auto children = grid_.get_children();
    for (auto child : children)
    {
        Card *card = (Card*)child;
        card->ClearImg();
        grid_.remove(*child);
    }
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
	return cards_[y*sy_+x];
}
#endif

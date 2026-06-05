#include "../config.h"
#ifndef DISABLE_GRAPHICS_DEMO

#include "cardtable.h"

CardTable::CardTable(uint sx, uint sy) :
	sx_(sx), sy_(sy)
{
	set_margin(10);
	set_row_spacing(10);
	set_column_spacing(10);
}

CardTable::~CardTable()
{
}

void CardTable::SetCards(std::vector<CardPtr> cards)
{
	for (uint x=0; x<sx_; ++x)
	{
		for (uint y=0; y<sy_; ++y)
		{
			auto card = cards[y*sx_+x];
			card->set_vexpand(true);
			card->set_hexpand(true);	
			attach(*card, x, y, 1, 1);
		}
	}	
}

void CardTable::RemoveCards()
{
	for (auto* child : get_children())
    	remove(*child);
}


#endif

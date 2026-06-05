#include "../config.h"
#ifndef DISABLE_GRAPHICS_DEMO

#include "cardcollection.h"
#include <iostream>

CardCollection::CardCollection()
{
}

CardCollection::~CardCollection()
{
	for (uint i=0; i<size(); ++i)
		delete (*this)[i];
	clear();
}



void CardCollection::LoadCardSet(std::string file, const latero::Tactograph *dev, uint scale)
{
	CardSet *cs = new CardSet();
	cs->Load(file, dev, scale);
	push_back(cs);
}

#endif

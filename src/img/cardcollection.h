#pragma once

#include "../config.h"
#ifndef DISABLE_GRAPHICS_DEMO

#include "cardset.h"

class CardCollection : public std::vector<CardSet*>
{
public:
	CardCollection();
	virtual ~CardCollection();

	bool Load(std::string file, const latero::Tactograph *dev, uint scale);

};

#endif

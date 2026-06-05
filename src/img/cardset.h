#pragma once

#include "../config.h"
#ifndef DISABLE_GRAPHICS_DEMO

#include <vector>
#include <laterographics/generator.h>
#include "card.h"

class CardSet : public std::vector<Card*>
{
public:
	CardSet();
	CardSet(std::string file, const latero::Tactograph *dev, uint scale);
	virtual ~CardSet();

	bool Load(std::string file, const latero::Tactograph *dev, uint scale);

	inline void DeleteCards()
	{
		while (size())
		{
			delete back();
			pop_back();
		}
	}

	bool LoadGenerator(std::string file, const latero::Tactograph *dev, uint scale);
};

#endif

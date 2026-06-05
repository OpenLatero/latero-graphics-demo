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

	std::string GetName() { return name_; }
private:
	std::string name_;
	std::vector<latero::graphics::GeneratorPtr> managedGenerators_;

};

#endif

#pragma once

#include "../config.h"
#ifndef DISABLE_GRAPHICS_DEMO

#include <vector>
#include <laterographics/generator.h>
#include "card.h"

class CardSet : public std::vector<CardPtr>
{
public:
	CardSet();
	virtual ~CardSet();
};

#endif

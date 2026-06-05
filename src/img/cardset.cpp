#include "../config.h"
#ifndef DISABLE_GRAPHICS_DEMO

#include "cardset.h"
#include <iostream>
#include <random>
#include "settings.h"

CardSet::CardSet()
{	
}



CardSet::~CardSet()
{
	DeleteCards();
}



bool CardSet::LoadGenerator(std::string file, const latero::Tactograph *dev, uint scale)
{
	if (size() < 12)
	{
		latero::graphics::GeneratorPtr gen = latero::graphics::Generator::Create(file, dev);
		Card *c = new Card(gen,DefaultCardWidth, DefaultCardWidth * dev->GetSurfaceHeight() / dev->GetSurfaceWidth(), scale);
		push_back(c);
	}
	return true;
}

#endif

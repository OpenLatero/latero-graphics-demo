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

	CardSet *GetSet(std::string name)
	{
		for (uint i=0; i<size(); ++i)
			if ((*this)[i]->GetName() == name)
				return (*this)[i];
		return NULL;
	}


	std::string GetName() { return name_; }
private:
	std::string name_;

};

#endif

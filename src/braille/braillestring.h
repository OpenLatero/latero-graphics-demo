#pragma once

#include "../config.h"
#ifndef DISABLE_BRAILLE_DEMO

#include "braillecell.h"
#include <string>
#include <vector>
#include <laterographics/modifiable.h>

class BrailleString : public latero::graphics::Modifiable
{
public:
	BrailleString(unsigned int size);
	BrailleString(const BrailleString& p);
	BrailleString operator= (const BrailleString& s);
	virtual ~BrailleString();

	void Set(std::string str);
	std::string Get();
	std::string GetPattern();
	
	unsigned int GetSize() const { return (unsigned int)cells_.size(); }
	BrailleCell* GetCell(unsigned int i);
	std::string GetDesc(std::string prefix);

public:
	std::vector<BrailleCell> cells_;
};

#endif

#include "../config.h"
#ifndef DISABLE_BRAILLE_DEMO

#include "braillestring.h"
#include <sstream>

BrailleString::BrailleString(unsigned int size)
{
	for (unsigned int i=0; i<size; ++i)
		cells_.push_back(BrailleCell());
}

BrailleString::~BrailleString()
{
}

void BrailleString::Set(std::string str)
{
	SetLastModified();
	for (unsigned int i=0; (i<str.length()) && (i<cells_.size()); ++i)
		cells_[i].SetLetter(str.at(i));
}

BrailleCell* BrailleString::GetCell(unsigned int i)
{
	if (i<cells_.size())
		return &cells_[i];
	else
		return NULL;
}

std::string BrailleString::Get()
{
	std::stringstream str;
	for (unsigned int i=0; i<cells_.size(); ++i)
		str << cells_[i].GetLetter();
	return str.str();
}

std::string BrailleString::GetPattern()
{
	std::stringstream str;
	for (unsigned int i=0; i<cells_.size(); ++i)
		str << cells_[i].GetPattern();
	return str.str();
}

std::string BrailleString::GetDesc(std::string prefix)
{
	std::stringstream stream;
	stream << prefix << "string: " << Get() << "\n";
	return stream.str();
}

BrailleString::BrailleString(const BrailleString& p)
{
	LATERO_GRAPHICS_GUARD
	cells_ = p.cells_;
}

BrailleString BrailleString::operator= (const BrailleString& s)
{ 
	if (&s == this) return *this;
	LATERO_GRAPHICS_GUARD
	cells_ = s.cells_;
	return *this; 
};

#endif

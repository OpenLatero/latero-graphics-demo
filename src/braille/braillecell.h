#pragma once

#include "../config.h"
#ifndef DISABLE_BRAILLE_DEMO

#define DOT_1 (1<<0)
#define DOT_2 (1<<1)
#define DOT_3 (1<<2)
#define DOT_4 (1<<3)
#define DOT_5 (1<<4)
#define DOT_6 (1<<5)

class BrailleCell
{
public:
	BrailleCell();
	BrailleCell(const BrailleCell& p);
	BrailleCell operator=(const BrailleCell& s);

	void Set(unsigned int x, unsigned int y, bool v);
	void Set_(unsigned int x, unsigned int y, bool v);
	bool Get(unsigned int x, unsigned int y);
	bool Get_(unsigned int x, unsigned int y);

	void SetLetter(char letter);
	char GetLetter();

	unsigned char GetPattern();

protected:
	unsigned char Encode(char c);
	char Decode(unsigned char b);

	unsigned char dot_;
};

#endif

#pragma once

#include "../config.h"
#ifndef DISABLE_BRAILLE_DEMO

#include "../demo.h"
#include "braillegen.h"

namespace BrailleDemo {

class Demo : public ::Demo
{
public:
	Demo(const latero::Tactograph *dev);
	virtual ~Demo() {};
	virtual latero::graphics::GeneratorPtr Gen() { return gen_; };
protected:
	BrailleGenPtr gen_;
};

}; // namespace

#endif

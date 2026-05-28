#include "../config.h"
#ifndef DISABLE_BRAILLE_DEMO

#include "demo.h"

namespace BrailleDemo {

Demo::Demo(const latero::Tactograph *dev)
{
	gen_ = BrailleGen::Create(dev);
	set_child(*gen_->CreateWidget(gen_));
};

}; // namespace

#endif

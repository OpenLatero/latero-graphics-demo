#include "../config.h"
#ifndef DISABLE_GRAPHICS_DEMO

#include "card.h"
#include <iostream>

Card::Card(latero::graphics::GeneratorPtr gen) :
	gen_(gen),
	img_(gen->Dev(), gen_, true)
{  
	img_.ShowCursor(false);
	assert(gen);
	append(img_);
	clickGesture_ = Gtk::GestureClick::create();
	clickGesture_->set_button(1);
	clickGesture_->signal_pressed().connect(
		[this](int, double, double) { signal_clicked(); });
	add_controller(clickGesture_);
}

Card::~Card()
{
}


#endif

#include "../config.h"
#ifndef DISABLE_GRAPHICS_DEMO

#include "card.h"
#include <iostream>

Card::Card(latero::graphics::GeneratorPtr gen) :
	gen_(gen),
	img_(gen->Dev())
{  
	assert(gen);
	append(img_);
	clickGesture_ = Gtk::GestureClick::create();
	clickGesture_->set_button(1);
	clickGesture_->signal_pressed().connect(
		[this](int, double, double) { signal_clicked(); });
	add_controller(clickGesture_);
	img_.Set(GetIllustration());

}

Card::~Card()
{
}

latero::graphics::gtk::Animation Card::GetIllustration()
{
	return gen_->GetIllustration(1000,boost::posix_time::seconds(0));
}

#endif

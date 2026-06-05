#include "../config.h"
#ifndef DISABLE_GRAPHICS_DEMO

#include "card.h"
#include <iostream>

Card::Card(latero::graphics::GeneratorPtr gen) :
	gen_(gen),
	img_(gen->Dev())
{  
	assert(gen);

	// too slow to be done at runtime
	largeFaceUpAnim_ = gen_->GetIllustration(1000,boost::posix_time::seconds(0));
	//faceUpAnim_ = gen->GetIllustration(width, height);
	faceUpAnim_ = largeFaceUpAnim_; // TODO: this makes the image look nicer... try to do use exactly the right size instead? 

	append(img_);
	clickGesture_ = Gtk::GestureClick::create();
	clickGesture_->set_button(1);
	clickGesture_->signal_pressed().connect(
		[this](int, double, double) { signal_clicked(shared_from_this()); });
	add_controller(clickGesture_);
	img_.Set(faceUpAnim_);

}

Card::~Card()
{
}

latero::graphics::gtk::Animation Card::GetLargeFaceUpAnim()
{
	return largeFaceUpAnim_;
}

#endif

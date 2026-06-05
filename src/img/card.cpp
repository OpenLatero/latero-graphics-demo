#include "../config.h"
#ifndef DISABLE_GRAPHICS_DEMO

#include "card.h"

Card::Card(latero::graphics::GeneratorPtr gen, uint width, uint height, uint scale) :
	gen_(gen),
	width_(width), 
	height_(height),
	img_(gen->Dev())
{  
	img_.SetRounded();
	assert(gen);

	// too slow to be done at runtime
	largeFaceUpAnim_ = gen_->GetIllustration(width*scale,boost::posix_time::seconds(0));
	//faceUpAnim_ = gen->GetIllustration(width, height);
	faceUpAnim_ = largeFaceUpAnim_; // TODO: this makes the image look nicer... try to do use exactly the right size instead? 

	Initialize();
}



Card::Card(const Card& p) :
	img_(p.gen_->Dev())
{
	img_.SetRounded();
	faceUpAnim_ = p.faceUpAnim_;
	width_ = p.width_;
	height_ = p.height_;
	gen_ = p.gen_;
	largeFaceUpAnim_ = p.largeFaceUpAnim_;

	Initialize();
};

Card::~Card()
{
}


void Card::Initialize()
{
	append(img_);
	clickGesture_ = Gtk::GestureClick::create();
	clickGesture_->set_button(0); // listen to all buttons
	clickGesture_->signal_pressed().connect(
		sigc::mem_fun(*this, &Card::OnClicked));
	add_controller(clickGesture_);
}

Card Card::operator= (const Card& p)
{ 
	if (&p == this) return *this;
	largeFaceUpAnim_ = p.largeFaceUpAnim_;
	faceUpAnim_ = p.faceUpAnim_;
	width_ = p.width_;
	height_ = p.height_;
	gen_ = p.gen_;
	UpdateImg();
	return *this;
};

void Card::ClearImg()
{
	img_.Clear(0xffffffff);
}


void Card::UpdateImg()
{
	img_.Set(faceUpAnim_);
}

void Card::OnClicked(int n_press, double x, double y)
{
	guint button = clickGesture_->get_current_button();
	if (button == 1)
		signal_clicked1(this);
	else if (button == 3)
		signal_clicked3(this);
}

void Card::SetDisplayState(const latero::graphics::Point &center, double angle, const latero::BiasedImg &frame)
{
	img_.SetDisplayState(center, angle, frame);
}

void Card::HideTD()
{
	img_.ShowCursor(false);
}


latero::graphics::gtk::Animation Card::GetLargeFaceUpAnim()
{
	return largeFaceUpAnim_;
}

#endif

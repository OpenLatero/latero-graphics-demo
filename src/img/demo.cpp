#include "../config.h"
#ifndef DISABLE_GRAPHICS_DEMO

#include "demo.h"
#include "settings.h"
#include "../generatorhandle.h"

#define REFRESH_INTERVAL_MS 30
#define SCALE_UP_FACTOR 5

namespace ImgDemo {

Demo::Demo(const latero::Tactograph *dev) :
	currentSet_(NULL),
	zoomImg_(dev),
	demoTable_(NbCardsX,NbCardsY),
	curCard_(NULL),
	keyLocation_(0,0),
	currentSetIdx_(0)
{ 
	gen_ = GeneratorHandlePtr(new GeneratorHandle(dev));

	//zoomImg_.SetRounded();
	cardSets_.Load(media_dir+"/img/main.col", dev, SCALE_UP_FACTOR);

	for (uint i=0; i<cardSets_.size(); ++i)
	{
		std::string name = cardSets_[i]->GetName();
		auto *button = Gtk::make_managed<Gtk::CheckButton>(name);
		if (i > 0) button->set_group(*setActions_[0]);
		setActions_.push_back(button);
	}
	if (!setActions_.empty())
		setActions_[0]->set_active(true);

	auto box = Gtk::make_managed<Gtk::Box>(Gtk::Orientation::VERTICAL);
	auto hbox = Gtk::make_managed<Gtk::Box>(Gtk::Orientation::HORIZONTAL);
	auto prevButton = Gtk::make_managed<Gtk::Button>("<");
	auto nextButton = Gtk::make_managed<Gtk::Button>(">");

	set_child(*box);
	zoomImg_.set_vexpand(true);
	box->append(zoomImg_);
	box->append(*hbox);
		hbox->append(*prevButton);
		demoTable_.set_hexpand(true);
		hbox->append(demoTable_);
		hbox->append(*nextButton);

	auto clickGesture = Gtk::GestureClick::create();
	clickGesture->set_button(3);
	clickGesture->signal_pressed().connect(
		sigc::mem_fun(*this, &Demo::OnBoardClick));
	add_controller(clickGesture);

	prevButton->signal_clicked().connect(sigc::mem_fun(*this, &Demo::OnPrevSet));
	nextButton->signal_clicked().connect(sigc::mem_fun(*this, &Demo::OnNextSet));

	UpdateSet();

	 Glib::signal_timeout().connect(
		sigc::mem_fun(*this, &Demo::OnIdle),
		REFRESH_INTERVAL_MS,
		Glib::PRIORITY_DEFAULT_IDLE); 

	zoomImg_.ShowCursor();

	auto keyController = Gtk::EventControllerKey::create();
	keyController->signal_key_pressed().connect(
		sigc::mem_fun(*this, &Demo::OnKeyPress), false);
	add_controller(keyController);
}

Demo::~Demo()
{
	ClearSet();
}


void Demo::UpdateSet()
{
	for (uint i=0; i<setActions_.size(); ++i)
	{
		if (setActions_[i]->get_active())
		{
			currentSetIdx_ = i;
			std::stringstream id;
			id << "Set" << i;
			// OLD: CardSet *set = cardSets_.GetSet(setActions_[i]->property_label().get_value());
			// NEW: Use get_label() method instead
			CardSet *set = cardSets_.GetSet(setActions_[i]->get_label());
			LoadSet(*set);
		}
	}
	keyLocation_.x =  keyLocation_.y = 0;
	OnDemoClick(GetCard(keyLocation_.x, keyLocation_.y));
}

void Demo::UpdateMode()
{
}

void Demo::OnSetChanged()
{
	UpdateSet();
}

void Demo::ClearSet()
{
	demoTable_.RemoveCards();
	zoomImg_.Clear(0xffffffff);
	demoCards_.DeleteCards();
	currentSet_ = NULL;
	SetCurrentCard(NULL);
}


void Demo::LoadSet(const CardSet &set)
{
	if (&set == currentSet_)
		return;
	ClearSet();

	currentSet_ = &set;
	for (uint i=0; i<set.size(); ++i)
		demoCards_.push_back(new Card(*set[i]));

	for (uint i=0; i<demoCards_.size(); ++i)
	{
 		demoCards_[i]->signal_clicked1.connect(sigc::mem_fun(*this, &Demo::OnDemoClick));
	}

	demoTable_.SetCards(demoCards_);
}

void Demo::Reset()
{
	zoomImg_.Clear(0xffffffff);
	SetCurrentCard(NULL);
}

void Demo::OnRightClick(Card* card)
{
	Reset();
}

void Demo::UpdateZoom(Card* card)
{
	latero::graphics::gtk::Animation  anim = card->GetLargeFaceUpAnim();
	zoomImg_.Set(anim);
}

void Demo::OnDemoClick(Card* card)
{
	Reset();
	SetCurrentCard(card);
	UpdateZoom(card);

	demoTable_.GetLocation(card, keyLocation_.x, keyLocation_.y);
}


void Demo::OnBoardClick(int n_press, double x, double y)
{
	Reset();
}


bool Demo::OnIdle()
{
	if (curCard_)
	{
		latero::BiasedImg frame = gen_->GetLatestFrame();
		latero::graphics::Point center = gen_->GetDisplayCenter();
		double angle = gen_->GetDisplayOrientation();
		zoomImg_.SetDisplayState(center, angle, frame);
	}


	 Glib::signal_timeout().connect(
		sigc::mem_fun(*this, &Demo::OnIdle),	
		REFRESH_INTERVAL_MS,
		Glib::PRIORITY_DEFAULT_IDLE); 

	return false;
}

void Demo::OnShowCursor()
{
}

bool Demo::OnKeyPress(guint keyval, guint keycode, Gdk::ModifierType state)
{
	const auto key = keyval;

	// select
	if ((key == GDK_KEY_KP_5) || (key == GDK_KEY_space))
		OnDemoClick(GetCard(keyLocation_.x, keyLocation_.y));

	// move up
	if ((key == GDK_KEY_KP_7) || (key == GDK_KEY_KP_8) || (key == GDK_KEY_KP_9) || (key == GDK_KEY_Up))
		keyLocation_.y--;

	if ((key == GDK_KEY_KP_1) || (key == GDK_KEY_KP_2) || (key == GDK_KEY_KP_3) || (key == GDK_KEY_Down))
		keyLocation_.y++;
	
	if ((key == GDK_KEY_KP_7) || (key == GDK_KEY_KP_4) || (key == GDK_KEY_KP_1) || (key == GDK_KEY_Left))
		keyLocation_.x--;

	if ((key == GDK_KEY_KP_9) || (key == GDK_KEY_KP_6) || (key == GDK_KEY_KP_3) || (key == GDK_KEY_Right))
		keyLocation_.x++;

	if (keyLocation_.x > 5)
	{
		keyLocation_.x = 0;
		currentSetIdx_ = (currentSetIdx_+1)%setActions_.size();
		setActions_[currentSetIdx_]->set_active();
		OnDemoClick(GetCard(keyLocation_.x, keyLocation_.y));
	}
	else if (keyLocation_.x < 0)
	{
		currentSetIdx_--;
		if (currentSetIdx_<0) currentSetIdx_  = (int)setActions_.size()-1;
		setActions_[currentSetIdx_]->set_active();
		keyLocation_.x = 5;
		OnDemoClick(GetCard(keyLocation_.x, keyLocation_.y));
	}

	keyLocation_.y = keyLocation_.y%2;
	if (keyLocation_.y<0) keyLocation_.y = 1;

	return true;
}

void Demo::OnPrevSet()
{
	currentSetIdx_--;
	if (currentSetIdx_<0)
		currentSetIdx_ = (currentSetIdx_+1)%setActions_.size();
	setActions_[currentSetIdx_]->set_active();
	UpdateSet();
}

void Demo::OnNextSet()
{
	currentSetIdx_ = (currentSetIdx_+1)%setActions_.size();
	setActions_[currentSetIdx_]->set_active();
	UpdateSet();
}

Card *Demo::GetCard(int x, int y)
{
	assert((x>=0)&&(x<6));
	assert((y>=0)&&(y<2));
	return demoTable_.GetCard(x,y);
}

void Demo::SetCurrentCard(Card *card)
{
	curCard_ = card;
	if (card)
		gen_->SetGenerator(card->GetGenerator());
	else
		gen_->SetGenerator(latero::graphics::GeneratorPtr());
}

latero::graphics::GeneratorPtr Demo::Gen() { return gen_; };

} // namespace

#endif

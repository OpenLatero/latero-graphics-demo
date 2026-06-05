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
	currentSetIdx_(0)
{ 
	gen_ = GeneratorHandlePtr(new GeneratorHandle(dev));

	cardCollection_.Load(media_dir+"/img/main.col", dev, SCALE_UP_FACTOR);

	auto box = Gtk::make_managed<Gtk::Box>(Gtk::Orientation::VERTICAL);
	auto hbox = Gtk::make_managed<Gtk::Box>(Gtk::Orientation::HORIZONTAL);
	auto prevButton = Gtk::make_managed<Gtk::Button>("<");
	auto nextButton = Gtk::make_managed<Gtk::Button>(">");

	zoomImg_.set_vexpand(true);
	demoTable_.set_hexpand(true);

	set_child(*box);
	box->append(zoomImg_);
	box->append(*hbox);
		hbox->append(*prevButton);
		hbox->append(demoTable_);
		hbox->append(*nextButton);

	prevButton->signal_clicked().connect(sigc::mem_fun(*this, &Demo::OnPrevSet));
	nextButton->signal_clicked().connect(sigc::mem_fun(*this, &Demo::OnNextSet));

	UpdateSet();

	 Glib::signal_timeout().connect(
		sigc::mem_fun(*this, &Demo::OnIdle),
		REFRESH_INTERVAL_MS,
		Glib::PRIORITY_DEFAULT_IDLE); 

	zoomImg_.ShowCursor();
}

Demo::~Demo()
{
	ClearSet();
}


void Demo::UpdateSet()
{
	CardSet *set = cardCollection_[currentSetIdx_];
	LoadSet(*set);
	OnDemoClick(demoTable_.GetFirstCard());
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
 		demoCards_[i]->signal_clicked.connect(sigc::mem_fun(*this, &Demo::OnDemoClick));
	}

	demoTable_.SetCards(demoCards_);
}

void Demo::UpdateZoom(Card* card)
{
	latero::graphics::gtk::Animation  anim = card->GetLargeFaceUpAnim();
	zoomImg_.Set(anim);
}

void Demo::OnDemoClick(Card* card)
{
	SetCurrentCard(card);
	UpdateZoom(card);
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



void Demo::OnPrevSet()
{
	currentSetIdx_--;
	if (currentSetIdx_<0)
		currentSetIdx_ = (currentSetIdx_+1)%cardCollection_.size();
	UpdateSet();
}

void Demo::OnNextSet()
{
	currentSetIdx_ = (currentSetIdx_+1)%cardCollection_.size();
	UpdateSet();
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

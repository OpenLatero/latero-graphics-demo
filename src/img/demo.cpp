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

	LoadCards(dev);

	
	

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
   for (auto *card : cardCollection_)
        delete card;
	cardCollection_.clear();

	ClearSet();
}

void Demo::LoadCards(const latero::Tactograph *dev)
{
	std::string path = media_dir+"/img/";

	auto cardSet1 = new CardSet();	
	std::string path1 = media_dir+"/img/vib-objects/";
	std::vector<std::string> files1 = {
		"umbrella.gen", "car.gen", "house.gen", "phone.gen", "necklace.gen", "leaf.gen", 
		"cloud.gen", "cup.gen", "sun.gen", "balloons.gen", "hand.gen", "fork.gen" };
	for (const auto& file : files1)
		cardSet1->LoadGenerator(path1 + file, dev, SCALE_UP_FACTOR);
	cardCollection_.push_back(cardSet1);

	auto cardSet2 = new CardSet();
	std::string path2 = media_dir+"/img/combo-objects/";
	std::vector<std::string> files2 = {
		"leaf.gen", "car.gen", "crown.gen", "umbrella.gen", "sun.gen", "cup.gen", 
		"boat.gen", "candle.gen", "shirt.gen", "flashlight.gen", "necklace.gen", "insect.gen" };
	for (const auto& file : files2)
		cardSet2->LoadGenerator(path2 + file, dev, SCALE_UP_FACTOR);
	cardCollection_.push_back(cardSet2);
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

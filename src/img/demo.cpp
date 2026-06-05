#include "../config.h"
#ifndef DISABLE_GRAPHICS_DEMO

#include "demo.h"
#include "settings.h"
#include "../generatorhandle.h"
#include <vector>
#include <laterographics/generator.h>
#include "card.h"

#define REFRESH_INTERVAL_MS 30
#define SCALE_UP_FACTOR 5

namespace ImgDemo {

Demo::Demo(const latero::Tactograph *dev) :
	display_(dev),
	page_(0)
{ 
	gen_ = GeneratorHandlePtr(new GeneratorHandle(dev));

	LoadCards(dev);

	grid_.set_margin(10);
	grid_.set_row_spacing(10);
	grid_.set_column_spacing(10);

	auto box = Gtk::make_managed<Gtk::Box>(Gtk::Orientation::VERTICAL);
	auto hbox = Gtk::make_managed<Gtk::Box>(Gtk::Orientation::HORIZONTAL);
	auto prevButton = Gtk::make_managed<Gtk::Button>("<");
	auto nextButton = Gtk::make_managed<Gtk::Button>(">");

	display_.set_vexpand(true);
	grid_.set_hexpand(true);

	set_child(*box);
	box->append(display_);
	box->append(*hbox);
		hbox->append(*prevButton);
		hbox->append(grid_);
		hbox->append(*nextButton);

	prevButton->signal_clicked().connect(sigc::mem_fun(*this, &Demo::OnPrevPage));
	nextButton->signal_clicked().connect(sigc::mem_fun(*this, &Demo::OnNextPage));

	UpdatePage();

	 Glib::signal_timeout().connect(
		sigc::mem_fun(*this, &Demo::OnIdle),
		REFRESH_INTERVAL_MS,
		Glib::PRIORITY_DEFAULT_IDLE); 

	display_.ShowCursor();
}

Demo::~Demo()
{
}

void Demo::LoadCards(const latero::Tactograph *dev)
{
	std::vector<std::string> files;

	files = { "umbrella.gen", "car.gen", "house.gen", "phone.gen", "necklace.gen", "leaf.gen", 
		      "cloud.gen", "cup.gen", "sun.gen", "balloons.gen", "hand.gen", "fork.gen" };
	assert(files.size() == 12);
	cardPages_.push_back(CreateCardsFromFiles(media_dir+"/img/vib-objects/", files, dev));

	files = { "leaf.gen", "car.gen", "crown.gen", "umbrella.gen", "sun.gen", "cup.gen", 
		      "boat.gen", "candle.gen", "shirt.gen", "flashlight.gen", "necklace.gen", "insect.gen" };
	assert(files.size() == 12);
	cardPages_.push_back(CreateCardsFromFiles(media_dir+"/img/combo-objects/", files, dev));
}

std::vector<CardPtr> Demo::CreateCardsFromFiles(const std::string &path, const std::vector<std::string> &files, const latero::Tactograph *dev)
{
	std::vector<CardPtr> cards;
	for (const auto& file : files)
	{
		latero::graphics::GeneratorPtr gen = latero::graphics::Generator::Create(path+file, dev);
		auto card = Card::Create(gen);
		card->signal_clicked.connect(sigc::mem_fun(*this, &Demo::OnCardSelected));
		cards.push_back(card);
	}
	return cards;
}



void Demo::OnCardSelected(CardPtr card)
{
	gen_->SetGenerator(card->GetGenerator());
	display_.Set(card->GetIllustration());
}


bool Demo::OnIdle()
{
	if (gen_)
	{
		auto frame = gen_->GetLatestFrame();
		auto center = gen_->GetDisplayCenter();
		auto angle = gen_->GetDisplayOrientation();
		display_.SetDisplayState(center, angle, frame);
	}


	 Glib::signal_timeout().connect(
		sigc::mem_fun(*this, &Demo::OnIdle),	
		REFRESH_INTERVAL_MS,
		Glib::PRIORITY_DEFAULT_IDLE); 

	return false;
}



void Demo::OnPrevPage()
{
	page_ = (page_ - 1 + cardPages_.size()) % cardPages_.size();
	UpdatePage();
}

void Demo::OnNextPage()
{
	page_ = (page_+1)%cardPages_.size();
	UpdatePage();
}

void Demo::UpdatePage()
{
	auto set = cardPages_[page_];
	UpdateGrid(set);
	OnCardSelected(set[0]);
}



void Demo::UpdateGrid(std::vector<CardPtr> cards)
{
	for (auto* child : grid_.get_children())
    	grid_.remove(*child);

	for (uint x=0; x<NbCardsX; ++x)
	{
		for (uint y=0; y<NbCardsY; ++y)
		{
			auto card = cards[y*NbCardsX+x];
			card->set_vexpand(true);
			card->set_hexpand(true);	
			grid_.attach(*card, x, y, 1, 1);
		}
	}	
}


latero::graphics::GeneratorPtr Demo::Gen()
{ 
	return gen_; 
};

} // namespace

#endif

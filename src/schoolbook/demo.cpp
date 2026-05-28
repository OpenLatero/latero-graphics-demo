#include "demo.h"
#ifndef DISABLE_SCHOOLBOOK_DEMO

#include "../generatorhandle.h"

namespace SchoolbookDemo {

#define SEL_OEIL	0
#define SEL_CATH	1
#define SEL_BAR		2
#define SEL_MAP		3

const std::string GEN_OEIL = media_dir+"/schoolbook/oeil3/oeil3.gen";
const std::string GEN_CATH = media_dir+"/schoolbook/A1B1_Cathedrale_Gothique.gen";
const std::string GEN_BAR = media_dir+"/schoolbook/A2_Population_Attique/A2_Population_Attique.gen";
const std::string GEN_MAP = media_dir+"/schoolbook/A3A4_Civilisations.gen";

Demo::Demo(const latero::Tactograph *dev) :
	preview_(dev, latero::graphics::GeneratorPtr(), true),
	sel_(0),
	dev_(dev)
{
	peer_ = GeneratorHandlePtr(new GeneratorHandle(dev));
	preview_.SetGenerator(peer_);
	preview_.RefreshBackground();


	CreateGenerators();
	Select(SEL_CATH);

	preview_.ShowCursor();
	for (int i=1; i<NB_BUTTONS; ++i)
		selButton_[i].set_group(selButton_[0]);

	auto box = Gtk::make_managed<Gtk::Box>(Gtk::Orientation::VERTICAL);
	auto buttonBox = Gtk::make_managed<Gtk::Box>(Gtk::Orientation::HORIZONTAL);

	set_child(*box);
	preview_.set_vexpand(true);
	box->append(preview_);
	box->append(*buttonBox);
	for (int i=0; i<NB_BUTTONS; ++i)
	{
		buttonBox->append(selButton_[i]);
		selButton_[i].signal_toggled().connect(
			sigc::mem_fun(*this, &Demo::OnSelChange));
	}

	selButton_[0].set_label("oeil");
	selButton_[1].set_label("cathedrale gothique");
	selButton_[2].set_label("population attique");
	selButton_[3].set_label("civilisations");

	auto keyController = Gtk::EventControllerKey::create();
	keyController->signal_key_pressed().connect(
		sigc::mem_fun(*this, &Demo::OnKeyPress), false);
	add_controller(keyController);
}

Demo::~Demo() 
{
}

void Demo::CreateGenerators()
{
	list_.push_back(latero::graphics::Generator::Create(GEN_OEIL, dev_));
	list_.push_back(latero::graphics::Generator::Create(GEN_CATH, dev_));
	list_.push_back(latero::graphics::Generator::Create(GEN_BAR, dev_));
	list_.push_back(latero::graphics::Generator::Create(GEN_MAP, dev_));

    /*
	for (unsgigned int i=0; i<list_.size(); ++i)
	{
		float w = 1000;
		float h = w * dev_->GetSurfaceHeight() / dev_->GetSurfaceWidth();
		list_[i]->StoreIllustration(w,h);
	}
    */
}


void Demo::OnSelChange()
{
	if (selButton_[0].get_active())		Select(SEL_OEIL);
	else if (selButton_[1].get_active())	Select(SEL_CATH);
	else if (selButton_[2].get_active())	Select(SEL_BAR);
	else if (selButton_[3].get_active())	Select(SEL_MAP);
}


bool Demo::OnKeyPress(guint keyval, guint keycode, Gdk::ModifierType state)
{
	list_[sel_]->OnKeyPress(keyval, keycode, state);
	Select(sel_); // TODO: this is wasteful (only necessary if there's a toggle
	return true;
}

void Demo::Select(int i)
{
	sel_ = i;
	peer_->SetGenerator(list_[sel_]);
	assert(list_[sel_]);
	//preview_.SetGenerator(list_[sel_]);
	//preview_.RefreshBackground();
}

}; // namespace

#endif

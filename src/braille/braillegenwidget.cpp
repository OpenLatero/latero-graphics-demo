#include "../config.h"
#ifndef DISABLE_BRAILLE_DEMO

#include "braillegenwidget.h"
#include "braillegen.h"
#include "braillecellwidget.h"
#include <gtkmm.h>
#include "dot.h"
#include <laterographics/gtk/numwidget.h>
#include "virtualsurfacewidget.h"
#include "positiongraph.h"


BrailleGenWidget::BrailleGenWidget(BrailleGenPtr peer) :
	//latero::graphics::GeneratorWidget(peer),
	Gtk::Box(Gtk::Orientation::VERTICAL),
	peer_(peer),
	strWidget_(&peer->str_),
	dot_(&peer->dot_),
	vibDot_(&peer->vibDot_),
	dotWidthAdj_(Gtk::Adjustment::create(0,0.1,1)),
	intraDotDistAdj_(Gtk::Adjustment::create(0,0.1,3)),
	interDotDistAdj_(Gtk::Adjustment::create(0,0.1,4)),
	offsetAdj_(Gtk::Adjustment::create(1,0.0001,50)),
	vibFreqAdj_(Gtk::Adjustment::create(0,1,25)),
	vibModWidget_(&peer->vibMod_),
	invertCheck_("invert")
{
	mode_[BRAILLE_MODE_SINGLE_COMPACT].set_label("single (compact)"),
	mode_[BRAILLE_MODE_SINGLE_DIAG].set_label("single (diagonal)"),
	mode_[BRAILLE_MODE_SINGLE_SPARSE].set_label("single (sparse)"),
	mode_[BRAILLE_MODE_DOUBLE].set_label("double"),
	mode_[BRAILLE_MODE_DOUBLE_DOT_SHEAR].set_label("double (dot shear)"),
	mode_[BRAILLE_MODE_DOUBLE_ROW_SHEAR].set_label("double (row shear)"),

	dotWidthAdj_->set_value(peer_->GetDotWidthRel());
	intraDotDistAdj_->set_value(peer_->GetIntraDotDistRel());
	interDotDistAdj_->set_value(peer_->GetInterDotDistRel());
	offsetAdj_->set_value(peer_->GetOffset());
	vibFreqAdj_->set_value(peer_->GetVibFreq());

	auto notebook = manage(new Gtk::Notebook);
	strWidget_.set_halign(Gtk::Align::CENTER);
	strWidget_.set_valign(Gtk::Align::CENTER);

	auto vizWidget = CreateVizWidget();
	append(*vizWidget);

	append(strWidget_);
	append(*notebook);
		notebook->append_page(*CreateParamsWidget(), "General Settings");
		notebook->append_page(dot_, "Deflection Profile");
		notebook->append_page(*CreateVibWidget(), "Vibration Settings");
		notebook->append_page(vibDot_, "Vibration Profile");
	notebook->set_vexpand(false);

	dot_.signal_value_changed.connect(
		sigc::mem_fun(*this, &BrailleGenWidget::OnChange));
	vibDot_.signal_value_changed.connect(
		sigc::mem_fun(*this, &BrailleGenWidget::OnChange));
	strWidget_.signal_value_changed.connect(
		sigc::mem_fun(*this, &BrailleGenWidget::OnChange));
}

Gtk::Widget *BrailleGenWidget::CreateVibWidget()
{
	auto frame = manage(new Gtk::Frame("Vibration Parameters"));
	auto box = manage(new Gtk::Box(Gtk::Orientation::VERTICAL));

	frame->set_child(*box);
	frame->set_vexpand(false);
	box->set_vexpand(false);
	box->append(*manage(new latero::graphics::gtk::NumWidget(Gtk::Orientation::HORIZONTAL, vibFreqAdj_,0, latero::graphics::gtk::name_none, "frequency")));
	box->append(vibModWidget_);
	vibModWidget_.set_vexpand(false);
	vibFreqAdj_->signal_value_changed().connect(
		sigc::mem_fun(*this, &BrailleGenWidget::OnChange));
	return frame;
}


Gtk::Widget *BrailleGenWidget::CreateParamsWidget()
{
	auto box = manage(new Gtk::Box(Gtk::Orientation::HORIZONTAL));
	auto paramBox = manage(new Gtk::Box(Gtk::Orientation::VERTICAL));
	auto presetBox = manage(new Gtk::Box(Gtk::Orientation::VERTICAL));
	auto presetFrame = manage(new Gtk::Frame("presets"));

	auto stdButton = manage(new Gtk::Button("standard braille"));
	auto scaledButton = manage(new Gtk::Button("scaled braille (full height)"));
	auto halfScaledButton = manage(new Gtk::Button("scaled braille (half height)"));
	auto vbdButton = manage(new Gtk::Button("vbd braille"));

	box->append(*CreateModeWidget());
	box->append(*paramBox);
	box->append(*presetFrame);

	paramBox->append(
		*manage(new latero::graphics::gtk::NumWidget(Gtk::Orientation::HORIZONTAL, dotWidthAdj_,3, "dot width (% of space)", latero::graphics::gtk::units_none)));
	paramBox->append(
		*manage(new latero::graphics::gtk::NumWidget(Gtk::Orientation::HORIZONTAL, intraDotDistAdj_,3, "dot-to-dot spacing (in cell, % of standard)", latero::graphics::gtk::units_none)));
	paramBox->append(
		*manage(new latero::graphics::gtk::NumWidget(Gtk::Orientation::HORIZONTAL, interDotDistAdj_,3, "dot-to-dot spacing (between cells, % of standard)", latero::graphics::gtk::units_none)));
	paramBox->append(
		*manage(new latero::graphics::gtk::NumWidget(Gtk::Orientation::HORIZONTAL, offsetAdj_,3,"offset", latero::graphics::gtk::units_none)));

	presetFrame->set_child(*presetBox);
		presetBox->append(*stdButton);
		presetBox->append(*scaledButton);
		presetBox->append(*halfScaledButton);
		presetBox->append(*vbdButton);

	dotWidthAdj_->signal_value_changed().connect(
		sigc::mem_fun(*this, &BrailleGenWidget::OnChange));
	intraDotDistAdj_->signal_value_changed().connect(
		sigc::mem_fun(*this, &BrailleGenWidget::OnChange));
	interDotDistAdj_->signal_value_changed().connect(
		sigc::mem_fun(*this, &BrailleGenWidget::OnChange));
	offsetAdj_->signal_value_changed().connect(
		sigc::mem_fun(*this, &BrailleGenWidget::OnChange));

	stdButton->signal_clicked().connect(
		sigc::mem_fun(*this, &BrailleGenWidget::OnStandardButton));
	scaledButton->signal_clicked().connect(
		sigc::mem_fun(*this, &BrailleGenWidget::OnScaledButton));
	halfScaledButton->signal_clicked().connect(
		sigc::mem_fun(*this, &BrailleGenWidget::OnHalfScaledButton));
	vbdButton->signal_clicked().connect(
		sigc::mem_fun(*this, &BrailleGenWidget::OnVBDButton));
	
	return box;
}


Gtk::Widget *BrailleGenWidget::CreateModeWidget()
{
	for (int i=1; i<BRAILLE_MODE_SIZE; ++i)
		mode_[i].set_group(mode_[0]);
	mode_[(int)peer_->GetMode()].set_active(true);
	invertCheck_.set_active(peer_->GetInvert());

	auto modeFrame = manage(new Gtk::Frame("mode"));
	auto modeBox = manage(new Gtk::Box(Gtk::Orientation::VERTICAL));

	modeFrame->set_child(*modeBox);
	//modeBox->pack_start(*manage(new Gtk::Label("single")));
	modeBox->append(mode_[BRAILLE_MODE_SINGLE_COMPACT]);
	modeBox->append(mode_[BRAILLE_MODE_SINGLE_DIAG]);
	modeBox->append(mode_[BRAILLE_MODE_SINGLE_SPARSE]);
	//modeBox->pack_start(*manage(new Gtk::Label("double")));
	modeBox->append(mode_[BRAILLE_MODE_DOUBLE]);
	modeBox->append(mode_[BRAILLE_MODE_DOUBLE_DOT_SHEAR]);
	modeBox->append(mode_[BRAILLE_MODE_DOUBLE_ROW_SHEAR]);
	modeBox->append(invertCheck_);

	for (int i=0; i<BRAILLE_MODE_SIZE; ++i)
  		mode_[i].signal_toggled().connect(
			sigc::mem_fun(*this, &BrailleGenWidget::OnChange));
	invertCheck_.signal_toggled().connect(
		sigc::mem_fun(*this, &BrailleGenWidget::OnChange));

	return modeFrame;
}


BrailleGenWidget::~BrailleGenWidget()
{
}

void BrailleGenWidget::OnChange()
{
	for (int i=0; i<BRAILLE_MODE_SIZE; ++i)
		if (mode_[i].get_active()) peer_->SetMode((braille_mode_t)i);
	peer_->SetInvert(invertCheck_.get_active());
	peer_->SetIntraDotDistRel(intraDotDistAdj_->get_value());
	peer_->SetInterDotDistRel(interDotDistAdj_->get_value());
	peer_->SetDotWidthRel(dotWidthAdj_->get_value());
	peer_->SetOffset(offsetAdj_->get_value());
	peer_->SetVibFreq(vibFreqAdj_->get_value());
}

void BrailleGenWidget::OnStandardButton()
{
	intraDotDistAdj_->set_value(1.0);
	interDotDistAdj_->set_value(1.0);
	dotWidthAdj_->set_value(0.655);
}

void BrailleGenWidget::OnScaledButton()
{
	// dot-to-dot distance is 2.54 mm vertically
	// assuming the middle of a dot is between rows, that means that 4/6th of the display should cover 5.08 mm
	// => 10.8 * 2/3 = 7.2 mm => ratio is 1.42
	// height of display is 10.8 mm

	intraDotDistAdj_->set_value(1.42);
	interDotDistAdj_->set_value(1.42);
	dotWidthAdj_->set_value(0.655);
}

void BrailleGenWidget::OnHalfScaledButton()
{
	// dot-to-dot distance is 2.54 mm vertically
	// assuming the middle of a dot is between rows, that means that 4/6th of the display should cover 5.08 mm
	// => 5.4 * 2/3 = 3.6 mm => ratio is 0.71
	// height of display is 10.8 mm

	intraDotDistAdj_->set_value(0.71);
	interDotDistAdj_->set_value(0.71);
	dotWidthAdj_->set_value(0.655);
}

void BrailleGenWidget::OnVBDButton()
{
	intraDotDistAdj_->set_value(1.75);
	interDotDistAdj_->set_value(1.75);
	dotWidthAdj_->set_value(0.5);
}

Gtk::Widget *BrailleGenWidget::CreateVizWidget()
{
	auto box = manage(new Gtk::Box(Gtk::Orientation::VERTICAL));
	box->set_halign(Gtk::Align::FILL);
	box->set_valign(Gtk::Align::FILL);

	VirtualSurfaceWidget *surf = Gtk::make_managed<VirtualSurfaceWidget>(peer_);
	surf->set_size_request(1000,1.2*1000*peer_->Dev()->GetHeight()/peer_->Dev()->GetSurfaceWidth());
	surf->set_margin_top(10);

	PositionGraph *graph = manage(new PositionGraph(peer_));;
	box->append(*graph);
	box->append(*surf);

	return box;
}

#endif

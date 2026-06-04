#include "../config.h"
#ifndef DISABLE_BRAILLE_DEMO

#include "modulatorwidget.h"
#include <gtkmm/frame.h>
#include <gtkmm.h>

ModulatorWidget::ModulatorWidget(Modulator *peer) :
	peer_(peer),
	fixedBox_(Gtk::Orientation::HORIZONTAL),
	velBox_(Gtk::Orientation::VERTICAL),
	ampAdj_(Gtk::Adjustment::create(0,0,1,0.1,0.1)),
	rampMinAdj_(Gtk::Adjustment::create(0,0,500)),
	rampMaxAdj_(Gtk::Adjustment::create(0,0,500)),
	rampMinAmpAdj_(Gtk::Adjustment::create(0,0,1)),
	rampMaxAmpAdj_(Gtk::Adjustment::create(0,0,1)),
	maxRiseRateAdj_(Gtk::Adjustment::create(0,0.0,1.0)),
	maxFallRateAdj_(Gtk::Adjustment::create(0,0.0,1.0)),
	fixedMode_("fixed"),
	velMode_("vel")
{
	ampAdj_->set_value(1);
	rampMinAdj_->set_value(50);
	rampMaxAdj_->set_value(100);
	rampMinAmpAdj_->set_value(0);
	rampMaxAmpAdj_->set_value(1);
	maxRiseRateAdj_->set_value(0.5);
	maxFallRateAdj_->set_value(0.5);

	velMode_.set_group(fixedMode_);
	fixedMode_.set_active(true);
	ampAdj_->set_value(peer_->GetFixedAmp());
	double min,max;
	peer_->GetRampRange(min,max);
	rampMinAdj_->set_value(min);
	rampMaxAdj_->set_value(max);
	peer_->GetRampAmpRange(min,max);
	rampMinAmpAdj_->set_value(min);
	rampMaxAmpAdj_->set_value(max);
	maxRiseRateAdj_->set_value(peer_->GetMaxRiseRate());
	maxFallRateAdj_->set_value(peer_->GetMaxFallRate());

	auto fixedFrame = Gtk::make_managed<Gtk::Frame>();
	auto velFrame = Gtk::make_managed<Gtk::Frame>();
	auto velAmpBox = Gtk::make_managed<Gtk::Box>(Gtk::Orientation::HORIZONTAL);
	auto velRangeBox = Gtk::make_managed<Gtk::Box>(Gtk::Orientation::HORIZONTAL);
	auto velRateBox = Gtk::make_managed<Gtk::Box>(Gtk::Orientation::HORIZONTAL);

	set_vexpand(false);

	//attach(fixedMode_, 0, 1, 0, 1, Gtk::SHRINK);
	attach(fixedMode_, 0, 0, 1, 1);
	//attach(*fixedFrame, 1, 2, 0, 1);
	attach(*fixedFrame, 1, 0, 1, 1);
		fixedFrame->set_child(fixedBox_);
		fixedBox_.append(*Gtk::make_managed<Gtk::Label>(" Amplitude (0-1) "));
		fixedBox_.append(*Gtk::make_managed<Gtk::SpinButton>(ampAdj_,0, 3));
	//attach(velMode_, 0, 1, 1, 2, Gtk::SHRINK);
	attach(velMode_, 0, 1, 1, 1);
	//attach(*velFrame, 1, 2, 1, 2);
	attach(*velFrame, 1, 1, 1, 1);
		velFrame->set_child(velBox_);
		velBox_.append(*velAmpBox);
			velAmpBox->append(*Gtk::make_managed<Gtk::Label>("Amplitude range (0-1): "));
			velAmpBox->append(*Gtk::make_managed<Gtk::SpinButton>(rampMinAmpAdj_,0, 2));
			velAmpBox->append(*Gtk::make_managed<Gtk::Label>("  to  "));
			velAmpBox->append(*Gtk::make_managed<Gtk::SpinButton>(rampMaxAmpAdj_,0, 2));
		velBox_.append(*velRangeBox);
			velRangeBox->append(*Gtk::make_managed<Gtk::Label>("Ramp range (mm/s): "));
			velRangeBox->append(*Gtk::make_managed<Gtk::SpinButton>(rampMinAdj_,0, 2));
			velRangeBox->append(*Gtk::make_managed<Gtk::Label>("  to  "));
			velRangeBox->append(*Gtk::make_managed<Gtk::SpinButton>(rampMaxAdj_,0, 2));
		velBox_.append(*velRateBox);
			velRateBox->append(*Gtk::make_managed<Gtk::Label>(" Maximum transition rate (sec/full): "));
			velRateBox->append(*Gtk::make_managed<Gtk::Label>("rise "));
			velRateBox->append(*Gtk::make_managed<Gtk::SpinButton>(maxRiseRateAdj_,0, 2));
			velRateBox->append(*Gtk::make_managed<Gtk::Label>("  fall "));
			velRateBox->append(*Gtk::make_managed<Gtk::SpinButton>(maxFallRateAdj_,0, 2));

	ampAdj_->signal_value_changed().connect(
		sigc::mem_fun(*this, &ModulatorWidget::OnChange));
	maxRiseRateAdj_->signal_value_changed().connect(
		sigc::mem_fun(*this, &ModulatorWidget::OnChange));
	maxFallRateAdj_->signal_value_changed().connect(
		sigc::mem_fun(*this, &ModulatorWidget::OnChange));
  	fixedMode_.signal_toggled().connect(
		sigc::mem_fun(*this, &ModulatorWidget::OnChange));
  	velMode_.signal_toggled().connect(
		sigc::mem_fun(*this, &ModulatorWidget::OnChange));
	rampMinAdj_->signal_value_changed().connect(
		sigc::mem_fun(*this, &ModulatorWidget::OnChange));
	rampMaxAdj_->signal_value_changed().connect(
		sigc::mem_fun(*this, &ModulatorWidget::OnChange));
	rampMinAmpAdj_->signal_value_changed().connect(
		sigc::mem_fun(*this, &ModulatorWidget::OnChange));
	rampMaxAmpAdj_->signal_value_changed().connect(
		sigc::mem_fun(*this, &ModulatorWidget::OnChange));


	OnModeChange();
}

ModulatorWidget::~ModulatorWidget()
{
}

void ModulatorWidget::OnChange()
{
	if (rampMaxAdj_->get_value() <= rampMinAdj_->get_value())
	{
		double min,max;
		peer_->GetRampRange(min,max);
		rampMinAdj_->set_value(min);
		rampMaxAdj_->set_value(max);
	}
	else
	{
		peer_->SetRampRange(rampMinAdj_->get_value(),rampMaxAdj_->get_value());
	}
	if (rampMaxAmpAdj_->get_value() <= rampMinAmpAdj_->get_value())
	{
		double min,max;
		peer_->GetRampAmpRange(min,max);
		rampMinAmpAdj_->set_value(min);
		rampMaxAmpAdj_->set_value(max);
	}
	else
	{
		peer_->SetRampAmpRange(rampMinAmpAdj_->get_value(),rampMaxAmpAdj_->get_value());
	}
	peer_->SetMaxRiseRate(maxRiseRateAdj_->get_value());
	peer_->SetMaxFallRate(maxFallRateAdj_->get_value());
	peer_->SetFixedAmp(ampAdj_->get_value());
	if (fixedMode_.get_active()) peer_->SetModeFixed();
	if (velMode_.get_active()) peer_->SetModeVel();
	OnModeChange();
}

void ModulatorWidget::OnModeChange()
{
	fixedBox_.set_sensitive(fixedMode_.get_active());
	velBox_.set_sensitive(velMode_.get_active());
}



#endif

#include "../config.h"
#ifndef DISABLE_BRAILLE_DEMO


#include "dotwidget.h"
#include <laterographics/gtk/numwidget.h>

DotSideWidget::DotSideWidget() :
	Gtk::Box(Gtk::Orientation::VERTICAL),
	radiusAdj_(Gtk::Adjustment::create(0,0.0,1.0)),
	plateauAdj_(Gtk::Adjustment::create(0,0.0,1.0)),
	txAmpAdj_(Gtk::Adjustment::create(0,0.0,0.5)),
	txNbCyclesAdj_(Gtk::Adjustment::create(0,1.0,20.0))
{
	radiusAdj_->set_value(1.0);
	plateauAdj_->set_value(1.0);
	txAmpAdj_->set_value(0.0);
	txNbCyclesAdj_->set_value(0.0);

	shapeList_ = Gtk::StringList::create({});
	shapeDropDown_.set_model(shapeList_);
	append(shapeDropDown_);
	append(*manage(new latero::graphics::gtk::NumWidget(Gtk::Orientation::HORIZONTAL, radiusAdj_, 2, latero::graphics::units::none, "radius")));
	append(*manage(new latero::graphics::gtk::NumWidget(Gtk::Orientation::HORIZONTAL, plateauAdj_, 2, latero::graphics::units::none, "plateau (% of radius)")));
	append(*manage(new latero::graphics::gtk::NumWidget(Gtk::Orientation::HORIZONTAL, txAmpAdj_, 2, latero::graphics::units::none, "texture amplitude")));
	append(*manage(new latero::graphics::gtk::NumWidget(Gtk::Orientation::HORIZONTAL, txNbCyclesAdj_, 0, latero::graphics::units::none, "texture nb cycles")));

	shapeDropDown_.property_selected().signal_changed().connect(
		sigc::mem_fun(*this, &DotSideWidget::OnChange));
	radiusAdj_->signal_value_changed().connect(
		sigc::mem_fun(*this, &DotSideWidget::OnChange));
	plateauAdj_->signal_value_changed().connect(
		sigc::mem_fun(*this, &DotSideWidget::OnChange));
	txAmpAdj_->signal_value_changed().connect(
		sigc::mem_fun(*this, &DotSideWidget::OnChange));
	txNbCyclesAdj_->signal_value_changed().connect(
		sigc::mem_fun(*this, &DotSideWidget::OnChange));
}

Dot::SideParams DotSideWidget::Get()
{
	Dot::SideParams p;
	p.radius = radiusAdj_->get_value();
	p.plateau = plateauAdj_->get_value();
	auto idx = shapeDropDown_.get_selected();
	p.shape = (idx != GTK_INVALID_LIST_POSITION) ? std::string(shapeList_->get_string(idx)) : "";
	p.txAmp = txAmpAdj_->get_value();
	p.txNbCycles = (uint)txNbCyclesAdj_->get_value();
	return p;
}

void DotSideWidget::Set(const Dot::SideParams &p)
{
	radiusAdj_->set_value(p.radius);
	plateauAdj_->set_value(p.plateau);
	for (guint i = 0; i < shapeList_->get_n_items(); ++i) {
		if (shapeList_->get_string(i) == p.shape) { shapeDropDown_.set_selected(i); break; }
	}
	txAmpAdj_->set_value(p.txAmp);
	txNbCyclesAdj_->set_value(p.txNbCycles);
}

void DotSideWidget::AddShapes(const std::vector<std::string> &shapes)
{
	for (uint i=0; i<shapes.size(); ++i)
		shapeList_->append(shapes[i]);
}

void DotSideWidget::Disable(bool v)
{
	set_sensitive(!v);
	shapeDropDown_.set_sensitive(!v);
}

void DotSideWidget::OnChange()
{
	signal_value_changed();
}


DotWidget::DotWidget(Dot *peer) :
	Gtk::Box(Gtk::Orientation::HORIZONTAL),
	peer_(peer)
{
	graph_ = manage(new DotGraph(peer));

	std::vector<std::string> shapes = Dot::GetShapes();
	left_.AddShapes(shapes);
	right_.AddShapes(shapes);

	Dot::SideParams l = peer_->GetLeft();
	Dot::SideParams r = peer_->GetRight();
	left_.Set(l);
	right_.Set(r);
	sideLockCheck_.set_active(peer_->GetLockedSides());
	right_.Disable(peer_->GetLockedSides());

	append(left_);
	append(sideLockCheck_);
	append(right_);
	append(*graph_);
	graph_->Refresh();

	left_.signal_value_changed.connect(
		sigc::mem_fun(*this, &DotWidget::OnChange));
	right_.signal_value_changed.connect(
		sigc::mem_fun(*this, &DotWidget::OnChange));
	sideLockCheck_.signal_toggled().connect(
		sigc::mem_fun(*this, &DotWidget::OnChange));
}

void DotWidget::OnChange()
{
	right_.Disable(LockedSides());
	peer_->Set(left_.Get(),right_.Get(),sideLockCheck_.get_active());
	graph_->Refresh();
	signal_value_changed();
}
	
bool DotWidget::LockedSides()
{
	return sideLockCheck_.get_active();
}


#endif

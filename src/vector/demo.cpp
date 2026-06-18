#include "../config.h"
#ifndef DISABLE_VECTOR_DEMO

#include "demo.h"
#include <laterographics/graphics/polygon.h>
#include <laterographics/graphics/line.h>
#include <laterographics/graphics/circle.h>

namespace VectorDemo {

Demo::Demo(const latero::Tactograph *dev) :
	preview_(dev, latero::graphics::GeneratorPtr(), true)
{
	using namespace latero::graphics;

	peer_ = Canvas::Create(dev);

	double w = dev->GetSurfaceWidth();
	double h = dev->GetSurfaceHeight();
	peer_->GetGroup()->InsertPattern(Circle::Create(dev, dev->GetSurfaceSize()/2.0, 50));
	peer_->GetGroup()->InsertPattern(Line::Create(dev, latero::Point(0.25*w,0.5*h), latero::Point(0.75*w,0.5*h)));
	//peer_->InsertObject(Line::Create(dev, latero::Point(50,60), latero::Point(175,60)));

	/*
	PolygonPtr poly = Polygon::Create(dev);
	poly->InsertPoint(Point(50,50));
	poly->InsertPoint(Point(50,150));
	poly->InsertPoint(Point(150,150));
	peer_->InsertObject(poly);	
	*/

	/*
	PolygonPtr poly = Polygon::Create(dev);
	poly->InsertPoint(Point(0.25*w, 0.25*h));
	poly->InsertPoint(Point(0.25*w, 0.75*h));
	poly->InsertPoint(Point(0.75*w, 0.75*h));
	poly->InsertPoint(Point(0.75*w, 0.25*h));
	poly->InsertPoint(Point(0.50*w, 0.50*h));
	peer_->InsertPattern(poly);	
	*/

	//BlendPtr blend = Blend::Create(dev);
	//peer_->InsertPattern(blend);

	//peer_->InsertObject(Dot::Create(dev, Point(0.75*w,0.75*h)));

	//DotsPtr dots = Dots::Create(dev);
	//dots->InsertPoint(Point(0.25*w,0.25*h));
	//peer_->InsertObject(dots);

	preview_.ShowCursor();
	preview_.AnimateCursor(true);
	preview_.SetGenerator(peer_);
	preview_.set_vexpand(true);
	preview_.set_size_request(100,100); // make sure it doesn't get too small

	auto vbox = Gtk::make_managed<Gtk::Box>(Gtk::Orientation::VERTICAL);

	vectorWidget_ = (CanvasWidget*)peer_->CreateWidget(peer_);

	set_child(*vbox);
	vbox->append(preview_);
	vbox->append(*vectorWidget_);
	vectorWidget_->set_vexpand(false);
};

}; // namespace

#endif

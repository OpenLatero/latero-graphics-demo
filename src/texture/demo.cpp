#include "../config.h"
#ifndef DISABLE_TEXTURE_DEMO

#include "demo.h"
#include <cairomm/cairomm.h>
#include <laterographics/graphics/texture/stock.h>
#include <laterographics/graphics/texture/texture.h>
#include <laterographics/graphics/group.h>


namespace TextureDemo {

Demo::Demo(const latero::Tactograph *dev) :
	preview_(dev, latero::graphics::GeneratorPtr(), true)
{
	using namespace latero::graphics;
	gen_ = Canvas::Create(dev);
	peer_ = Image::Create(dev,GetMask(dev),Texture::Create(dev,latero::graphics::tx_grating_horizontal));
	gen_->GetGroup()->InsertPattern(peer_);
	preview_.ShowCursor();
	preview_.AnimateCursor(true);
	preview_.SetGenerator(gen_);
	preview_.set_vexpand(true);

	auto vbox = manage(new Gtk::Box(Gtk::Orientation::VERTICAL));

	waveWidget_ = manage(peer_->CreateWidget(peer_));

	set_child(*vbox);
	vbox->append(preview_);
	vbox->append(*waveWidget_);
	waveWidget_->set_vexpand(false);
};

Glib::RefPtr<Gdk::Pixbuf> Demo::GetMask(const latero::Tactograph *dev)
{
	int h = 1000;
	int w = 1000*dev->GetSurfaceWidth()/dev->GetSurfaceHeight();

	Glib::RefPtr<Gdk::Pixbuf> buf = Gdk::Pixbuf::create(Gdk::Colorspace::RGB, true, 8, w, h);
	Cairo::RefPtr<Cairo::ImageSurface> surface = Cairo::ImageSurface::create(
		(unsigned char*)buf->get_pixels(),
		Cairo::Surface::Format::ARGB32,
		buf->get_width(),
		buf->get_height(),
		buf->get_rowstride()
	);
	Cairo::RefPtr<Cairo::Context> cr = Cairo::Context::create(surface);

	// clear to black
	cr->set_source_rgb(0.0, 0.0, 0.0); // bgr
	cr->paint();

	cr->set_source_rgb(1.0, 1.0, 1.0); // bgr
	//cr->rectangle(0.1*w,0.1*h,0.8*w,0.8*h);
	cr->rectangle(0,0,w,h);
	cr->fill();
 	return buf;
}


}; // namespace

#endif

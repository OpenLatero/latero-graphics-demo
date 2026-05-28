#pragma once

#include "../config.h"
#ifndef DISABLE_TEXTURE_DEMO

#include "../demo.h"
#include <laterographics/virtualsurfacewidget.h>
#include <laterographics/graphics/image.h>
#include <laterographics/graphics/canvas.h>


namespace TextureDemo {

class Demo : public ::Demo
{
public:
	Demo(const latero::Tactograph *dev);
	virtual ~Demo() {};
	virtual latero::graphics::GeneratorPtr Gen() { return gen_; };
protected:
	Glib::RefPtr<Gdk::Pixbuf> GetMask(const latero::Tactograph *dev);
	bool RefreshCursor();
	void OnChange();

	latero::graphics::VirtualSurfaceWidget preview_;
	latero::graphics::CanvasPtr gen_;
	latero::graphics::ImagePtr peer_;
	Gtk::Widget *waveWidget_;
};

}; // namespace

#endif

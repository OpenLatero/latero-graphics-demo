#pragma once

#include "../config.h"
#ifndef DISABLE_ICON_DEMO

#include "generator.h"
#include <laterographics/graphics/texture/texturefwd.h>
#include <gtkmm.h>

namespace IconDemo {

/** small toolbar with minimal controls for the generator parameters */
class Toolbar : public Gtk::Frame
{
public:
	Toolbar(GeneratorPtr peer, Gtk::Window *window);
	virtual ~Toolbar() {};
protected:
	void Rebuild();
	void OnAdvanced();
	void OnTextureChanged(latero::graphics::TexturePtr tx);

	Gtk::Window *window_;
	GeneratorPtr peer_;
};

}; // namespace

#endif // !DISABLED

#pragma once

#include "../config.h"
#ifndef DISABLE_ICON_DEMO

#include "../demo.h"
#include <laterographics/tactographview.h>
#include "generator.h"
#include "toolbar.h"

namespace IconDemo {

class Demo : public ::Demo
{
public:
	Demo(const latero::Tactograph *dev, Gtk::Window *window);
	virtual ~Demo() {};
	virtual latero::graphics::GeneratorPtr Gen() { return peer_; };
protected:

	GeneratorPtr peer_;
	latero::graphics::TactographView preview_;
	Toolbar genToolbar_;

	Gtk::Box mainBox_;
};

}; // namespace

#endif // !DISABLED

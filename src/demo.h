#pragma once

#include <gtkmm.h>
#include <laterographics/generator.h>

class Demo : public Gtk::Frame
{
public:
	Demo() {};
	virtual ~Demo() {};
	virtual latero::graphics::GeneratorPtr Gen() = 0;
};
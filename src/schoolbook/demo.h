#pragma once

#include "../config.h"

#ifndef DISABLE_SCHOOLBOOK_DEMO

#include "../demo.h"
#include <laterographics/tactographview.h>
#include "../generatorhandle.h"

#define NB_BUTTONS 4

namespace SchoolbookDemo {

class Demo : public ::Demo
{
public:
	Demo(const latero::Tactograph *dev);
	virtual ~Demo();

	virtual latero::graphics::GeneratorPtr Gen() { return peer_; };

private:
	void OnSelChange();
	bool OnKeyPress(guint keyval, guint keycode, Gdk::ModifierType state);
	void Select(int i);
	void CreateGenerators();

	latero::graphics::TactographView preview_;
	Gtk::CheckButton selButton_[NB_BUTTONS];

	int sel_;
	std::vector<latero::graphics::GeneratorPtr> list_;
	GeneratorHandlePtr peer_;
	const latero::Tactograph *dev_;
};

}; // namespace

#endif

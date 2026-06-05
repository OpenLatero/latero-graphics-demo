#pragma once

#include "../config.h"
#ifndef DISABLE_GRAPHICS_DEMO

#include "../generatorhandle.h"
#include "../demo.h"
#include <vector>
#include <laterographics/generator.h>
#include "card.h"

namespace ImgDemo {

class Demo : public ::Demo
{
public:
	Demo(const latero::Tactograph *dev);
	virtual ~Demo();
	virtual latero::graphics::GeneratorPtr Gen();

protected:
	void OnPrevPage();
	void OnNextPage();
	void UpdatePage();

	void LoadSet(std::vector<CardPtr> set);

	void OnCardClicked(CardPtr card);
	bool OnIdle();
	void UpdateZoom(CardPtr card);

	void LoadCards(const latero::Tactograph *dev);
	void UpdateGrid(std::vector<CardPtr> cards);


	std::vector< std::vector<CardPtr> > cardCollection_;

	// large visualization of the current card, at the top of the window
	latero::graphics::BaseVirtualSurfaceWidget zoomImg_;

	GeneratorHandlePtr gen_;

	int page_;

	Gtk::Grid grid_;
};

} // namespace

#endif

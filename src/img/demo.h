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

	void LoadCards(const latero::Tactograph *dev);


	std::vector<CardPtr> CreateCardsFromFiles(const std::string &path, const std::vector<std::string> &files, const latero::Tactograph *dev);


	void OnCardSelected(CardPtr card);
	bool OnIdle();


	void UpdateGrid(std::vector<CardPtr> cards);

	std::vector< std::vector<CardPtr> > cardPages_;

	// large visualization of the current card, at the top of the window
	latero::graphics::BaseVirtualSurfaceWidget display_;

	GeneratorHandlePtr gen_;

	int page_;

	Gtk::Grid grid_;
};

} // namespace

#endif

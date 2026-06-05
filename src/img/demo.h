#pragma once

#include "../config.h"
#ifndef DISABLE_GRAPHICS_DEMO

#include "cardset.h"
#include "../generatorhandle.h"
#include "../demo.h"

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

	void OnDemoClick(CardPtr card);
	bool OnIdle();
	void UpdateZoom(CardPtr card);


private:
	void LoadCards(const latero::Tactograph *dev);
	void UpdateGrid(std::vector<CardPtr> cards);

	void SetCurrentCard(CardPtr card);
	std::vector<CardSet*> cardCollection_;

	// large visualization of the current card, at the top of the window
	latero::graphics::BaseVirtualSurfaceWidget zoomImg_;

	CardPtr curCard_; // currently activated card	
	GeneratorHandlePtr gen_;

	int page_;

	Gtk::Grid grid_;
};

} // namespace

#endif

#pragma once

#include "../config.h"
#ifndef DISABLE_GRAPHICS_DEMO

#include "cardset.h"
#include "cardtable.h"
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
	void OnPrevSet();
	void OnNextSet();

	void UpdateSet();
	void ClearSet();
	void LoadSet(const CardSet &set);

	void OnDemoClick(CardPtr card);
	bool OnIdle();
	void UpdateZoom(CardPtr card);


private:
	void LoadCards(const latero::Tactograph *dev);

	void SetCurrentCard(CardPtr card);
	std::vector<CardSet*> cardCollection_;

	CardSet demoCards_;
	const CardSet* currentSet_;

	// large visualization of the current card, at the top of the window
	latero::graphics::BaseVirtualSurfaceWidget zoomImg_;

	CardTable demoTable_;
	CardPtr curCard_; // currently activated card	
	GeneratorHandlePtr gen_;

	int currentSetIdx_;
};

} // namespace

#endif

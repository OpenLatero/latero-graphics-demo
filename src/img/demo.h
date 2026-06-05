#pragma once

#include "../config.h"
#ifndef DISABLE_GRAPHICS_DEMO

#include "cardset.h"
#include "cardtable.h"
#include "cardcollection.h"
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
	void Reset();

	void OnBoardClick(int n_press, double x, double y);
	void OnDemoClick(Card* card);
	void OnRightClick(Card* card);
	void OnSetChanged();
	bool OnIdle();
	void OnShowCursor();
	bool OnKeyPress(guint keyval, guint keycode, Gdk::ModifierType state);
	void UpdateZoom(Card* card);


private:
	void SetCurrentCard(Card *card);
	Card *GetCard(int x, int y);
	CardCollection cardSets_;
	void UpdateMode();

	CardSet demoCards_;
	const CardSet* currentSet_;

	// large visualization of the current card, at the top of the window
	latero::graphics::BaseVirtualSurfaceWidget zoomImg_;

	CardTable demoTable_;
	Card* curCard_; // currently activated card	
	GeneratorHandlePtr gen_;

	std::vector<Gtk::CheckButton*> setActions_;

	latero::graphics::INTPoint keyLocation_;
	int currentSetIdx_;
};

} // namespace

#endif

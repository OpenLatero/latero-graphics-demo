#pragma once

#include "../config.h"
#ifndef DISABLE_GRAPHICS_DEMO

#include "gtkmm.h"
#include <laterographics/virtualsurfacewidget.h>
#include <laterographics/generator.h>

class Card : public Gtk::Box
{
public:
	Card(latero::graphics::GeneratorPtr gen, uint width, uint height, uint scale);
	~Card();

	Card(const Card& p);
	Card operator= (const Card& p);

	void Initialize();

	void SetBlind(bool v);

	void SetDisplayState(const latero::graphics::Point &center, double angle, const latero::BiasedImg &frame);
	void HideTD();

	inline latero::graphics::GeneratorPtr GetGenerator() {
		return gen_;
	}

	sigc::signal<void(Card*)> signal_clicked1;
	sigc::signal<void(Card*)> signal_clicked3;

	latero::graphics::gtk::Animation GetLargeFaceUpAnim();


	void ShowCursor(bool v) {
		img_.ShowBorder(v);
	}

	void UpdateImg();
	void ClearImg();
protected:

	void OnClicked(int n_press, double x, double y);
	Glib::RefPtr<Gtk::GestureClick> clickGesture_;
	bool blindMode_;

	latero::graphics::GeneratorPtr gen_;

	uint width_, height_;

	latero::graphics::gtk::Animation largeFaceUpAnim_;
	latero::graphics::gtk::Animation faceUpAnim_;

	// TODO: make sure img_ is used only for cards we are actually using! (i.e. when inserted in table!)
	latero::graphics::BaseVirtualSurfaceWidget img_;

};

#endif

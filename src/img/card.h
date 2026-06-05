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

	inline latero::graphics::GeneratorPtr GetGenerator() {
		return gen_;
	}

	sigc::signal<void(Card*)> signal_clicked;

	/** This is used to set the content of the large display. */
	latero::graphics::gtk::Animation GetLargeFaceUpAnim();

protected:
	void Initialize();

Glib::RefPtr<Gtk::GestureClick> clickGesture_;

	latero::graphics::GeneratorPtr gen_;

	latero::graphics::gtk::Animation largeFaceUpAnim_;
	latero::graphics::gtk::Animation faceUpAnim_;

	latero::graphics::BaseVirtualSurfaceWidget img_;

};

#endif

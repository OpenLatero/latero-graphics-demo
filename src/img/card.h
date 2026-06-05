#pragma once

#include "../config.h"
#ifndef DISABLE_GRAPHICS_DEMO

#include <boost/enable_shared_from_this.hpp>
#include "gtkmm.h"
#include <laterographics/virtualsurfacewidget.h>
#include <laterographics/generator.h>

class Card;
typedef boost::shared_ptr<Card> CardPtr;

class Card : public Gtk::Box, public boost::enable_shared_from_this<Card>
{
public:

	static CardPtr Create(latero::graphics::GeneratorPtr gen, uint width, uint height, uint scale) {
		return CardPtr(new Card(gen, width, height, scale));
	}

	~Card();

	Card(const Card& p);

	inline latero::graphics::GeneratorPtr GetGenerator() {
		return gen_;
	}

	sigc::signal<void(CardPtr)> signal_clicked;

	/** This is used to set the content of the large display. */
	latero::graphics::gtk::Animation GetLargeFaceUpAnim();

protected:
	Card(latero::graphics::GeneratorPtr gen, uint width, uint height, uint scale);
	void Initialize();

	Glib::RefPtr<Gtk::GestureClick> clickGesture_;

	latero::graphics::GeneratorPtr gen_;

	latero::graphics::gtk::Animation largeFaceUpAnim_;
	latero::graphics::gtk::Animation faceUpAnim_;

	latero::graphics::BaseVirtualSurfaceWidget img_;

};

#endif

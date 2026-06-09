#pragma once

#include "../config.h"
#ifndef DISABLE_GRAPHICS_DEMO

#include "gtkmm.h"
#include <laterographics/tactographview.h>
#include <laterographics/generator.h>

class Card;
typedef boost::shared_ptr<Card> CardPtr;

class Card : public Gtk::Box
{
public:

	static CardPtr Create(latero::graphics::GeneratorPtr gen) {
		return CardPtr(new Card(gen));
	}

	~Card();

	inline latero::graphics::GeneratorPtr GetGenerator() {
		return gen_;
	}

	sigc::signal<void()> signal_clicked;



protected:
	Card(latero::graphics::GeneratorPtr gen);

	Glib::RefPtr<Gtk::GestureClick> clickGesture_;

	latero::graphics::GeneratorPtr gen_;

	latero::graphics::TactographView img_;

};

#endif

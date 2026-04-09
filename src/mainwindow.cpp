// -----------------------------------------------------------
//
// Copyright (c) 2015 by Vincent Levesque. All Rights Reserved.
//
// This file is part of latero-demo.
//
//    latero-demo is free software: you can redistribute it and/or modify
//    it under the terms of the GNU General Public License as published by
//    the Free Software Foundation, either version 3 of the License, or
//    (at your option) any later version.
//
//    latero-demo is distributed in the hope that it will be useful,
//    but WITHOUT ANY WARRANTY; without even the implied warranty of
//    MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
//    GNU General Public License for more details.
//
//    You should have received a copy of the GNU General Public License
//    along with latero-demo.  If not, see <http://www.gnu.org/licenses/>.
//
// -----------------------------------------------------------

#include "mainwindow.h"
#include <sstream>
#include <iostream>

MainWindow::MainWindow(latero::graphics::TactileEngine *tEngine, latero::graphics::AudioEngine *aEngine, bool disableAudio) :
	mainbox_(Gtk::Orientation::VERTICAL),
	demobox_(Gtk::Orientation::VERTICAL),
#ifndef DISABLE_TEXTURE_DEMO
	textureDemo_(tEngine->Dev()),
#endif
#ifndef DISABLE_ICON_DEMO
	iconDemo_(tEngine->Dev(),this),
#endif
#ifndef DISABLE_VECTOR_DEMO
	vectorDemo_(tEngine->Dev()),
#endif
#ifndef DISABLE_SCHOOLBOOK_DEMO
	schoolbookDemo_(tEngine->Dev()),
#endif
#ifndef DISABLE_GRAPHICS_DEMO
	graphicsDemo_(tEngine->Dev()),
#endif
#ifndef DISABLE_BRAILLE_DEMO
	brailleDemo_(tEngine->Dev()),
#endif
	tEngine_(tEngine),
	aEngine_(aEngine),
	demo_(NULL)
{
	set_title("LATERO Tactile Graphics Demonstration");
	maximize();

	set_child(mainbox_);
	mainbox_.append(*CreateMenu());
	demobox_.set_vexpand(true);
	mainbox_.append(demobox_);

	std::cout << "Starting tactile & audio engines...\n";
	tEngine_->Start();
	if (!disableAudio) aEngine_->Start();

#ifndef DISABLE_VECTOR_DEMO
	OnDemoVector();
#else
#ifndef DISABLE_TEXTURE_DEMO
	OnDemoTexture();
#else
#ifndef DISABLE_GRAPHICS_DEMO
	OnDemoGraphics();
#else
#ifndef DISABLE_SCHOOLBOOK_DEMO
	OnDemoSchoolbook();
#else
#ifndef DISABLE_ICON_DEMO
	OnDemoIcon();
#endif
#ifndef DISABLE_BRAILLE_DEMO
	OnDemoBraille();
#endif

#endif
#endif
#endif
#endif
}

MainWindow::~MainWindow()
{
	std::cout << "~MainWindow()\n";

	std::cout << "Stopping tactile & audio engines...\n";
	tEngine_->Stop();
	aEngine_->Stop();
	std::cout << "Stopped tactile & audio engines...\n";
}



Gtk::Widget *MainWindow::CreateMenu()
{
	auto menuModel = Gio::Menu::create();

	// File menu
	auto fileMenu = Gio::Menu::create();
	fileMenu->append("Quit", "win.quit");
	menuModel->append_submenu("File", fileMenu);

	// View menu
	auto viewMenu = Gio::Menu::create();
	viewMenu->append("Fullscreen", "win.fullscreen");
	menuModel->append_submenu("View", viewMenu);

	// Demo menu
	auto demoMenu = Gio::Menu::create();
#ifndef DISABLE_VECTOR_DEMO
	demoMenu->append("Vector", "win.demo::vector");
#endif
#ifndef DISABLE_ICON_DEMO
	demoMenu->append("Icon", "win.demo::icon");
#endif
#ifndef DISABLE_TEXTURE_DEMO
	demoMenu->append("Texture", "win.demo::texture");
#endif
#ifndef DISABLE_GRAPHICS_DEMO
	demoMenu->append("Graphics", "win.demo::graphics");
#endif
#ifndef DISABLE_SCHOOLBOOK_DEMO
	demoMenu->append("Schoolbook", "win.demo::schoolbook");
#endif
#ifndef DISABLE_BRAILLE_DEMO
	demoMenu->append("Braille", "win.demo::braille");
#endif
	menuModel->append_submenu("Demo", demoMenu);

	// Quit action
	auto quitAction = Gio::SimpleAction::create("quit");
	quitAction->signal_activate().connect([this](const Glib::VariantBase&) { OnQuit(); });
	add_action(quitAction);

	// Fullscreen toggle action
	fullscreenAction_ = Gio::SimpleAction::create_stateful(
		"fullscreen", Glib::Variant<bool>::create(false));
	fullscreenAction_->signal_activate().connect(
		[this](const Glib::VariantBase&) { OnFullscreen(); });
	add_action(fullscreenAction_);

	// Demo radio action
	demoAction_ = Gio::SimpleAction::create_radio_string("demo", "none");
	demoAction_->signal_activate().connect([this](const Glib::VariantBase& v) {
		demoAction_->set_state(v);
		auto target = Glib::VariantBase::cast_dynamic<Glib::Variant<Glib::ustring>>(v).get();
#ifndef DISABLE_VECTOR_DEMO
		if (target == "vector") ReplaceDemo(&vectorDemo_);
#endif
#ifndef DISABLE_ICON_DEMO
		else if (target == "icon") ReplaceDemo(&iconDemo_);
#endif
#ifndef DISABLE_TEXTURE_DEMO
		else if (target == "texture") ReplaceDemo(&textureDemo_);
#endif
#ifndef DISABLE_GRAPHICS_DEMO
		else if (target == "graphics") ReplaceDemo(&graphicsDemo_);
#endif
#ifndef DISABLE_SCHOOLBOOK_DEMO
		else if (target == "schoolbook") ReplaceDemo(&schoolbookDemo_);
#endif
#ifndef DISABLE_BRAILLE_DEMO
		else if (target == "braille") ReplaceDemo(&brailleDemo_);
#endif
	});
	add_action(demoAction_);

	return Gtk::make_managed<Gtk::PopoverMenuBar>(menuModel);
}

void MainWindow::OnQuit()
{
	close();
}

void MainWindow::OnFullscreen()
{
	Glib::Variant<bool> state;
	fullscreenAction_->get_state(state);
	bool active = !state.get();
	fullscreenAction_->set_state(Glib::Variant<bool>::create(active));
	if (active) fullscreen(); else unfullscreen();
}

#ifndef DISABLE_VECTOR_DEMO
void MainWindow::OnDemoVector()
{
	demoAction_->activate(Glib::Variant<Glib::ustring>::create("vector"));
}
#endif

#ifndef DISABLE_ICON_DEMO
void MainWindow::OnDemoIcon()
{
	demoAction_->activate(Glib::Variant<Glib::ustring>::create("icon"));
}
#endif

#ifndef DISABLE_TEXTURE_DEMO
void MainWindow::OnDemoTexture()
{
	demoAction_->activate(Glib::Variant<Glib::ustring>::create("texture"));
}
#endif

#ifndef DISABLE_GRAPHICS_DEMO
void MainWindow::OnDemoGraphics()
{
	demoAction_->activate(Glib::Variant<Glib::ustring>::create("graphics"));
}
#endif

#ifndef DISABLE_SCHOOLBOOK_DEMO
void MainWindow::OnDemoSchoolbook()
{
	demoAction_->activate(Glib::Variant<Glib::ustring>::create("schoolbook"));
}
#endif

#ifndef DISABLE_BRAILLE_DEMO
void MainWindow::OnDemoBraille()
{
	demoAction_->activate(Glib::Variant<Glib::ustring>::create("braille"));
}
#endif


void MainWindow::ReplaceDemo(Demo *demo)
{
	if (demo_) demobox_.remove(*demo_);
	demo_ = demo;
	demobox_.append(*demo_);
	tEngine_->SetGenerator(demo_->Gen());
	aEngine_->SetGenerator(demo_->Gen());
}

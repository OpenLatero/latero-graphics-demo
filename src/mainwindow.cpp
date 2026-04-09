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
	demoMenu->append("Vector", "win.demo-vector");
#endif
#ifndef DISABLE_ICON_DEMO
	demoMenu->append("Icon", "win.demo-icon");
#endif
#ifndef DISABLE_TEXTURE_DEMO
	demoMenu->append("Texture", "win.demo-texture");
#endif
#ifndef DISABLE_GRAPHICS_DEMO
	demoMenu->append("Graphics", "win.demo-graphics");
#endif
#ifndef DISABLE_SCHOOLBOOK_DEMO
	demoMenu->append("Schoolbook", "win.demo-schoolbook");
#endif
#ifndef DISABLE_BRAILLE_DEMO
	demoMenu->append("Braille", "win.demo-braille");
#endif
	menuModel->append_submenu("Demo", demoMenu);

	auto actionGroup = Gio::SimpleActionGroup::create();

	auto quitAction = Gio::SimpleAction::create("quit");
	quitAction->signal_activate().connect([this](const Glib::VariantBase&) { OnQuit(); });
	actionGroup->add_action(quitAction);

	auto fullscreenAction = Gio::SimpleAction::create("fullscreen");
	fullscreenAction->signal_activate().connect([this](const Glib::VariantBase&) { OnFullscreen(); });
	actionGroup->add_action(fullscreenAction);

#ifndef DISABLE_VECTOR_DEMO
	auto vectorAction = Gio::SimpleAction::create("demo-vector");
	vectorAction->signal_activate().connect([this](const Glib::VariantBase&) { ReplaceDemo(&vectorDemo_); });
	actionGroup->add_action(vectorAction);
#endif
#ifndef DISABLE_ICON_DEMO
	auto iconAction = Gio::SimpleAction::create("demo-icon");
	iconAction->signal_activate().connect([this](const Glib::VariantBase&) { ReplaceDemo(&iconDemo_); });
	actionGroup->add_action(iconAction);
#endif
#ifndef DISABLE_TEXTURE_DEMO
	auto textureAction = Gio::SimpleAction::create("demo-texture");
	textureAction->signal_activate().connect([this](const Glib::VariantBase&) { ReplaceDemo(&textureDemo_); });
	actionGroup->add_action(textureAction);
#endif
#ifndef DISABLE_GRAPHICS_DEMO
	auto graphicsAction = Gio::SimpleAction::create("demo-graphics");
	graphicsAction->signal_activate().connect([this](const Glib::VariantBase&) { ReplaceDemo(&graphicsDemo_); });
	actionGroup->add_action(graphicsAction);
#endif
#ifndef DISABLE_SCHOOLBOOK_DEMO
	auto schoolbookAction = Gio::SimpleAction::create("demo-schoolbook");
	schoolbookAction->signal_activate().connect([this](const Glib::VariantBase&) { ReplaceDemo(&schoolbookDemo_); });
	actionGroup->add_action(schoolbookAction);
#endif
#ifndef DISABLE_BRAILLE_DEMO
	auto brailleAction = Gio::SimpleAction::create("demo-braille");
	brailleAction->signal_activate().connect([this](const Glib::VariantBase&) { ReplaceDemo(&brailleDemo_); });
	actionGroup->add_action(brailleAction);
#endif

	insert_action_group("win", actionGroup);

	return Gtk::make_managed<Gtk::PopoverMenuBar>(menuModel);
}

void MainWindow::OnQuit()
{
	close();
}

void MainWindow::OnFullscreen()
{
	isFullscreen_ = !isFullscreen_;
	if (isFullscreen_) fullscreen(); else unfullscreen();
}

#ifndef DISABLE_VECTOR_DEMO
void MainWindow::OnDemoVector()   { ReplaceDemo(&vectorDemo_); }
#endif
#ifndef DISABLE_ICON_DEMO
void MainWindow::OnDemoIcon()     { ReplaceDemo(&iconDemo_); }
#endif
#ifndef DISABLE_TEXTURE_DEMO
void MainWindow::OnDemoTexture()  { ReplaceDemo(&textureDemo_); }
#endif
#ifndef DISABLE_GRAPHICS_DEMO
void MainWindow::OnDemoGraphics() { ReplaceDemo(&graphicsDemo_); }
#endif
#ifndef DISABLE_SCHOOLBOOK_DEMO
void MainWindow::OnDemoSchoolbook() { ReplaceDemo(&schoolbookDemo_); }
#endif
#ifndef DISABLE_BRAILLE_DEMO
void MainWindow::OnDemoBraille()  { ReplaceDemo(&brailleDemo_); }
#endif


void MainWindow::ReplaceDemo(Demo *demo)
{
	if (demo_) demobox_.remove(*demo_);
	demo_ = demo;
	demobox_.append(*demo_);
	tEngine_->SetGenerator(demo_->Gen());
	aEngine_->SetGenerator(demo_->Gen());
}

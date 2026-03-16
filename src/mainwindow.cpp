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

	add(mainbox_);
	mainbox_.pack_start(*CreateMenu(), Gtk::PACK_SHRINK);
	mainbox_.pack_start(demobox_);

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

	show_all_children();
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
	auto menubar = Gtk::manage(new Gtk::MenuBar());

	// File menu
	auto fileMenu = Gtk::manage(new Gtk::Menu());
	auto fileMenuItem = Gtk::manage(new Gtk::MenuItem("File"));
	fileMenuItem->set_submenu(*fileMenu);

	auto quitItem = Gtk::manage(new Gtk::MenuItem("Quit"));
	quitItem->signal_activate().connect(sigc::mem_fun(*this, &MainWindow::OnQuit));
	fileMenu->append(*quitItem);
	fileMenu->show_all();

	// View menu
	auto viewMenu = Gtk::manage(new Gtk::Menu());
	auto viewMenuItem = Gtk::manage(new Gtk::MenuItem("View"));
	viewMenuItem->set_submenu(*viewMenu);

	auto fullscreenItem = Gtk::manage(new Gtk::CheckMenuItem("Fullscreen"));
	actionFullscreen_ = fullscreenItem;
	fullscreenItem->signal_activate().connect(sigc::mem_fun(*this, &MainWindow::OnFullscreen));
	viewMenu->append(*fullscreenItem);
	viewMenu->show_all();

	// Demo menu
	auto demoMenu = Gtk::manage(new Gtk::Menu());
	auto demoMenuItem = Gtk::manage(new Gtk::MenuItem("Demo"));
	demoMenuItem->set_submenu(*demoMenu);

	Gtk::RadioMenuItem::Group demoGroup;

#ifndef DISABLE_VECTOR_DEMO
	auto vectorItem = Gtk::manage(new Gtk::RadioMenuItem(demoGroup, "Vector"));
	actionDemoVector_ = vectorItem;
	vectorItem->signal_activate().connect(sigc::mem_fun(*this, &MainWindow::OnDemoVector));
	demoMenu->append(*vectorItem);
#endif

#ifndef DISABLE_ICON_DEMO
	auto iconItem = Gtk::manage(new Gtk::RadioMenuItem(demoGroup, "Icon"));
	actionDemoIcon_ = iconItem;
	iconItem->signal_activate().connect(sigc::mem_fun(*this, &MainWindow::OnDemoIcon));
	demoMenu->append(*iconItem);
#endif

#ifndef DISABLE_TEXTURE_DEMO
	auto textureItem = Gtk::manage(new Gtk::RadioMenuItem(demoGroup, "Texture"));
	actionDemoTexture_ = textureItem;
	textureItem->signal_activate().connect(sigc::mem_fun(*this, &MainWindow::OnDemoTexture));
	demoMenu->append(*textureItem);
#endif

#ifndef DISABLE_GRAPHICS_DEMO
	auto graphicsItem = Gtk::manage(new Gtk::RadioMenuItem(demoGroup, "Graphics"));
	actionDemoGraphics_ = graphicsItem;
	graphicsItem->signal_activate().connect(sigc::mem_fun(*this, &MainWindow::OnDemoGraphics));
	demoMenu->append(*graphicsItem);
#endif

#ifndef DISABLE_SCHOOLBOOK_DEMO
	auto schoolbookItem = Gtk::manage(new Gtk::RadioMenuItem(demoGroup, "Schoolbook"));
	actionDemoSchoolbook_ = schoolbookItem;
	schoolbookItem->signal_activate().connect(sigc::mem_fun(*this, &MainWindow::OnDemoSchoolbook));
	demoMenu->append(*schoolbookItem);
#endif

#ifndef DISABLE_BRAILLE_DEMO
	auto brailleItem = Gtk::manage(new Gtk::RadioMenuItem(demoGroup, "Braille"));
	actionDemoBraille_ = brailleItem;
	brailleItem->signal_activate().connect(sigc::mem_fun(*this, &MainWindow::OnDemoBraille));
	demoMenu->append(*brailleItem);
#endif

	demoMenu->show_all();

	// Assemble menubar
	menubar->append(*fileMenuItem);
	menubar->append(*viewMenuItem);
	menubar->append(*demoMenuItem);
	menubar->show_all();

	return menubar;
}

void MainWindow::OnQuit()
{
	close();
}

void MainWindow::OnFullscreen()
{
	if (actionFullscreen_ && actionFullscreen_->get_active())
		fullscreen();
	else
		unfullscreen();
}

#ifndef DISABLE_VECTOR_DEMO
void MainWindow::OnDemoVector()
{
	if (actionDemoVector_->get_active())
		ReplaceDemo(&vectorDemo_);
}
#endif

#ifndef DISABLE_ICON_DEMO
void MainWindow::OnDemoIcon()
{
	if (actionDemoIcon_->get_active())
		ReplaceDemo(&iconDemo_);

}
#endif

#ifndef DISABLE_TEXTURE_DEMO
void MainWindow::OnDemoTexture()
{
	if (actionDemoTexture_->get_active())
		ReplaceDemo(&textureDemo_);
}
#endif

#ifndef DISABLE_GRAPHICS_DEMO
void MainWindow::OnDemoGraphics()
{
	if (actionDemoGraphics_->get_active())
		ReplaceDemo(&graphicsDemo_);
}
#endif

#ifndef DISABLE_SCHOOLBOOK_DEMO
void MainWindow::OnDemoSchoolbook()
{
	if (actionDemoSchoolbook_->get_active())
		ReplaceDemo(&schoolbookDemo_);
}
#endif

#ifndef DISABLE_BRAILLE_DEMO
void MainWindow::OnDemoBraille()
{
	if (actionDemoBraille_->get_active())
		ReplaceDemo(&brailleDemo_);
}
#endif


void MainWindow::ReplaceDemo(Demo *demo)
{
	if (demo_) demobox_.remove(*demo_);
	demo_ = demo;
	demobox_.add(*demo_);
	show_all_children();
	tEngine_->SetGenerator(demo_->Gen());
	aEngine_->SetGenerator(demo_->Gen());
}

#pragma once

#include "config.h"
#include <gtkmm.h>
#include <giomm.h>
#include <laterographics/tactileengine.h>
#include <laterographics/audioengine.h>
#include "img/demo.h"
#include "icon/demo.h"
#include "texture/demo.h"
#include "schoolbook/demo.h"
#include "braille/demo.h"
#include "vector/demo.h"

class MainWindow : public Gtk::ApplicationWindow
{
public:
	MainWindow(latero::graphics::TactileEngine *tEngine, latero::graphics::AudioEngine *aEngine, bool disableAudio);
	virtual ~MainWindow();

protected:
	void OnQuit();
	void OnFullscreen();

#ifndef DISABLE_TEXTURE_DEMO
	TextureDemo::Demo textureDemo_;
	void OnDemoTexture();
#endif

#ifndef DISABLE_ICON_DEMO
	IconDemo::Demo iconDemo_;
	void OnDemoIcon();
#endif

#ifndef DISABLE_VECTOR_DEMO
	VectorDemo::Demo vectorDemo_;
	void OnDemoVector();
#endif

#ifndef DISABLE_SCHOOLBOOK_DEMO
	SchoolbookDemo::Demo schoolbookDemo_;
	void OnDemoSchoolbook();
#endif

#ifndef DISABLE_GRAPHICS_DEMO
	ImgDemo::Demo graphicsDemo_;
	void OnDemoGraphics();
#endif

#ifndef DISABLE_BRAILLE_DEMO
	BrailleDemo::Demo brailleDemo_;
	void OnDemoBraille();
#endif

	void ReplaceDemo(Demo *demo);
	void CreateMenu();

	bool isFullscreen_ = false;

	Gtk::Box mainbox_;
	Gtk::Box demobox_;
	latero::graphics::TactileEngine *tEngine_;
	latero::graphics::AudioEngine *aEngine_;
	Demo *demo_;
};

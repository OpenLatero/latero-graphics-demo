#include "../config.h"
#ifndef DISABLE_ICON_DEMO


#include "demo.h"

namespace IconDemo {

Demo::Demo(const latero::Tactograph *dev, Gtk::Window *window) :
	peer_(GeneratorPtr(new Generator(dev))),
	mainBox_(Gtk::Orientation::VERTICAL),
	preview_(dev, peer_, true),
	genToolbar_(peer_,window)
{
	preview_.ShowCursor();
	preview_.AnimateCursor(true);
	preview_.set_vexpand(true);

	// prepare main view...
	mainBox_.append(genToolbar_);
	mainBox_.append(preview_);
	set_child(mainBox_);
};

}; // namespace

#endif // !DISABLED

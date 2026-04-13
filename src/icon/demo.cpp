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

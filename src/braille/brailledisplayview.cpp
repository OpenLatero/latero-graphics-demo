#include "../config.h"
#ifndef DISABLE_BRAILLE_DEMO
#include <laterographics/tactiledisplayview.h>
#include "brailledisplayview.h"

BrailleDisplayView::BrailleDisplayView(BrailleGenPtr peer) :
 	Gtk::AspectFrame(0.5, 0.5, peer->Dev()->GetSurfaceWidth()/peer->Dev()->GetHeight(), false),
	dev_(peer->Dev()),
	tdState_(peer->Dev()->GetFrameSizeX(), peer->Dev()->GetFrameSizeY()),
	peer_(peer),
	tdPainter_(dev_)
{
    drawingArea_.set_draw_func(sigc::mem_fun(*this, &BrailleDisplayView::OnDraw));

	set_child(drawingArea_);

	Glib::signal_timeout().connect(
		sigc::mem_fun(*this, &BrailleDisplayView::RefreshCursor),
		(uint)33, // ms
		Glib::PRIORITY_DEFAULT_IDLE);

	Glib::signal_timeout().connect(
		sigc::mem_fun(*this, &BrailleDisplayView::OnCheckPeer),
		(uint)333, // ms
		Glib::PRIORITY_DEFAULT_IDLE);

	drawingArea_.signal_resize().connect(
		[this](int, int) { RefreshBackground(); });
}

void BrailleDisplayView::OnDraw(const Cairo::RefPtr<Cairo::Context>& cr, int width, int height)
{
	if (!bg_)
	{
		cr->set_source_rgb(1.0, 1.0, 1.0);
		cr->paint();
		return;
	}

	if (width == 0 || height == 0)
		return;

	Glib::RefPtr<Gdk::Pixbuf> buf = bg_;
	if (buf)
	{
		buf = buf->scale_simple(width,height,Gdk::InterpType::NEAREST);
        Gdk::Cairo::set_source_pixbuf(cr, buf, 0, 0);
        cr->paint();
	}

	// draw cursor
	cr->scale(width / dev_->GetSurfaceWidth(), height / dev_->GetHeight()); // scale to mm
	cr->translate(pos_, dev_->GetHeight()/2);	// shift origin to center of TD

	tdPainter_.Paint(cr, tdState_, false);
}

void BrailleDisplayView::SetBackground(Glib::RefPtr<Gdk::Pixbuf> bg)
{
	bg_ = bg;
	drawingArea_.queue_draw();
}




bool BrailleDisplayView::RefreshCursor()
{
	latero::BiasedImg frame = peer_->GetLatestFrame();
	pos_ = peer_->GetLastPos();
	tdState_ = frame;
	drawingArea_.queue_draw();
	return true;
}


bool BrailleDisplayView::OnCheckPeer()
{
	if (peer_)
	{
		// if the background has never been updated or peer has been modified since
		if (bgUpdateTime_.is_not_a_date_time() || (peer_->GetLastModified() > bgUpdateTime_))
			RefreshBackground();
	}
	return true;
}

void BrailleDisplayView::RefreshBackground()
{
	if (drawingArea_.get_width() == 0 || drawingArea_.get_height() == 0)
		return;
	bgUpdateTime_ = boost::posix_time::microsec_clock::universal_time();
	latero::graphics::gtk::Animation anim = peer_->GetIllustration(drawingArea_.get_width(),drawingArea_.get_height());
	SetBackground(anim);
}


#endif

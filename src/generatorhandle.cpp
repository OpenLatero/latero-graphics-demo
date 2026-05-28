#include "generatorhandle.h"

GeneratorHandle::GeneratorHandle(const latero::Tactograph *dev) :
	Generator(dev)
{
}

GeneratorHandle::~GeneratorHandle()
{
}

void GeneratorHandle::DoRender_(const latero::graphics::State *state, latero::BiasedImg &frame)
{
	if (gen_)
		gen_->Render_(state, frame);
	else
		frame.Set(0);
}

void GeneratorHandle::SetGenerator(latero::graphics::GeneratorPtr gen)
{
	LATERO_GRAPHICS_GUARD
	SetLastModified_();
	if (gen_) RemoveModifiableChild_(gen_);
	gen_ = gen;
	if (gen_) AddModifiableChild_(gen_);
}

latero::graphics::gtk::Animation GeneratorHandle::GetIllustration(uint w, boost::posix_time::time_duration t) const
{
	LATERO_GRAPHICS_GUARD;
	if (gen_)
		return gen_->GetIllustration(w,t);
	else
		return Generator::GetIllustration(w,t);
}

void GeneratorHandle::PlayAudio(latero::graphics::AudioDevicePtr dev)
{
	latero::graphics::GeneratorPtr gen = GetGenerator();
	if (gen)
	  gen->PlayAudio(dev);
}

latero::graphics::GeneratorPtr GeneratorHandle::GetGenerator()
{
	LATERO_GRAPHICS_GUARD;
	return gen_;
}

bool GeneratorHandle::OnKeyPress(guint keyval, guint keycode, Gdk::ModifierType state)
{
	return GetGenerator()->OnKeyPress(keyval, keycode, state);
}

Gtk::Widget *GeneratorHandle::CreateWidget(latero::graphics::GeneratorPtr)
{
	LATERO_GRAPHICS_GUARD;
	if (gen_)
		return gen_->CreateWidget(gen_);
	return Generator::CreateWidget(latero::graphics::GeneratorPtr());
}

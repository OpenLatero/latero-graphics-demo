#pragma once

#include <laterographics/generator.h>

class GeneratorHandle;
typedef boost::shared_ptr<GeneratorHandle> GeneratorHandlePtr;

class GeneratorHandle : public latero::graphics::Generator
{
public:
	GeneratorHandle(const latero::Tactograph *dev);
	virtual ~GeneratorHandle();
	virtual void AppendXML(latero::graphics::XMLOutputNode &root) const {};
	virtual latero::graphics::gtk::Animation GetIllustration(uint w, boost::posix_time::time_duration t) const;
	virtual void PlayAudio(latero::graphics::AudioDevicePtr dev);
	void SetGenerator(latero::graphics::GeneratorPtr gen);
	latero::graphics::GeneratorPtr GetGenerator();
	virtual bool OnKeyPress(guint keyval, guint keycode, Gdk::ModifierType state);
	virtual Gtk::Widget *CreateWidget(latero::graphics::GeneratorPtr ptr);

protected:
	virtual void DoRender_(const latero::graphics::State *state, latero::BiasedImg &frame);
	latero::graphics::GeneratorPtr gen_;
};
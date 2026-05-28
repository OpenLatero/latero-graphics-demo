#pragma once

#include "../config.h"
#ifndef DISABLE_VECTOR_DEMO

#include <laterographics/virtualsurfacewidget.h>
#include <laterographics/graphics/canvas.h>
#include <laterographics/graphics/canvaswidget.h>
#include "../demo.h"


namespace VectorDemo {

class Demo : public ::Demo
{
public:
	Demo(const latero::Tactograph *dev);
	virtual ~Demo() {};
	virtual latero::graphics::GeneratorPtr Gen() { return peer_; };
protected:
	bool RefreshCursor();
	void OnChange();

	latero::graphics::VirtualSurfaceWidget preview_;
	latero::graphics::CanvasPtr peer_;
	latero::graphics::CanvasWidget *vectorWidget_;
};

}; // namespace

#endif

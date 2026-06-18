#pragma once

#include "../config.h"
#ifndef DISABLE_ICON_DEMO

#include <laterographics/graphics/texture/texture.h>
#include "../generatorhandle.h"
#include <laterographics/graphics/canvas.h>
#include <laterographics/graphics/closedpattern.h>
#include <laterographics/graphics/stroke.h>

namespace IconDemo {

class Generator;
typedef std::shared_ptr<Generator> GeneratorPtr;

class Generator : public latero::graphics::Canvas
{
public:
	enum {SIZE_S, SIZE_M, SIZE_L};
	enum {CONTOUR_THICK_S, CONTOUR_THICK_M, CONTOUR_THICK_L};
	enum {CONTOUR_VIB, CONTOUR_NONE, CONTOUR_DOT, CONTOUR_STROKE};
	enum {SHAPE_CIRCLE, SHAPE_TRIANGLE, SHAPE_SQUARE, SHAPE_RATRIANG, SHAPE_DIAMOND, SHAPE_PLUS};

public:
	Generator(const latero::Tactograph *dev);
	virtual ~Generator() {};

	virtual void AppendXML(latero::graphics::XMLOutputNode &root) {};

	void SetContour(int id);
	int GetContour();

	void SetContourThickness(int id);
	int GetContourThickness();

	void SetShape(int shape);
	int GetShape();

	void SetSize(int shape);
	int GetSize();

	latero::graphics::TexturePtr GetAreaTexture() const;
	void SetAreaTexture(const latero::graphics::TexturePtr tx);

protected:

	std::vector<latero::Point> GetPolygon(int shape, double size);
	double GetSize_();
	double GetStrokeWidth();

	void UpdateGen();
	latero::graphics::StrokePtr stroke_;
	latero::graphics::ClosedPatternPtr icon_;
	latero::graphics::TexturePtr areaTexture_;

	int sizeId_;
	int contourThickness_;
	int contour_;
	int shape_;
};

} // namespace

#endif // !DISABLED

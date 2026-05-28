#pragma once

#include "../config.h"
#ifndef DISABLE_BRAILLE_DEMO

#include <laterographics/modifiable.h>
#include <string>

class Modulator : public latero::graphics::Modifiable
{
public:
	Modulator();
	virtual ~Modulator();
	double GetFixedAmp();
	void SetFixedAmp(float v);
	inline double GetFixedAmp_() { return fixedAmp_; }

	double GetAmp(double vel, double period);
	double GetAmp_(double vel, double period);

	void SetModeFixed();
	void SetModeVel();

	void GetRampRange(double &vmin, double &vmax);
	void SetRampRange(double vmin, double vmax);

	void GetRampAmpRange(double &vmin, double &vmax);
	void SetRampAmpRange(double vmin, double vmax);

	double GetMaxRiseRate();
	void SetMaxRiseRate(double v);
	double GetMaxFallRate();
	void SetMaxFallRate(double v);

	std::string GetDesc(std::string prefix);

protected:
	double fixedAmp_;
	int mode_;
	double vmin_;
	double vmax_;
	double amin_;
	double amax_;
	double maxRiseRate_; // in second per full transition (0.0 to 1.0)
	double maxFallRate_;

	double amp_;
};

#endif

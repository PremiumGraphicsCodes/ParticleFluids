#pragma once

#include "IWindow.h"

namespace Crystal {
	namespace UI {

class DoubleView : public IWindow
{
public:
	DoubleView(const std::string& name, const double value) :
		IWindow(name),
		value(value)
	{}

	void show() override;

	double getValue() const { return value; }

private:
	double value;
};

	}
}
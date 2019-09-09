#pragma once

#include "IWindow.h"

#include "IntView.h"

namespace Crystal {
	namespace Shape {
		class WireFrame;
	}
	namespace UI {

class WireFrameView : public IWindow
{
public:
	explicit WireFrameView(const std::string& name);

	void onShow() override;

	void setValue(Shape::WireFrame* value);

private:
	IntView edgeCount;
};

	}
}
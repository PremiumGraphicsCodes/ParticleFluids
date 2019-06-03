#pragma once

#include "IWindow.h"
#include "imgui.h"

#include "IntView.h"
#include "StringView.h"
#include "FaceView.h"

namespace Crystal {
	namespace Shape {
		class FaceGroup;
	}
	namespace UI {

class FaceGroupView : public IWindow
{
public:
	explicit FaceGroupView(const std::string& name);

	FaceGroupView(const std::string& name, Shape::FaceGroup* value);

	void show() override;

	void setValue(Shape::FaceGroup* value);

	Shape::FaceGroup* getValue() const { return value; }

private:
	IntView id;
	IntView faceCount;
	IntView attributeId;
	Shape::FaceGroup* value;
};

	}
}
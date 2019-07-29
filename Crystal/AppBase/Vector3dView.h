#pragma once

#include "IWindow.h"

#include "imgui.h"

#include "../Math/Vector3d.h"

namespace Crystal {
	namespace UI {

class Vector3dView : public IWindow
{
public:
	explicit Vector3dView(const std::string& name) :
		IWindow(name),
		value(0,0,0)
	{}

	Vector3dView(const std::string& name, const Math::Vector3dd& value) :
		IWindow(name),
		value(value)
	{}

	void show() override {
		ImGui::InputDouble("X", &value.x);
		ImGui::InputDouble("Y", &value.y);
		ImGui::InputDouble("Z", &value.z);

		//ImGui::InputFloat3(name.c_str(), &value[0]);
	}

	void setValue(const Math::Vector3dd& value) { this->value = value; }

	Math::Vector3dd getValue() const { return value; }

private:
	Math::Vector3dd value;
};

	}
}
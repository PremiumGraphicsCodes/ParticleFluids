#include "Cylinder3dButton.h"

#include "../Math/Cylinder3d.h"

#include "imgui.h"

using namespace Crystal::Math;
using namespace Crystal::UI;

void Cylinder3dButton::onShow()
{
	ImGui::InputFloat3("Center", &center[0]);
	ImGui::InputDouble("Radius", &radius);
	ImGui::InputDouble("Height", &radius);
}

void Cylinder3dButton::onOk()
{
}

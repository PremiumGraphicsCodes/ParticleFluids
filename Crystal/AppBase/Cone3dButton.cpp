#include "Cone3dButton.h"

#include "imgui.h"

#include "../Math/Cone3d.h"
#include "../Shape/WireFrameBuilder.h"

using namespace Crystal::Math;
using namespace Crystal::UI;

void Cone3dButton::onShow()
{
	ImGui::InputFloat3("Center", &center[0]);
	ImGui::InputDouble("Radius", &radius);
	ImGui::InputDouble("Height", &height);
}

void Cone3dButton::onOk()
{
}

#include "Sphere3dButton.h"

#include "imgui.h"

using namespace Crystal::Math;
using namespace Crystal::UI;

void Sphere3dButton::onShow()
{
	ImGui::InputFloat3("Center", &center[0]);
	ImGui::InputDouble("Radius", &radius);
}

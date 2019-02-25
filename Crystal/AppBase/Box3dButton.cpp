#include "Box3dButton.h"

#include "imgui.h"

using namespace Crystal::Math;
using namespace Crystal::UI;

void Box3dButton::onShow()
{
	ImGui::InputFloat3("Min", &min[0]);
	ImGui::InputFloat3("Max", &max[0]);
}

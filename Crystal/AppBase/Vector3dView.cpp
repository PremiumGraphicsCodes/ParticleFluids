#include "Vector3dView.h"

#include "imgui.h"

using namespace Crystal::Math;
using namespace Crystal::UI;

void Vector3dView::show()
{
	ImGui::InputDouble("X", &value.x);
	ImGui::InputDouble("Y", &value.y);
	ImGui::InputDouble("Z", &value.z);

	//ImGui::InputFloat3(name.c_str(), &value[0]);
}

#include "Vector3dView.h"

#include "imgui.h"

using namespace Crystal::Math;
using namespace Crystal::UI;

void Vector3dView::show()
{
	const auto str = name.c_str();
	ImGui::InputFloat3(str, &value[0]);
}


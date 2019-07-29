#include "Vector3dView.h"

#include "imgui.h"

using namespace Crystal::Math;
using namespace Crystal::UI;

void Vector3dView::show()
{
	ImGui::InputFloat3(name.c_str(), &value[0]);
}

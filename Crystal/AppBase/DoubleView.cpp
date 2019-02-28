#include "DoubleView.h"

#include "imgui.h"

using namespace Crystal::UI;

void DoubleView::show()
{
	const auto str = name.c_str();
	ImGui::InputDouble(str, &value);
}

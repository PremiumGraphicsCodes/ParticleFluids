#include "WFAttributeButton.h"

#include "imgui.h"

using namespace Crystal::Math;
using namespace Crystal::UI;

void WFAttributeButton::onShow()
{
	ImGui::ColorPicker4("Color", &color[0]);
}

void WFAttributeButton::onOk()
{
}

void WFAttributeButton::onCancel()
{
}

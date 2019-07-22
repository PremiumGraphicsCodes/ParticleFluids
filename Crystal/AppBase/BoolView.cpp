#include "BoolView.h"
#include "imgui.h"

using namespace Crystal::UI;

BoolView::BoolView(const std::string& name) :
	BoolView(name, false)
{}

BoolView::BoolView(const std::string& name, const bool value) :
	IWindow(name),
	value(value)
{}

void BoolView::show()
{
	ImGui::Checkbox(name.c_str(), &value);
}

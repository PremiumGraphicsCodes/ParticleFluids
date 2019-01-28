#include "IPanel.h"

#include "imgui.h"
#include <algorithm>

using namespace Crystal::UI;

void IPanel::show()
{
	ImGui::Begin(name.c_str());

	std::for_each(children.begin(), children.end(), [](auto c) {c->show(); });

	ImGui::End();

}

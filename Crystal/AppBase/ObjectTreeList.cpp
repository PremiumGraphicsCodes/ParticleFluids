#include "ObjectTreeList.h"

#include "imgui.h"

using namespace Crystal::UI;

ObjectTreeList::ObjectTreeList(const std::string& name, Model* model, Canvas* canvas) :
	ITreeList(name, model, canvas)
{
}

void ObjectTreeList::onShow()
{
	const auto& particleSystems = getModel()->getObjects()->getParticleSystems();

	auto n = getName();
	auto str = n.c_str();
	ImGui::Begin(str);

	ImGui::BeginChild(str, ImVec2(250, 100), ImGuiWindowFlags_NoTitleBar);
	for (auto ps : particleSystems) {
		char str[256];
		sprintf(str, "%d", ps.getId());
		ImGui::Text(str);
	}
	ImGui::EndChild();

	ImGui::End();
}

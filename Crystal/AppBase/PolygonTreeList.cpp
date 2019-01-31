#include "PolygonTreeList.h"

#include "imgui.h"

using namespace Crystal::UI;

PolygonTreeList::PolygonTreeList(const std::string& name, Model* model, Canvas* canvas) :
	ITreeList(name, model, canvas)
{
}

void PolygonTreeList::onShow()
{
	auto n = getName();
	auto str = n.c_str();
	ImGui::Begin(str);

	const auto& polygons = getModel()->getObjects()->getPolygonMeshes()->getObjects();
	ImGui::BeginChild("Polygons", ImVec2(250, 100), ImGuiWindowFlags_NoTitleBar);

	for (const auto& polygon : polygons) {
		const auto& n = polygon.getName();
		const auto str = n.c_str();

		bool b = polygon.isVisible();
		ImGui::Checkbox(str, &b);

//		ImGui::Text(str);
	}

	ImGui::EndChild();

	ImGui::End();
}

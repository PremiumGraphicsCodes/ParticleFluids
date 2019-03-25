#include "PolygonTreeList.h"

#include "imgui.h"

using namespace Crystal::UI;

PolygonTreeList::PolygonTreeList(const std::string& name, Repository* model, Canvas* canvas) :
	ITreeList(name, model, canvas)
{
}

void PolygonTreeList::onShow()
{
	auto n = getName();
	auto str = n.c_str();
	ImGui::Begin(str);

	const auto& polygons = getRepository()->getObjects()->getPolygonMeshes()->getObjects();
	ImGui::BeginChild("Polygons", ImVec2(250, 100), ImGuiWindowFlags_NoTitleBar);

	for (const auto& polygon : polygons) {
		const auto& n = polygon->getName();
		const auto str = n.c_str();

		if (ImGui::Checkbox(str, &polygon->_isVisible)) {
			getCanvas()->setViewModel(getRepository()->toViewModel());
			getCanvas()->fitCamera(getRepository()->getBoundingBox());
			//polygon->_isVisible = !polygon->_isVisible;
		}

//		ImGui::Text(str);
	}

	ImGui::EndChild();

	ImGui::End();
}

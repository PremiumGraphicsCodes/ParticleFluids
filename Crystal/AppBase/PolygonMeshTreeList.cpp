#include "PolygonMeshTreeList.h"

#include "imgui.h"

using namespace Crystal::UI;

PolygonMeshTreeList::PolygonMeshTreeList(const std::string& name, Repository* model, Canvas* canvas) :
	ITreeList(name, model, canvas)
{
}

void PolygonMeshTreeList::onShow()
{
	const auto& polygons = getRepository()->getObjects()->getFactory()->getObjects();
	ImGui::BeginChild("Polygons", ImVec2(250, 100), ImGuiWindowFlags_NoTitleBar);

	for (const auto& polygon : polygons) {
		const auto& n = polygon->getName();
		const auto str = n.c_str();

		if (ImGui::Checkbox(str, &polygon->_isVisible)) {
			getCanvas()->setViewModel(getRepository()->toViewModel());
//			getCanvas()->fitCamera(getRepository()->getBoundingBox());
			//polygon->_isVisible = !polygon->_isVisible;
		}

//		ImGui::Text(str);
	}

	ImGui::EndChild();
}

#include "WireFrameTreeList.h"

#include "imgui.h"

using namespace Crystal::UI;

WireFrameTreeList::WireFrameTreeList(const std::string& name, Repository* model, Canvas* canvas) :
	ITreeList(name, model, canvas)
{
}

void WireFrameTreeList::onShow()
{
	auto n = getName();
	auto str = n.c_str();
	ImGui::Begin(str);

	const auto& wires = getRepository()->getObjects()->getWireFrames()->getObjects();
	ImGui::BeginChild("WireFrames", ImVec2(250, 100), ImGuiWindowFlags_NoTitleBar);
	ImGui::Text("WireFrames");
	for (auto ws : wires) {
		const auto name = ws->getName();
		if (ImGui::Checkbox(name.c_str(), &ws->_isVisible)) {
			getCanvas()->setViewModel(getRepository()->toViewModel());
//			getCanvas()->fitCamera(getRepository()->getBoundingBox());
		}
	}
	ImGui::EndChild();

	ImGui::End();
}

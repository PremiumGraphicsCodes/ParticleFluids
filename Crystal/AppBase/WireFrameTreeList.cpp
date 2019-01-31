#include "WireFrameTreeList.h"

#include "imgui.h"

using namespace Crystal::UI;

WireFrameTreeList::WireFrameTreeList(const std::string& name, Model* model, Canvas* canvas) :
	ITreeList(name, model, canvas)
{
}

void WireFrameTreeList::onShow()
{
	auto n = getName();
	auto str = n.c_str();
	ImGui::Begin(str);

	const auto& wires = getModel()->getObjects()->getWireFrames();
	ImGui::BeginChild("WireFrames", ImVec2(250, 100), ImGuiWindowFlags_NoTitleBar);
	ImGui::Text("WireFrames");
	for (auto ws : wires) {
		const auto name = ws.getName();
		ImGui::Checkbox(name.c_str(), &ws._isVisible);
	}
	ImGui::EndChild();

	ImGui::End();
}

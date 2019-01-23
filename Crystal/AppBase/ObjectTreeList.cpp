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

	ImGui::BeginChild("ParticleSystems", ImVec2(250, 100), ImGuiWindowFlags_NoTitleBar);
	ImGui::Text("ParticleSystems");
	for (auto ps : particleSystems) {
		char str[256];
		sprintf(str, "%d", ps.getId());
		ImGui::Text(str);
	}
	ImGui::EndChild();

	const auto& wires = getModel()->getObjects()->getWireFrames();
	ImGui::BeginChild("WireFrames", ImVec2(250, 100), ImGuiWindowFlags_NoTitleBar);
	ImGui::Text("WireFrames");
	for (auto ws : wires) {
		char str[256];
		sprintf(str, "%d", ws.getId());
		ImGui::Text(str);
	}
	ImGui::EndChild();

	const auto& polygons = getModel()->getObjects()->getPolygonMeshes();
	ImGui::BeginChild("Polygons", ImVec2(250, 100), ImGuiWindowFlags_NoTitleBar);
	ImGui::Text("Polygons");
	for (auto ws : polygons) {
		char str[256];
		sprintf(str, "%d", ws.getId());
		ImGui::Text(str);
	}
	ImGui::EndChild();



	ImGui::End();
}

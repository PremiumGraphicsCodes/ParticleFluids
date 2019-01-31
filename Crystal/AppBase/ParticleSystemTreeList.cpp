#include "ParticleSystemTreeList.h"

#include "imgui.h"

using namespace Crystal::UI;

ParticleSystemTreeList::ParticleSystemTreeList(const std::string& name, Model* model, Canvas* canvas) :
	ITreeList(name, model, canvas)
{
}

void ParticleSystemTreeList::onShow()
{
	const auto& particleSystems = getModel()->getObjects()->getParticleSystems()->getObjects();

	auto n = getName();
	auto str = n.c_str();
	ImGui::Begin(str);

	ImGui::BeginChild("ParticleSystems", ImVec2(250, 100), ImGuiWindowFlags_NoTitleBar);
	for (auto& ps : particleSystems) {
		const auto& n = ps.getName();
		//ImGui::Text(n.c_str());
		bool b = ps._isVisible;
		ImGui::Checkbox(str, &b);
	}
	ImGui::EndChild();

	ImGui::End();
}

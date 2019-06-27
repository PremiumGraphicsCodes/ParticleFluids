#include "ParticleSystemTreeList.h"

#include "imgui.h"

using namespace Crystal::UI;

ParticleSystemTreeList::ParticleSystemTreeList(const std::string& name, Repository* model, Canvas* canvas) :
	ITreeList(name, model, canvas)
{
}

void ParticleSystemTreeList::onShow()
{
	const auto& particleSystems = getRepository()->getObjects()->getFactory()->getPolygonMeshes();

	//auto n = getName();
	//auto str = n.c_str();
	//ImGui::Begin(str);

	ImGui::BeginChild("ParticleSystems", ImVec2(250, 100), ImGuiWindowFlags_NoTitleBar);
	for (auto& ps : particleSystems) {
		const auto& n = ps->getName();
		auto str = n.c_str();
		//ImGui::Text(n.c_str());
		if(ImGui::Checkbox(str, &ps->_isVisible)) {
			getCanvas()->setViewModel(getRepository()->toViewModel());
//			getCanvas()->fitCamera(getRepository()->getBoundingBox());
		}
	}
	ImGui::EndChild();

	//ImGui::End();
}

#include "ImageTreeList.h"

#include "imgui.h"

using namespace Crystal::UI;

ImageTreeList::ImageTreeList(const std::string& name, Repository* model, Canvas* canvas) :
	ITreeList(name, model, canvas)
{
}

void ImageTreeList::onShow()
{
	const auto& lights = getRepository()->getAppearances()->getImages()->getImages();

	auto n = getName();
	auto str = n.c_str();
	//ImGui::Begin(str);

	ImGui::BeginChild(str, ImVec2(250, 100), ImGuiWindowFlags_NoTitleBar);
	for (const auto& l : lights) {
		const auto str = l->getName();
		auto s = str.c_str();
		if (ImGui::Button(s)) {
			//edit.setValue(*l);
		}
	}
	//edit.show();
	ImGui::EndChild();

	//ImGui::End();
}

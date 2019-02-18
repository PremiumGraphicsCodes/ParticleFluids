#include "TextureTreeList.h"

#include "imgui.h"

using namespace Crystal::UI;

TextureTreeList::TextureTreeList(const std::string& name, Repository* model, Canvas* canvas) :
	ITreeList(name, model, canvas)
{
}

void TextureTreeList::onShow()
{
	const auto& textures = getRepository()->getAppearances()->getTextures()->getTextures();

	auto n = getName();
	auto str = n.c_str();
	ImGui::Begin(str);

	ImGui::BeginChild("Textures", ImVec2(250, 100), ImGuiWindowFlags_NoTitleBar);
	/*
	for (auto l : textures) {
		auto str = l.getName();
		auto s = str.c_str();
		ImGui::Text(s);
	}
	*/
	ImGui::EndChild();

	ImGui::End();
}

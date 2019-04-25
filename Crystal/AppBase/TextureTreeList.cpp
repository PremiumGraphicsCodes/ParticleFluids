#include "TextureTreeList.h"

#include "imgui.h"


using namespace Crystal::UI;

TextureTreeList::TextureTreeList(const std::string& name, Repository* model, Canvas* canvas) :
	ITreeList(name, model, canvas),
	image("TextureEdit", *model->getShaders()->getTextures(), 1)
{
}

void TextureTreeList::onShow()
{
	const auto& textures = getRepository()->getShaders()->getTextures()->getTextures();

	auto n = getName();
	auto str = n.c_str();
	ImGui::Begin(str);

	ImGui::BeginChild("Textures", ImVec2(250, 100), ImGuiWindowFlags_NoTitleBar);
	for (const auto& l : textures) {
		auto str = l->getName();
		auto s = str.c_str();
		if (ImGui::Button(s)) {
			image.setTextureId(l->getId());
		}
	}
	ImGui::EndChild();

	image.show();

	ImGui::End();
}

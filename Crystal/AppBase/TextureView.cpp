#include "TextureView.h"


using namespace Crystal::UI;

void TextureView::show()
{
	auto object = repository.findObjectById(textureId);
	if (object == nullptr) {
		return;
	}
	auto texture = object->getTexture();
	const auto width = texture->getWidth();
	const auto height = texture->getHeight();

	texture->bind();
	//glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, image.getWidth(), image.getHeight(), 0, GL_RGBA, GL_UNSIGNED_BYTE, data.data());
	ImGui::Image((ImTextureID)textureId, ImVec2(width, height));
	texture->unbind();



}


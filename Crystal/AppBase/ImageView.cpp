#include "ImageView.h"

using namespace Crystal::UI;

void ImageView::show()
{
	auto object = repository.findObjectById(textureId);
	if (object == nullptr) {
		return;
	}
	auto texture = object->getTexture();
	const auto width = texture->getWidth();
	const auto height = texture->getHeight();

	ImGui::ImageButton((ImTextureID)textureId, ImVec2(width, height));
}
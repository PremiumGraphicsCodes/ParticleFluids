#include "GL/glew.h"

#include "ImageView.h"


using namespace Crystal::Graphics;
using namespace Crystal::UI;

void ImageView::show()
{
	// Turn the RGBA pixel data into an OpenGL texture:
	ImGui::Image((void*)(intptr_t)textureId, ImVec2(image.getWidth(), image.getHeight()));
}

void ImageView::setValue(const Image& image)
{
	this->image = image;

	glGenTextures(1, &textureId);
	glBindTexture(GL_TEXTURE_2D, textureId);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
	glPixelStorei(GL_UNPACK_ROW_LENGTH, 0);
	auto data = image.getValues();
	glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, image.getWidth(), image.getHeight(), 0, GL_RGBA, GL_UNSIGNED_BYTE, data.data());

}


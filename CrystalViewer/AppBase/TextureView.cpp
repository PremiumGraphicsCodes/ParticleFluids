#include "../../Crystal/Shader/glew.h"

#include "TextureView.h"

#include "imgui.h"

using namespace Crystal::Graphics;
using namespace Crystal::UI;

TextureView::TextureView(const std::string& name) :
	TextureView(name, Graphics::Image(0, 0))
{
}

TextureView::TextureView(const std::string& name, const Image& image) :
	IWindow(name),
	image(image),
	textureId(-1),
	nameView("TextureName")
{
	glGenTextures(1, &textureId);

	setValue(image);
}

TextureView::~TextureView()
{
	glDeleteTextures(1, &textureId);
}

void TextureView::onShow()
{
	nameView.show();
	// Turn the RGBA pixel data into an OpenGL texture:
	glBindTexture(GL_TEXTURE_2D, textureId);
	ImGui::Image((void*)(intptr_t)textureId, ImVec2(image.getWidth(), image.getHeight()));
	glBindTexture(GL_TEXTURE_2D, 0);
}

void TextureView::setValue(const Image& image)
{
	this->image = image;

	glBindTexture(GL_TEXTURE_2D, textureId);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
	glPixelStorei(GL_UNPACK_ROW_LENGTH, 0);
	const auto& data = image.getValues();
	glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, image.getWidth(), image.getHeight(), 0, GL_RGBA, GL_UNSIGNED_BYTE, data.data());
	glBindTexture(GL_TEXTURE_2D, 0);
}

